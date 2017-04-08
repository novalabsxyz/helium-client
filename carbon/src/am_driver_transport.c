#include "am_driver_transport.h"
// #include "am_driver_transport_private.h"

#include <assert.h>

void amd_uart_tx_framed_start(struct uart_tx_ctx * ctx,
                              size_t frame_len) {
    assert(!ctx->framed_busy);

    am_frame_encode_init(&ctx->ctx, frame_len);

    ctx->framed_busy = true;
}

enum amd_uart_tx_stat amd_uart_tx_framed_give(struct am_transport_iface const * iface,
                                              struct uart_tx_ctx * ctx,
                                              void const * data,
                                              size_t len) {
    /* Take the input data and chunk it into several
     * TX_FRAME_BUFFER_SIZE chunks of data. Send these individually to
     * the USART to be transmitted.
     *
     * This function does not need to be given an entire frame. */

    enum am_frame_encode_buffer_status bstat;
    enum am_frame_encode_give_status gstat;

    assert(ctx->framed_busy);
    assert(data || len == 0);

    /* Give the entire buffer to the encoder. */
    gstat = am_frame_encode_give(&ctx->ctx, data, len);
    assert(gstat == afeg_status_OK);

   /* Pull out TX_FRAME_BUFFER_SIZE chunks from the encoder until we
     * exhaust the given data. */
    while (true) {
        size_t used = 0;

        bstat = am_frame_encode_buffer(&ctx->ctx,
                                       ctx->tx_frame_buffer,
                                       sizeof(ctx->tx_frame_buffer),
                                       &used);

        if ((bstat == afebu_status_BUFFER_VALID) ||
            (bstat == afebu_status_BUFFER_FULL)) {
            assert(used > 0);

            /* Buffer is valid. Transmit it. */
            enum amd_uart_tx_stat tstat;
            tstat = iface->tx(iface->param,
                              ctx->tx_frame_buffer,
                              used);
            assert(amdu_tx_ok == tstat);
        } else if (bstat == afebu_status_DONE) {
            /* We've reached the end of the frame. */
            ctx->framed_busy = false;
            return amdu_tx_frame_done;
        } else if (bstat == afebu_status_NEED_INPUT) {
            /* We've reached the end of the available data. We need to
             * go back to the caller to get more. */
            return amdu_tx_frame_more;
        } else {
            assert(0);
        }
    }
}

enum amd_uart_rx_stat amd_uart_rx_framed_init(struct uart_rx_ctx * ctx) {
    am_frame_decode_init(&ctx->ctx);
    ctx->buf = (struct uart_rx_buffer) {
        .stat = amd_uart_rx_UNINITIALIZED,
        .used = 0,
    };

    return amd_uart_rx_ok;
}

enum amd_uart_rx_stat amd_uart_rx_framed_get(struct am_transport_iface const * iface,
                                             struct uart_rx_ctx * ctx,
                                             void * data,
                                             size_t len,
                                             size_t * used) {
    *used = 0;
    uint8_t * const bytes = data;

    while (true) {
        enum amd_uart_rx_stat rxs;

        if (0 == am_frame_decode_remaining(&ctx->ctx)) {
            /* The RX buffer has no decodable data. Try and get some
             * more there. */
            rxs = iface->rx(iface->param, &ctx->buf);

            /* If the RX resulted in bad things, forward on the errors. */
            switch (rxs) {
            case amd_uart_rx_os_timeout:
            case amd_uart_rx_err:
                return rxs;
            default:
                break; // leave switch
            }

            /* These are the assumptions we make after leaving this
             * block. */
            assert((rxs == amd_uart_rx_ok) ||
                   (rxs == amd_uart_rx_timeout));
            assert(rxs == ctx->buf.stat);

            /* Give the buffer's data to the decoder. */
            if (ctx->buf.used > 0) {
                enum am_frame_decode_give_status const dgs =
                    am_frame_decode_give(&ctx->ctx,
                                         ctx->buf.data,
                                         ctx->buf.used);
                assert(afdg_status_OK == dgs);
            } else {
                /* It's possible that we finish parsing a frame on the
                 * RX-buffer size boundary. When this happens, we'll
                 * get a completely full buffer with an `_rx_ok`
                 * status. Normally, we're responsible to make sure we
                 * read until we get a timeout, but since it's
                 * possible to use this function to stream out
                 * multiple consecutive frames, we need to handle the
                 * empty-timeout-RX frame special.
                 *
                 * When we see one of these `_rx_timeout` cases, we
                 * can simply ignore it if the size of the data is
                 * 0. The next time we call `_uart_rx`, either we'll
                 * get an OS timeout (which is handled differently)
                 * unless we've actually received more data from the
                 * UART. Because of this, I think it's safe to ignore
                 * all empty timeouts. */
                assert(amd_uart_rx_timeout == rxs);
            }
        } else if (*used >= len) {
            return amd_uart_rx_frame_more;
        } else {
            /* In a loop, decode each byte into our input buffer while we
             * still have input buffer space. */
            while (*used < len) {
                enum am_frame_decode_byte_status const dbs =
                    am_frame_decode_byte(&ctx->ctx, &bytes[*used]);

                if (afdb_status_OUT_VALID == dbs) {
                    /* The byte is valid. Keep going. */
                    (*used)++;
                    continue;
                } else if (afdb_status_NEED_INPUT == dbs) {
                    /* We ran out of input data to decode. Go back to the
                     * outer while loop so that we can get more data from
                     * the UART. */
                    break; // leave inner while
                } else if (afdb_status_RESTART_FRAME == dbs) {
                    /* Oh dear, when parsing out the frame, we found a
                     * place where we got a new SOF after we'd already
                     * started parsing a frame. */
                    return amd_uart_rx_frame_restart;
                } else if (afdb_status_DONE == dbs) {
                    /* We found the end of the frame. */
                    return amd_uart_rx_frame_done;
                } else  if (afdb_status_DONE_WITH_ERROR == dbs) {
                    /* We found the end of the frame, but there are errors. */
                    return amd_uart_rx_frame_done_with_error;
                }
            }
        }
    }
}

enum amd_uart_rx_stat amd_uart_rx_framed_flush(struct am_transport_iface const * iface,
                                               struct uart_rx_ctx * ctx) {
    uint8_t dummy[16];
    size_t used;

    while (true) {
        enum amd_uart_rx_stat const ret =
            amd_uart_rx_framed_get(iface, ctx, dummy, sizeof(dummy), &used);

        switch (ret) {
        default:
        case amd_uart_rx_ok:
            /* None of these should be returned by _framed_get. */
            assert(0);
            break;
        case amd_uart_rx_os_timeout:
        case amd_uart_rx_err:
        case amd_uart_rx_frame_done:
        case amd_uart_rx_frame_done_with_error:
            /* These are all the terminals. When these occur, we
             * return them as status. */
            return ret;
        case amd_uart_rx_timeout:
        case amd_uart_rx_frame_more:
        case amd_uart_rx_frame_restart:
        case amd_uart_rx_frame_timeout:
            /* These are all things that require us to service the
             * loop again. */
            break;
        }
    }
}

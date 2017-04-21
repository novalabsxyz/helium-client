#include "xfer/carbon_xfer.h"
#include "carbon_interface_helpers.h"

#include <assert.h>

void carbon_xfer_tx_start(struct carbon_xfer_tx_ctx * ctx,
                          size_t frame_len) {
    ctx->framed_busy = true;
    carbon_frame_encode_init(&ctx->ctx, frame_len);
}

enum carbon_xfer_tx_give_status carbon_xfer_tx_give(struct carbon_transport_iface const * iface,
                                                    struct carbon_xfer_tx_ctx * ctx,
                                                    void const * data,
                                                    size_t len) {
    /* Take the input data and chunk it into several
     * TX_FRAME_BUFFER_SIZE chunks of data. Send these individually to
     * the USART to be transmitted.
     *
     * This function does not need to be given an entire frame. */

    enum carbon_frame_encode_buffer_status bstat;
    enum carbon_frame_encode_give_status gstat;

    assert(ctx->framed_busy);
    assert(data || len == 0);

    /* Give the entire buffer to the encoder. */
    gstat = carbon_frame_encode_give(&ctx->ctx, data, len);
    assert(gstat == carbon_frame_encode_give_OK);

    /* Pull out TX_FRAME_BUFFER_SIZE chunks from the encoder until we
     * exhaust the given data. */
    while (true) {
        bstat = carbon_frame_encode_buffer(&ctx->ctx,
                                           ctx->buffer.data,
                                           sizeof(ctx->buffer.data),
                                           &ctx->buffer.used);

        if ((bstat == carbon_frame_encode_buffer_BUFFER_VALID) ||
            (bstat == carbon_frame_encode_buffer_BUFFER_FULL)) {
            assert(ctx->buffer.used > 0);

            /* Buffer is valid. Transmit it. */
            enum carbon_iface_tx_stat tstat;
            tstat = transport_tx(iface, &ctx->buffer);
            if (carbon_iface_tx_OK != tstat) {
                return carbon_xfer_tx_give_ERR;
            }
        } else if (bstat == carbon_frame_encode_buffer_DONE) {
            /* We've reached the end of the frame. */
            ctx->framed_busy = false;
            return carbon_xfer_tx_give_DONE;
        } else if (bstat == carbon_frame_encode_buffer_NEED_INPUT) {
            /* We've reached the end of the available data. We need to
             * go back to the caller to get more. */
            return carbon_xfer_tx_give_MORE;
        } else {
            assert(0);
        }
    }
}

void carbon_xfer_rx_init(struct carbon_xfer_rx_ctx * ctx) {
    carbon_frame_decode_init(&ctx->ctx);
    ctx->buf = (struct carbon_rx_buffer) {
        .stat = carbon_iface_rx_ERR_TIMEOUT,
        .used = 0,
    };
}

enum carbon_xfer_rx_get_status carbon_xfer_rx_get(struct carbon_transport_iface const * iface,
                                                  struct carbon_xfer_rx_ctx * ctx,
                                                  void * data,
                                                  size_t len,
                                                  size_t * used) {
    *used = 0;
    uint8_t * const bytes = data;

    while (true) {
        enum carbon_iface_rx_stat rxs;

        if (0 == carbon_frame_decode_remaining(&ctx->ctx)) {
            /* The RX buffer has no decodable data. Try and get some
             * more there. */
            rxs = iface->rx(iface->param, &ctx->buf);

            /* If the RX resulted in bad things, forward on the errors. */
            if (carbon_iface_rx_ERR_TIMEOUT == rxs) {
                return carbon_xfer_rx_get_ERR_TIMEOUT;
            }

            /* These are the assumptions we make after leaving this
             * block. */
            assert((rxs == carbon_iface_rx_MORE) ||
                   (rxs == carbon_iface_rx_DONE));
            assert(rxs == ctx->buf.stat);

            /* Give the buffer's data to the decoder. */
            if (ctx->buf.used > 0) {
                enum carbon_frame_decode_give_status const dgs =
                    carbon_frame_decode_give(&ctx->ctx,
                                             ctx->buf.data,
                                             ctx->buf.used);
                assert(carbon_frame_decode_give_OK == dgs);
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
                assert(carbon_iface_rx_DONE == rxs);
            }
        } else if (*used >= len) {
            return carbon_xfer_rx_get_MORE;
        } else {
            /* In a loop, decode each byte into our input buffer while we
             * still have input buffer space. */
            while (*used < len) {
                enum carbon_frame_decode_byte_status const dbs =
                    carbon_frame_decode_byte(&ctx->ctx, &bytes[*used]);

                if (carbon_frame_decode_byte_OUT_VALID == dbs) {
                    /* The byte is valid. Keep going. */
                    (*used)++;
                    continue;
                } else if (carbon_frame_decode_byte_NEED_INPUT == dbs) {
                    /* We ran out of input data to decode. Go back to the
                     * outer while loop so that we can get more data from
                     * the UART. */
                    break; // leave inner while
                } else if (carbon_frame_decode_byte_RESTART_FRAME == dbs) {
                    /* Oh dear, when parsing out the frame, we found a
                     * place where we got a new SOF after we'd already
                     * started parsing a frame. */
                    return carbon_xfer_rx_get_RESTART;
                } else if (carbon_frame_decode_byte_DONE == dbs) {
                    /* We found the end of the frame. */
                    return carbon_xfer_rx_get_DONE;
                } else  if (carbon_frame_decode_byte_DONE_WITH_ERROR == dbs) {
                    /* We found the end of the frame, but there are errors. */
                    return carbon_xfer_rx_get_ERR_DONE_WITH_ERROR;
                }
            }
        }
    }
}

enum carbon_xfer_rx_get_status carbon_xfer_rx_flush(struct carbon_transport_iface const * iface,
                                                    struct carbon_xfer_rx_ctx * ctx) {
    uint8_t dummy[16];
    size_t used;

    while (true) {
        enum carbon_xfer_rx_get_status const ret =
            carbon_xfer_rx_get(iface, ctx, dummy, sizeof(dummy), &used);

        switch (ret) {
        case carbon_xfer_rx_get_DONE:
        case carbon_xfer_rx_get_ERR_TIMEOUT:
        case carbon_xfer_rx_get_ERR_DONE_WITH_ERROR:
            /* These are all the terminals. When these occur, we
             * return them as status. */
            return ret;

        case carbon_xfer_rx_get_MORE:
        case carbon_xfer_rx_get_RESTART:
            /* These are all things that require us to service the
             * loop again. */
            break;
        }
    }
}

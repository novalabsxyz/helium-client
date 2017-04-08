#include "am_frame_atom_api.h"
#include "helium_atom_api_infodefines.h"
#include "array_size.h"
#include "am_frame_encode.h"
#include "am_frame_decode.h"
#include "am_driver_transport.h"

#include <assert.h>
#include <string.h>

#define XFER_CHUNK_SIZE (16)

static size_t aa_size(struct amfaa_ctx * ctx, struct a_cmd_t const * req);
static enum amf_atom_api_status aa_tx(struct amfaa_ctx * ctx, struct a_cmd_t const * req);
static enum amf_atom_api_status aa_rx(struct amfaa_ctx * ctx, struct a_cmd_t * res);

static bool caut_status_is_error(enum caut_status c);

enum amf_atom_api_status amf_atom_api(struct amfaa_ctx * ctx, struct a_cmd_t * req_res) {
    assert(ctx);
    assert(req_res);

    enum amf_atom_api_status astat;
    uint16_t const req_seq = req_res->sequence;

    astat = aa_tx(ctx, req_res);
    if (amfaa_status_ok != astat) {
        return astat;
    }

    astat = aa_rx(ctx, req_res);
    if (amfaa_status_ok != astat) {
        return astat;
    }

    uint16_t const res_seq = req_res->sequence;

    if (req_seq != res_seq) {
        return amfaa_status_err_wrong_seq;
    }

    return amfaa_status_ok;
}

static size_t aa_size(struct amfaa_ctx * ctx, struct a_cmd_t const * req) {
    enum caut_status cstat;
    struct schema_size_iterator si;
    size_t ret = 0;

    cstat = schema_size_iterator_init(
        &si, &schema_descriptor_helium_atom_api,
        ctx->tis.size, ARRAY_SIZE(ctx->tis.size),
        type_id_helium_atom_api_a_cmd_t, req);
    assert(caut_status_ok == cstat);

    cstat = caut_size_get(&si, &ret);
    assert(caut_status_ok == cstat);

    return ret;
}

static enum amf_atom_api_status aa_tx(struct amfaa_ctx * ctx, struct a_cmd_t const * req) {
    enum caut_status cstat;
    struct schema_encode_iterator ei;
    struct uart_tx_ctx tx_ctx;

    amd_uart_tx_framed_start(&tx_ctx, aa_size(ctx, req));

    cstat = schema_encode_iterator_init(
        &ei, &schema_descriptor_helium_atom_api,
        ctx->tis.encode, ARRAY_SIZE(ctx->tis.encode),
        type_id_helium_atom_api_a_cmd_t, req);
    assert(caut_status_ok == cstat);

    uint8_t tx_chunk[XFER_CHUNK_SIZE] = { 0 };
    size_t enc_bytes = 0;

    do {
        cstat = caut_enc_get(&ei, tx_chunk, sizeof(tx_chunk), &enc_bytes);
        if (caut_status_is_error(cstat)) {
            return amfaa_status_err_bad_cauterize;
        }

        /* Transmit the encoded buffer. */
        assert(enc_bytes > 0);

        enum amd_uart_tx_stat const gstat =
            amd_uart_tx_framed_give(ctx->iface, &tx_ctx, tx_chunk, enc_bytes);

        /* We're going to spend a bunch of lines here asserting on
         * some assumptions because, frankly, there's a few moving
         * pieces here that I'm not entirely convinced work the way I
         * think they do. Hardware is, well, hard. */

        /* This API shouldn't ever return OK. TODO: split up the
         * enumerations so that this sort of check doesn't need to
         * happen. */
        assert(amdu_tx_ok != gstat);

        /* The way the TX stuff works, I'm pretty sure we really
         * shouldn't ever encounter this error. I'm going to assert
         * here for now until we get evidence that it can happen. */
        assert(amdu_tx_err != gstat);

        /* Make sure that the return values from the different
         * encoders agree. */
        if (caut_status_ok == cstat) {
            /* If the cauterize encode finished, then the most recent
             * give should have finished the frame. */
            assert(gstat == amdu_tx_frame_done);
        } else if (caut_status_ok_busy == cstat) {
            /* If the cauterize encode is still busy, then the frame
             * should still require more data. */
            assert(gstat == amdu_tx_frame_more);
        } else {
            /* I don't think we should ever reach this. */
            assert(0);
        }
    } while (caut_status_ok != cstat);

    return amfaa_status_ok;
}

static enum amf_atom_api_status aa_rx(struct amfaa_ctx * ctx, struct a_cmd_t * res) {
    enum caut_status cstat;
    struct schema_decode_iterator di;
    struct uart_rx_ctx rx_ctx;

    memset(res, 0xFF, sizeof(*res));

    amd_uart_rx_framed_init(&rx_ctx);

    cstat = schema_decode_iterator_init(
        &di, &schema_descriptor_helium_atom_api,
        ctx->tis.decode, ARRAY_SIZE(ctx->tis.decode),
        type_id_helium_atom_api_a_cmd_t, res);
    assert(caut_status_ok == cstat);

    size_t used = 0;
    uint8_t rx_chunk[XFER_CHUNK_SIZE] = { 0 };
    enum amd_uart_rx_stat gstat;

    while (true) {
        gstat = amd_uart_rx_framed_get(ctx->iface, &rx_ctx, rx_chunk, sizeof(rx_chunk), &used);
        if (gstat != amd_uart_rx_frame_more && gstat != amd_uart_rx_frame_done) {
            break;
        } else {
            size_t put_size = 0;
            cstat = caut_dec_put(&di, rx_chunk, used, &put_size);
            assert(caut_status_ok == cstat || caut_status_ok_busy == cstat);

            if (cstat != caut_status_ok_busy) {
                break;
            }
        }
    }

    /* Once again, make sure these never pop out. They shouldn't. It's
     * John's fault for making a bad Cauterize API that needs
     * clarification. */
    assert((cstat != caut_status_ok_pop) &&
           (cstat != caut_status_ok_pushed));

    if (cstat == caut_status_ok) {
        /* The cauterize decode was successful. We can return now. */
        assert(gstat == amd_uart_rx_frame_done);

        return amfaa_status_ok;
    } else if (caut_status_is_error(cstat)) {
        /* Something went wrong while decoding the cauterize value. */
        return amfaa_status_err_bad_cauterize;
    } else {
        /* These two shouldn't happen by this point. */
        assert(caut_status_ok_busy == cstat);
        assert(amd_uart_rx_frame_more == gstat);
        assert(amd_uart_rx_frame_timeout == gstat);

        /* Something went wrong with framing. */
        if (amd_uart_rx_os_timeout == gstat) {
            return amfaa_status_err_timeout;
        } else if (amd_uart_rx_frame_done_with_error == gstat) {
            return amfaa_status_err_bad_frame;
        } else {
            /* I think we've covered all the cases above. If any more
             * pop out, we should specifically handle the error. */
            assert(0);
        }
    }

    return amfaa_status_err_timeout;
}

static bool caut_status_is_error(enum caut_status c) {
    bool ret = true;

    switch (c) {
    case caut_status_ok_pop:
    case caut_status_ok_pushed:
        // This is to paper over a bit of a problem in the cauterize
        // streaming API -- these two shouldn't really ever pop out of
        // the encoding or decoding functions.
        assert(0);
        break;
    case caut_status_ok:
    case caut_status_ok_busy:
        ret = false;
        break;
    case caut_status_err_bad_state:
    case caut_status_err_need_byte:
    case caut_status_err_invalid_type_id:
    case caut_status_err_iter_stack_would_overflow:
    case caut_status_err_invalid_range:
    case caut_status_err_invalid_enum:
    case caut_status_err_invalid_vector:
    case caut_status_err_invalid_record:
    case caut_status_err_invalid_combination:
    case caut_status_err_invalid_union:
    default:
        ret = true;
        break;
    }

    return ret;
}

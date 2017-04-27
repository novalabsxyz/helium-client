#include "carbon_api.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(ARR) (sizeof(ARR) / sizeof(ARR[0]))
#endif

#include "helium_atom_api_infodefines.h"
#include "xfer/carbon_xfer.h"

#include <assert.h>
#include <string.h>

#define XFER_CHUNK_SIZE (16)

static size_t aa_size(struct carbon_api_ctx * ctx, struct a_cmd_t const * req);
static enum carbon_api_status aa_tx(struct carbon_api_ctx * ctx, struct a_cmd_t const * req);
static void caut_dec_reset(struct carbon_api_ctx * ctx,
                           struct schema_decode_iterator * di,
                           struct a_cmd_t * res);
static enum carbon_api_status aa_rx(struct carbon_api_ctx * ctx, struct a_cmd_t * res);

static bool caut_status_is_error(enum caut_status c);

enum carbon_api_status carbon_api(struct carbon_api_ctx * ctx, struct a_cmd_t * req_res) {
    assert(ctx);
    assert(req_res);

    enum carbon_api_status astat;
    uint16_t const req_seq = req_res->sequence;

    astat = aa_tx(ctx, req_res);
    if (carbon_api_status_ok != astat) {
        return astat;
    }

    astat = aa_rx(ctx, req_res);
    if (carbon_api_status_ok != astat) {
        return astat;
    }

    uint16_t const res_seq = req_res->sequence;

    if (req_seq != res_seq) {
        return carbon_api_status_err_wrong_seq;
    }

    return carbon_api_status_ok;
}

static size_t aa_size(struct carbon_api_ctx * ctx, struct a_cmd_t const * req) {
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

static enum carbon_api_status aa_tx(struct carbon_api_ctx * ctx, struct a_cmd_t const * req) {
    enum caut_status cstat;
    struct schema_encode_iterator ei;
    struct carbon_xfer_tx_ctx tx_ctx;

    carbon_xfer_tx_start(&tx_ctx, aa_size(ctx, req));

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
            return carbon_api_status_err_bad_cauterize;
        }

        /* Transmit the encoded buffer. */
        assert(enc_bytes > 0);

        enum carbon_xfer_tx_give_status const gstat =
            carbon_xfer_tx_give(ctx->iface, &tx_ctx, tx_chunk, enc_bytes);

        if (carbon_xfer_tx_give_ERR == gstat) {
            /* The way the TX stuff works, I'm pretty sure we really
             * shouldn't ever encounter this error. However, future
             * implementations may encounter TX errors. Handle them
             * here. */
            return carbon_api_status_err_xfer;
        } else if (caut_status_ok == cstat) {
            /* If the cauterize encode finished, then the most recent
             * give should have finished the frame. */
            assert(gstat == carbon_xfer_tx_give_DONE);
        } else if (caut_status_ok_busy == cstat) {
            /* If the cauterize encode is still busy, then the frame
             * should still require more data. */
            assert(gstat == carbon_xfer_tx_give_MORE);
        } else {
            /* I don't think we should ever reach this. */
            assert(0);
        }
    } while (caut_status_ok != cstat);

    return carbon_api_status_ok;
}

static void caut_dec_reset(struct carbon_api_ctx * ctx,
                           struct schema_decode_iterator * di,
                           struct a_cmd_t * res) {
    enum caut_status cstat;
    cstat = schema_decode_iterator_init(
        di, &schema_descriptor_helium_atom_api,
        ctx->tis.decode, ARRAY_SIZE(ctx->tis.decode),
        type_id_helium_atom_api_a_cmd_t, res);
    assert(caut_status_ok == cstat);
}

static enum carbon_api_status aa_rx(struct carbon_api_ctx * ctx, struct a_cmd_t * res) {
    struct schema_decode_iterator di;
    struct carbon_xfer_rx_ctx rx_ctx;

    memset(res, 0xFF, sizeof(*res));

    carbon_xfer_rx_init(&rx_ctx);
    caut_dec_reset(ctx, &di, res);

    size_t used = 0;
    uint8_t rx_chunk[XFER_CHUNK_SIZE] = { 0 };
    enum carbon_xfer_rx_get_status gstat;
    enum caut_status c_dec_stat = caut_status_err_UNIMPLEMENTED;

    while (true) {
        gstat = carbon_xfer_rx_get(ctx->iface, &rx_ctx, rx_chunk, sizeof(rx_chunk), &used);

        if (gstat == carbon_xfer_rx_get_MORE || gstat == carbon_xfer_rx_get_DONE) {
            size_t put_size = 0;
            c_dec_stat = caut_dec_put(&di, rx_chunk, used, &put_size);
            assert(caut_status_ok == c_dec_stat || caut_status_ok_busy == c_dec_stat);

            if (c_dec_stat != caut_status_ok_busy) {
                /* If cauterize stops being busy, it's time to get
                 * out. If cauterize stopped on something other than
                 * _ok, flush the RX. */
                if (c_dec_stat != caut_status_ok) {
                    (void)carbon_xfer_rx_flush(ctx->iface, &rx_ctx);
                }
                break;
            }
        } else if (gstat == carbon_xfer_rx_get_RESTART) {
            /* The receive encountered a frame restart. We need to
             * clear the state we've accumulated so far in the
             * Cauterize decoder. */
            caut_dec_reset(ctx, &di, res);
        } else if (gstat == carbon_xfer_rx_get_ERR_TIMEOUT) {
            return carbon_api_status_err_timeout;
        } else if (gstat == carbon_xfer_rx_get_ERR_DONE_WITH_ERROR) {

            return carbon_api_status_err_bad_frame;
        }
    }

    /* Once again, make sure these never pop out. They shouldn't. It's
     * John's fault for making a bad Cauterize API that needs
     * clarification. */
    assert((c_dec_stat != caut_status_ok_pop) &&
           (c_dec_stat != caut_status_ok_pushed));
    assert(c_dec_stat != caut_status_err_UNIMPLEMENTED);

    if (c_dec_stat == caut_status_ok) {
        /* The cauterize decode was successful. We can return now. */
        return carbon_api_status_ok;
    } else if (caut_status_is_error(c_dec_stat)) {
        /* Something went wrong while decoding the cauterize value. */
        return carbon_api_status_err_bad_cauterize;
    } else {
        /* We shoudln't be able to reach this branch. */
        assert(0);
        return carbon_api_status_err_timeout;
    }
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
    case caut_status_err_UNIMPLEMENTED:
    default:
        ret = true;
        break;
    }

    return ret;
}

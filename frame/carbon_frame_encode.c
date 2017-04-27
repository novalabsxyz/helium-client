#include "carbon_frame_encode.h"
#include "carbon_frame_common.h"

#include <assert.h>

static bool ctx_is_initialized(struct carbon_frame_encode_ctx * ctx);
static bool needs_escape(uint8_t byte);
static uint8_t escape(uint8_t byte);
static void advance_pos(struct carbon_frame_encode_ctx * ctx);
static bool write_out_byte(struct carbon_frame_encode_ctx * ctx, uint8_t b, uint8_t * out);

void carbon_frame_encode_init(struct carbon_frame_encode_ctx * ctx, size_t len) {
    assert(ctx);
    assert(len <= UINT16_MAX);

    *ctx = (struct carbon_frame_encode_ctx) {
        .state = carbon_frame_encode_state_SOF,
        .len = len,
        .pos = 0,
    };
}

enum carbon_frame_encode_give_status carbon_frame_encode_give(struct carbon_frame_encode_ctx * ctx,
                                                              void const * input,
                                                              size_t len) {
    assert(ctx_is_initialized(ctx));
    assert(len == 0 || input);

    if (ctx->given_len > ctx->given_pos) {
        /* The previous give was not completely consumed. */
        return carbon_frame_encode_give_BUSY;
    }

    if (ctx->len < len + ctx->pos) {
        /* This would overflow the bounds of the context. */
        return carbon_frame_encode_give_OVERFLOW;
    }

    ctx->given = input;
    ctx->given_len = len;
    ctx->given_pos = 0;

    return carbon_frame_encode_give_OK;
}

enum carbon_frame_encode_byte_status carbon_frame_encode_byte(struct carbon_frame_encode_ctx * ctx,
                                                              uint8_t * out) {
    assert(ctx_is_initialized(ctx));
    assert(out);

    enum carbon_frame_encode_byte_status ret = carbon_frame_encode_byte_UNINITIALIZED;
    uint8_t const * given_bytes = ctx->given;
    uint8_t b;

    switch(ctx->state) {
    case carbon_frame_encode_state_SOF:
        ctx->state = carbon_frame_encode_state_LEN_LSB;
        *out = SOF_CHAR;
        ret = carbon_frame_encode_byte_OUT_VALID;
        break;
    case carbon_frame_encode_state_LEN_LSB:
        b = (0xFF & (ctx->len >> 0));

        if (write_out_byte(ctx, b, out)) {
            ctx->state = carbon_frame_encode_state_LEN_MSB;
        }

        ret = carbon_frame_encode_byte_OUT_VALID;
        break;
    case carbon_frame_encode_state_LEN_MSB:
        b = (0xFF & (ctx->len >> 8));

        if (write_out_byte(ctx, b, out)) {
            if (ctx->len > 0) {
                /* Only go to the length state if there's data to be
                 * output. */
                ctx->state = carbon_frame_encode_state_DATA;
            } else {
                /* If there's no data (this is an empty frame), then
                 * we can skip straight to EOF. */
                ctx->state = carbon_frame_encode_state_EOF;
            }
        }

        ret = carbon_frame_encode_byte_OUT_VALID;
        break;
    case carbon_frame_encode_state_DATA:
        if (ctx->given_pos >= ctx->given_len) {
            ret = carbon_frame_encode_byte_NEED_INPUT;
        } else {
            b = given_bytes[ctx->given_pos];

            if (write_out_byte(ctx, b, out)) {
                advance_pos(ctx);
            }

            if (ctx->pos >= ctx->len) {
                ctx->state = carbon_frame_encode_state_EOF;
            }

            ret = carbon_frame_encode_byte_OUT_VALID;
        }
        break;
    case carbon_frame_encode_state_EOF:
        *out = EOF_CHAR;
        ctx->state = carbon_frame_encode_state_DONE;
        ret = carbon_frame_encode_byte_OUT_VALID;
        break;
    case carbon_frame_encode_state_DONE:
        *out = 0;
        ret = carbon_frame_encode_byte_DONE;
        break;
    case carbon_frame_encode_state_UNINITIALIZED:
    default:
        assert(0);
        break;
    }

    return ret;
}

enum carbon_frame_encode_buffer_status carbon_frame_encode_buffer(struct carbon_frame_encode_ctx * const ctx,
                                                                  uint8_t * const buffer,
                                                                  size_t const bufsize,
                                                                  size_t * const used) {
    for (*used = 0; *used < bufsize; (*used)++) {
        enum carbon_frame_encode_byte_status stat;

        stat = carbon_frame_encode_byte(ctx, &buffer[*used]);
        if (stat == carbon_frame_encode_byte_OUT_VALID) {
            continue;
        } else if (stat == carbon_frame_encode_byte_NEED_INPUT) {
            if (*used == 0) {
                /* This was the first loop, return _NEED_INPUT. */
                return carbon_frame_encode_buffer_NEED_INPUT;
            } else {
                /* We have some valid data in the buffer even though
                 * we need more input now, so report the output as
                 * valid and return. */
                return carbon_frame_encode_buffer_BUFFER_VALID;
            }
        } else if (stat == carbon_frame_encode_byte_DONE) {
            if (*used == 0) {
                return carbon_frame_encode_buffer_DONE;
            } else {
                return carbon_frame_encode_buffer_BUFFER_VALID;
            }
        }
    }

    assert(*used > 0);

    /* We dropped out of the loop, so we must have filled our input
     * buffer before exhausing everything. */
    return carbon_frame_encode_buffer_BUFFER_FULL;
}


static bool ctx_is_initialized(struct carbon_frame_encode_ctx * ctx) {
    assert(ctx);

    switch(ctx->state) {
    case carbon_frame_encode_state_UNINITIALIZED:
        return false;
    case carbon_frame_encode_state_SOF:
    case carbon_frame_encode_state_LEN_LSB:
    case carbon_frame_encode_state_LEN_MSB:
    case carbon_frame_encode_state_DATA:
    case carbon_frame_encode_state_EOF:
    case carbon_frame_encode_state_DONE:
        break;
    }

    return true;
}

static bool needs_escape(uint8_t byte) {
    switch (byte) {
    case SOF_CHAR:
    case EOF_CHAR:
    case ESC_CHAR:
        return true;
    default:
        return false;
    }
}

static uint8_t escape(uint8_t byte) {
    uint8_t r = 0;

    switch (byte) {
    case SOF_CHAR:
        r = SOF_ESC;
        break;
    case EOF_CHAR:
        r = EOF_ESC;
        break;
    case ESC_CHAR:
        r = ESC_ESC;
        break;
    default:
        assert(0);
    }

    return r;
}

static void advance_pos(struct carbon_frame_encode_ctx * ctx) {
    assert(ctx->pos < ctx->len);
    assert(ctx->given_pos < ctx->given_len);

    ctx->pos++;
    ctx->given_pos++;
}

static bool write_out_byte(struct carbon_frame_encode_ctx * ctx, uint8_t b, uint8_t * out) {
    /* Return false when we need to see this byte has more bytes to
     * output. Return true when it's okay to move on to the next
     * byte. */

    if (needs_escape(b)) {
        if (!ctx->already_escaped) {
            *out = ESC_CHAR;
            ctx->already_escaped = true;
            return false;
        } else {
            *out = escape(b);
            ctx->already_escaped = false;
            return true;
        }
    } else {
        *out = b;
        return true;
    }
}

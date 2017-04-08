#include "am_frame_encode.h"
#include "am_frame_common.h"

#include <assert.h>

static bool ctx_is_initialized(struct am_frame_encode_ctx * ctx);
static bool needs_escape(uint8_t byte);
static uint8_t escape(uint8_t byte);
static void advance_pos(struct am_frame_encode_ctx * ctx);
static bool write_out_byte(struct am_frame_encode_ctx * ctx, uint8_t b, uint8_t * out);

void am_frame_encode_init(struct am_frame_encode_ctx * ctx, size_t len) {
    assert(ctx);
    assert(len <= UINT16_MAX);

    *ctx = (struct am_frame_encode_ctx) {
        .state = afe_state_SOF,
        .len = len,
        .pos = 0,
    };
}

enum am_frame_encode_give_status am_frame_encode_give(struct am_frame_encode_ctx * ctx,
                                                      void const * input,
                                                      size_t len) {
    assert(ctx_is_initialized(ctx));
    assert(len == 0 || input);

    if (ctx->given_len > ctx->given_pos) {
        /* The previous give was not completely consumed. */
        return afeg_status_BUSY;
    }

    if (ctx->len < len + ctx->pos) {
        /* This would overflow the bounds of the context. */
        return afeg_status_OVERFLOW;
    }

    ctx->given = input;
    ctx->given_len = len;
    ctx->given_pos = 0;

    return afeg_status_OK;
}

enum am_frame_encode_byte_status am_frame_encode_byte(struct am_frame_encode_ctx * ctx,
                                                      uint8_t * out) {
    assert(ctx_is_initialized(ctx));
    assert(out);

    enum am_frame_encode_byte_status ret = afeb_status_UNINITIALIZED;
    uint8_t const * given_bytes = ctx->given;
    uint8_t b;

    switch(ctx->state) {
    case afe_state_SOF:
        ctx->state = afe_state_LEN_LSB;
        *out = SOF_CHAR;
        ret = afeb_status_OUT_VALID;
        break;
    case afe_state_LEN_LSB:
        b = (0xFF & (ctx->len >> 0));

        if (write_out_byte(ctx, b, out)) {
            ctx->state = afe_state_LEN_MSB;
        }

        ret = afeb_status_OUT_VALID;
        break;
    case afe_state_LEN_MSB:
        b = (0xFF & (ctx->len >> 8));

        if (write_out_byte(ctx, b, out)) {
            if (ctx->len > 0) {
                /* Only go to the length state if there's data to be
                 * output. */
                ctx->state = afe_state_DATA;
            } else {
                /* If there's no data (this is an empty frame), then
                 * we can skip straight to EOF. */
                ctx->state = afe_state_EOF;
            }
        }

        ret = afeb_status_OUT_VALID;
        break;
    case afe_state_DATA:
        if (ctx->given_pos >= ctx->given_len) {
            ret = afeb_status_NEED_INPUT;
        } else {
            b = given_bytes[ctx->given_pos];

            if (write_out_byte(ctx, b, out)) {
                advance_pos(ctx);
            }

            if (ctx->pos >= ctx->len) {
                ctx->state = afe_state_EOF;
            }

            ret = afeb_status_OUT_VALID;
        }
        break;
    case afe_state_EOF:
        *out = EOF_CHAR;
        ctx->state = afe_state_DONE;
        ret = afeb_status_OUT_VALID;
        break;
    case afe_state_DONE:
        *out = 0;
        ret = afeb_status_DONE;
        break;
    case afe_state_UNINITIALIZED:
    default:
        assert(0);
        break;
    }

    return ret;
}

enum am_frame_encode_buffer_status am_frame_encode_buffer(struct am_frame_encode_ctx * const ctx,
                                                        uint8_t * const buffer,
                                                        size_t const bufsize,
                                                        size_t * const used) {
    for (*used = 0; *used < bufsize; (*used)++) {
        enum am_frame_encode_byte_status stat;

        stat = am_frame_encode_byte(ctx, &buffer[*used]);
        if (stat == afeb_status_OUT_VALID) {
            continue;
        } else if (stat == afeb_status_NEED_INPUT) {
            if (*used == 0) {
                /* This was the first loop, return _NEED_INPUT. */
                return afebu_status_NEED_INPUT;
            } else {
                /* We have some valid data in the buffer even though
                 * we need more input now, so report the output as
                 * valid and return. */
                return afebu_status_BUFFER_VALID;
            }
        } else if (stat == afeb_status_DONE) {
            if (*used == 0) {
                return afebu_status_DONE;
            } else {
                return afebu_status_BUFFER_VALID;
            }
        }
    }

    assert(*used > 0);

    /* We dropped out of the loop, so we must have filled our input
     * buffer before exhausing everything. */
    return afebu_status_BUFFER_FULL;
}


static bool ctx_is_initialized(struct am_frame_encode_ctx * ctx) {
    assert(ctx);

    switch(ctx->state) {
    case afe_state_UNINITIALIZED:
        return false;
    case afe_state_SOF:
    case afe_state_LEN_LSB:
    case afe_state_LEN_MSB:
    case afe_state_DATA:
    case afe_state_EOF:
    case afe_state_DONE:
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

static void advance_pos(struct am_frame_encode_ctx * ctx) {
    assert(ctx->pos < ctx->len);
    assert(ctx->given_pos < ctx->given_len);

    ctx->pos++;
    ctx->given_pos++;
}

static bool write_out_byte(struct am_frame_encode_ctx * ctx, uint8_t b, uint8_t * out) {
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

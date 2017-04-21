#include "carbon_frame_decode.h"
#include "carbon_frame_common.h"

#include <assert.h>

#define MSB_MASK (0x000000FF)
#define LSB_MASK (0x0000FF00)

/* When decoding, the maximum size of any input message is determined
 * as follows:
 *
 *   SOF     - 1
 *   ESCLSB  - 2
 *   ESCMSB  - 2
 *   ESCDATA - (2^16 - 1) * 2 = 131070
 *   EOF     - 1
 *
 * This is 131076 bytes. */
#define MAX_DECODE_INPUT_SIZE (1 + 2 + 2 + (0xFFFF * 2) + 1)

static bool is_initialized(struct carbon_frame_decode_ctx * const ctx);
static bool read_in_escaped_byte(struct carbon_frame_decode_ctx * const ctx, uint8_t in_b, uint8_t * out_b);
static bool next_byte(struct carbon_frame_decode_ctx * const ctx, uint8_t * b);
static void advance_give(struct carbon_frame_decode_ctx * const ctx);
static void set_error(struct carbon_frame_decode_ctx * const ctx, enum carbon_frame_decode_error e);
enum carbon_frame_decode_byte_status done_value(struct carbon_frame_decode_ctx * const ctx);

void carbon_frame_decode_init(struct carbon_frame_decode_ctx * const ctx) {
    *ctx = (struct carbon_frame_decode_ctx) {
        .state = carbon_frame_decode_state_SOF,
    };
}


enum carbon_frame_decode_give_status carbon_frame_decode_give(struct carbon_frame_decode_ctx * const ctx,
                                                              void const * const input,
                                                              size_t const len) {
    assert(is_initialized(ctx));

    if (ctx->given_pos < ctx->given_len) {
        return carbon_frame_decode_give_BUSY;
    }

    assert(ctx->pos + len <= MAX_DECODE_INPUT_SIZE);

    ctx->given = input;
    ctx->given_len = len;
    ctx->given_pos = 0;

    return carbon_frame_decode_give_OK;
}

enum carbon_frame_decode_byte_status carbon_frame_decode_byte(struct carbon_frame_decode_ctx * const ctx,
                                                              uint8_t * const byte) {
    assert(is_initialized(ctx));

    if (ctx->state == carbon_frame_decode_state_DONE) {
        return done_value(ctx);
    }

    while (true) {
        uint8_t b;
        uint8_t e;

        /* This retrieves the next given byte, storing it in `b`. It
         * also advances the position in the given data. */
        if (!next_byte(ctx, &b)) {
            /* The given data has no more bytes available. */
            return carbon_frame_decode_byte_NEED_INPUT;
        }

        /* If the byte is a SOF character, reset the state machine. */
        if (SOF_CHAR == b) {
            size_t const pos = ctx->pos;

            ctx->state = carbon_frame_decode_state_SOF;
            ctx->pos = 0;
            ctx->len = 0;

            if (pos > 0) {
                /* If the position indicates that we had already
                 * parsed out some bytes, indicate that those bytes
                 * are no longer part of this frame. */
                return carbon_frame_decode_byte_RESTART_FRAME;
            }
        }

        /* Advance the give position to the next byte for the next
         * time through this path. */
        advance_give(ctx);

        /* If the byte is an EOF character, force the state machine to
         * the EOF state. */
        if (EOF_CHAR == b) {
            ctx->state = carbon_frame_decode_state_EOF;
        }

        switch (ctx->state) {
        case carbon_frame_decode_state_SOF:
            if (SOF_CHAR == b) {
                /* Only advance from the SOF state if we actually see
                 * a SOF character. */
                ctx->state = carbon_frame_decode_state_LEN_LSB;
            }
            break;
        case carbon_frame_decode_state_LEN_LSB:
            assert((ctx->len & ~LSB_MASK) == 0);

            if (read_in_escaped_byte(ctx, b, &e)) {
                /* When we successfully read in an escaped byte, store
                 * it as the LSB and jump to the MSB state. */
                ctx->len = e;
                ctx->state = carbon_frame_decode_state_LEN_MSB;
            }
            break;
        case carbon_frame_decode_state_LEN_MSB:
            assert((ctx->len & ~MSB_MASK) == 0);

            if (read_in_escaped_byte(ctx, b, &e)) {
                /* When we successfully read in an escaped byte, store
                 * it as the MSB. If the parsed length is > 0, then
                 * jump to the DATA state. Otherwise advance directly
                 * to EOF. */
                ctx->len |= e << 8;
                ctx->state = carbon_frame_decode_state_DATA;

                if (0 == ctx->len) {
                    ctx->state = carbon_frame_decode_state_EOF;
                } else {
                    ctx->state = carbon_frame_decode_state_DATA;
                }
            }
            break;
        case carbon_frame_decode_state_DATA:
            if (read_in_escaped_byte(ctx, b, &e)) {
                /* When we have an escaped byte, store it and advance
                 * the frame position. */
                *byte = e;
                ctx->pos++;

                if (ctx->pos >= ctx->len) {
                    /* If we've reached the end of the input, advance
                     * to EOF. */
                    ctx->state = carbon_frame_decode_state_EOF;
                }

                return carbon_frame_decode_byte_OUT_VALID;
            }
            break;
        case carbon_frame_decode_state_EOF:
            /* Scan for EOF. Once we find it, we decide if we're in an
             * error condition or not and return DONE. */

            if (EOF_CHAR == b) {
                ctx->state = carbon_frame_decode_state_DONE;

                /* We found the EOF. If we collected at least as many
                 * bytes as we were expecting. We don't need to record
                 * an undersized frame error. */
                if (ctx->pos < ctx->len) {
                    /* The position indicates we didn't collect as
                     * much data as we expected before the EOF
                     * arrived. Record an undersized frame error. */
                    set_error(ctx, carbon_frame_decode_error_UNDERSIZED_FRAME);
                }

                return done_value(ctx);
            } else {
                /* We expected an EOF, but something else was there
                 * instead. Record an oversized frame error. */
                set_error(ctx, carbon_frame_decode_error_OVERSIZED_FRAME);
            }
            break;
        default:
        case carbon_frame_decode_state_UNINITIALIZED:
            assert(0);
            break;
        }
    }
}

enum carbon_frame_decode_buffer_status carbon_frame_decode_buffer(struct carbon_frame_decode_ctx * ctx,
                                                                  uint8_t * const buffer,
                                                                  size_t const bufsize,
                                                                  size_t * const used) {
    for (*used = 0; *used < bufsize; (*used)++) {
        enum carbon_frame_decode_byte_status stat;

        stat = carbon_frame_decode_byte(ctx, &buffer[*used]);
        if (stat == carbon_frame_decode_byte_OUT_VALID) {
            continue;
        } else if (stat == carbon_frame_decode_byte_NEED_INPUT) {
            return (*used > 0
                    ? carbon_frame_decode_buffer_BUFFER_VALID
                    : carbon_frame_decode_buffer_NEED_INPUT);
        } else if (stat == carbon_frame_decode_byte_RESTART_FRAME) {
            return carbon_frame_decode_buffer_RESTART_FRAME;
        } else if (stat == carbon_frame_decode_byte_DONE) {
            return (*used > 0
                    ? carbon_frame_decode_buffer_BUFFER_VALID
                    : carbon_frame_decode_buffer_DONE);
        } else if (stat == carbon_frame_decode_byte_DONE_WITH_ERROR) {
            return (*used > 0
                    ? carbon_frame_decode_buffer_BUFFER_VALID
                    : carbon_frame_decode_buffer_DONE_WITH_ERROR);
        } else {
            assert(0);
        }
    }

    assert(*used > 0);

    return carbon_frame_decode_buffer_BUFFER_FULL;
}


enum carbon_frame_decode_error carbon_frame_decode_get_error(struct carbon_frame_decode_ctx * ctx) {
    return ctx->error;
}

enum carbon_frame_decode_reset_status carbon_frame_decode_reset(struct carbon_frame_decode_ctx * const ctx) {
    switch (ctx->state) {
    case carbon_frame_decode_state_LEN_LSB:
    case carbon_frame_decode_state_LEN_MSB:
    case carbon_frame_decode_state_DATA:
    case carbon_frame_decode_state_EOF:
        return carbon_frame_decode_reset_NOT_DONE;
    case carbon_frame_decode_state_DONE:
    case carbon_frame_decode_state_UNINITIALIZED:
    default:
        break;
    }

    *ctx = (struct carbon_frame_decode_ctx) {
        .state = carbon_frame_decode_state_SOF,
        .pos = 0,
        .len = 0,
        .need_escape = false,
        .error = carbon_frame_decode_error_NONE,

        /* Copy these over. They are preserved. */
        .given = ctx->given,
        .given_len = ctx->given_len,
        .given_pos = ctx->given_pos,
    };

    return carbon_frame_decode_reset_OK;
}

size_t carbon_frame_decode_remaining(struct carbon_frame_decode_ctx * ctx) {
    assert(ctx);

    return (ctx->given_len < ctx->given_pos
            ? 0
            : ctx->given_len - ctx->given_pos);
}

static bool is_initialized(struct carbon_frame_decode_ctx * const ctx) {
    switch(ctx->state) {
    case carbon_frame_decode_state_SOF:
    case carbon_frame_decode_state_LEN_LSB:
    case carbon_frame_decode_state_LEN_MSB:
    case carbon_frame_decode_state_DATA:
    case carbon_frame_decode_state_EOF:
    case carbon_frame_decode_state_DONE:
        return true;
    default:
        return false;
    }
}

static bool read_in_escaped_byte(struct carbon_frame_decode_ctx * const ctx, uint8_t in_b, uint8_t * out_b) {
    /* Invalid escaped bytes are set to 0 and an error is recorded. */
    if (ctx->need_escape) {
        switch (in_b) {
        case SOF_ESC:
            *out_b = SOF_CHAR;
            break;
        case ESC_ESC:
            *out_b = ESC_CHAR;
            break;
        case EOF_ESC:
            *out_b = EOF_CHAR;
            break;
        default:
            set_error(ctx, carbon_frame_decode_error_BAD_ESCAPE);
            *out_b = 0x00;
            break;
        }

        ctx->need_escape = false;

        return true;
    } else {
        if (ESC_CHAR == in_b) {
            ctx->need_escape = true;
            return false;
        } else {
            *out_b = in_b;
            return true;
        }
    }
}

static bool next_byte(struct carbon_frame_decode_ctx * const ctx, uint8_t * const b) {
    if (ctx->given_pos >= ctx->given_len) {
        return false;
    }

    uint8_t const * bytes = ctx->given;
    *b = bytes[ctx->given_pos];

    return true;
}

static void advance_give(struct carbon_frame_decode_ctx * const ctx) {
    assert(ctx->given_pos < ctx->given_len);
    ctx->given_pos++;
}

static void set_error(struct carbon_frame_decode_ctx * const ctx, enum carbon_frame_decode_error e) {
    if (ctx->error == carbon_frame_decode_error_NONE) {
        ctx->error = e;
    }
}

enum carbon_frame_decode_byte_status done_value(struct carbon_frame_decode_ctx * const ctx) {
    if (ctx->error == carbon_frame_decode_error_NONE) {
        return carbon_frame_decode_byte_DONE;
    } else {
        return carbon_frame_decode_byte_DONE_WITH_ERROR;
    }
}

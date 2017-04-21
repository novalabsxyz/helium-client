#include "cauterize.h"
#include "cauterize_util.h"
#include "cauterize_encode.h"
#include "cauterize_decode.h"
#include "cauterize_size.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>

#define S enum caut_status
#define SD struct schema_descriptor
#define TD struct type_descriptor
#define TEI struct type_encode_iterator
#define TDI struct type_decode_iterator
#define TSI struct type_size_iterator
#define SEI struct schema_encode_iterator
#define SDI struct schema_decode_iterator
#define SSI struct schema_size_iterator

#define BYTE_AT_IX_OR_NULL(BUF, BUFLEN, IX)    \
    (IX < BUFLEN ? &(((uint8_t *)BUF)[IX]) : NULL)

/*
 * The following two functions use infinite loops. They need to
 * guarantee that they makes progress or that it alter the stack in a
 * meaningful way. We use an infinite loop because results can still
 * be produced even after all input has been consumed. This is because
 * the last byte can only trigger a single pop off the stack. We loop
 * with a NULL byte after the last data byte has been consumed so that
 * the nested types at the end that do not require more data can be
 * popped. Once the all the frames have been popped or the NULL byte
 * is rejected with _need_byte, then execution leaves the loop.
 *
 * As long as the call to caut_enc_get_byte can never accept a NULL
 * and return a busy status at the same time and the pushed indication
 * from _get_byte is true the loop will terminate.
 */
S caut_enc_get(SEI * ei, void * buf, size_t buf_size, size_t * enc_bytes) {
    S ret = caut_status_ok_busy;

    *enc_bytes = 0;

    DEBUG_CHAR('(');

    size_t * i = enc_bytes;
    while (true) {
        bool progress = false;
        uint8_t * const byte = BYTE_AT_IX_OR_NULL(buf, buf_size, *i);
        S const s = caut_enc_get_byte(ei, byte, &progress);

        if (progress) {
            *i += 1;
        }

        if (caut_status_ok_busy == s) {
            assert(true == progress);
            assert(NULL != byte);
            DEBUG_CHAR('.');
        } else if (caut_status_ok_pop == s) {
            DEBUG_CHAR(')');
            if (ei->iter_top == 0) {
                ret = caut_status_ok;
                ei->iter_top = SIZE_MAX;
                break;
            } else {
                ei->iter_top -= 1;
            }
        } else if (caut_status_ok_pushed == s) {
            DEBUG_CHAR('(');
        } else if (caut_status_err_need_byte == s) {
            DEBUG_CHAR('#');
            ret = caut_status_ok_busy;
            break;
        } else {
            assert(s >= ERRS_START);
            DEBUG_CHAR('!');
            ret = s;
            break;
        }
    }

    assert(*enc_bytes <= buf_size);

    return ret;
}

S caut_dec_put(SDI * di, void const * buf, size_t buf_size, size_t * dec_bytes) {
    S ret = caut_status_ok_busy;

    *dec_bytes = 0;

    DEBUG_CHAR('(');

    size_t * const i = dec_bytes;

    while (true) {
        bool progress = false;
        uint8_t * const byte = BYTE_AT_IX_OR_NULL(buf, buf_size, *i);
        S const s = caut_dec_put_byte(di, byte, &progress);

        if (progress) {
            *i += 1;
        }

        if (caut_status_ok_busy == s) {
            assert(true == progress);
            assert(NULL != byte);
            DEBUG_CHAR_IF(progress, '.');
        } else if (caut_status_ok_pop == s) {
            DEBUG_CHAR_IF(progress, '.');
            DEBUG_CHAR(')');
            if (di->iter_top == 0) {
                ret = caut_status_ok;
                di->iter_top = SIZE_MAX;
                break;
            } else {
                di->iter_top -= 1;
            }
        } else if (caut_status_ok_pushed == s) {
            assert(false == progress);
            DEBUG_CHAR('(');
        } else if (caut_status_err_need_byte == s) {
            DEBUG_CHAR('#');
            ret = caut_status_ok_busy;
            break;
        } else {
            assert(s >= ERRS_START);
            DEBUG_CHAR('!');
            ret = s;
            break;
        }
    }

    assert(*dec_bytes <= buf_size);

    return ret;
}

S caut_size_get(SSI * si, size_t * size) {
    S ret = caut_status_err_UNIMPLEMENTED;
    *size = 0;

    while (true) {
        S const s = caut_enc_get_size(si, size);

        if (caut_status_ok_pop == s) {
            // Pull the iterator off the stack after a pop.
            if (si->iter_top == 0) {
                ret = caut_status_ok;
                si->iter_top = SIZE_MAX;
                break;
            } else {
                si->iter_top -= 1;
            }
        } else if (caut_status_ok_pushed == s) {
            // We don't need to do anything after a push.
        } else if (caut_status_ok == s) {
            // We're done.
            ret = caut_status_ok;
            break;
        } else {
            // These should be impossible.
            assert(caut_status_ok_busy != s);
            assert(caut_status_err_need_byte != s);

            // We're done, but not good.
            ret = s;
            break;
        }
    }

    return ret;
}

S schema_encode_iterator_init(SEI * si, SD const * sd, TEI * ti, size_t ti_count, int type_id, void const * src_type) {
    RE(id_check(sd, type_id));

    *si = (SEI) {
        .desc = sd,
        .iters = ti,
        .iter_count = ti_count,
        .iter_top = 0,
        .src_type = src_type
    };

    RE(type_encode_iterator_init(sd, ti, type_id, src_type));

    return caut_status_ok;
}

S schema_decode_iterator_init(SDI * si, SD const * sd, TDI * ti, size_t ti_count, int type_id, void * dst_type) {
    RE(id_check(sd, type_id));

    *si = (SDI) {
        .desc = sd,
        .iters = ti,
        .iter_count = ti_count,
        .iter_top = 0,
        .dst_type = dst_type,
    };

    // Initialize the object memory to 0. The decoder assumes that it
    // only has to overlay bytes on top of a 0'ed out object. If this
    // is not here, then situations where tags on the host are wider
    // than the encoded tags may result in garbage values stored in
    // the host tag.
    TD const * td = NULL;
    RE(get_type_desc(sd, type_id, &td));
    memset(dst_type, 0, td->obj_size);

    RE(type_decode_iterator_init(sd, ti, type_id, dst_type));

    return caut_status_ok;
}

S schema_size_iterator_init(SSI * si, SD const * sd, TSI * ti, size_t ti_count, int type_id, void const * src_type) {
    RE(id_check(sd, type_id));

    *si = (SSI) {
        .desc = sd,
        .iters = ti,
        .iter_count = ti_count,
        .iter_top = 0,
        .src_type = src_type
    };

    RE(type_size_iterator_init(sd, ti, type_id, src_type));

    return caut_status_ok;
}

#include "cauterize_util.h"

#include <assert.h>
#include <string.h>

size_t caut_tag_size(enum caut_tag tag) {
    switch (tag) {
    case caut_tag_8: return 1;
    case caut_tag_16: return 2;
    case caut_tag_32: return 4;
    case caut_tag_64: return 8;
    default:
        assert(false);
        return 0;
    }
}

void signed_convert(void const * in, size_t in_size, void * out, size_t out_size) {
    // Assumes in and out are both properly aligned.

    assert(in_size == 1 || in_size == 2 || in_size == 4 || in_size == 8);
    assert(out_size == 1 || out_size == 2 || out_size == 4 || out_size == 8);

    int64_t word = 0;

    switch (in_size) {
    case sizeof(int8_t):  word = *(int8_t  *)in; break;
    case sizeof(int16_t): word = *(int16_t *)in; break;
    case sizeof(int32_t): word = *(int32_t *)in; break;
    case sizeof(int64_t): word = *(int64_t *)in; break;
    default: assert(false);
    }

    switch(out_size) {
    case sizeof(int8_t):
        assert(INT8_MIN <= word && word <= INT8_MAX);
        *((int8_t  *)out) = (int8_t )word;
        break;
    case sizeof(int16_t):
        assert(INT16_MIN <= word && word <= INT16_MAX);
        *((int16_t *)out) = (int16_t)word;
        break;
    case sizeof(int32_t):
        assert(INT32_MIN <= word && word <= INT32_MAX);
        *((int32_t *)out) = (int32_t)word;
        break;
    case sizeof(int64_t):
        assert(INT64_MIN <= word && word <= INT64_MAX);
        *((int64_t *)out) = (int64_t)word;
        break;
    default:
        assert(false);
    }
}

uint64_t mask_with_width(size_t width) {
    assert(0 < width && width < 65);

    uint64_t ret = 0;

    for (size_t i = 0; i < width; i++) {
        ret |= 1 << i;
    }

    return ret;
}

uint64_t flag_set_at(size_t width) {
    assert(width < 64);

    uint64_t ret = 1;
    ret <<= width;

    return ret;
}

bool range_convert(void const * type, struct caut_range const * desc, struct range_value * val) {
    if (desc->offset < 0) {
        val->is_signed = true;

        int64_t const rmin = desc->offset;
        int64_t const rmax = desc->offset + desc->length;

        signed_convert(type, desc->word_size, &val->u.s, sizeof(val->u.s));

        if (val->u.s < rmin || rmax < val->u.s) {
            return false;
        } else {
            val->u.s -= desc->offset;
        }

    } else {
        val->is_signed = false;

        uint64_t const rmin = desc->offset;
        uint64_t const rmax = desc->offset + desc->length;

        memcpy(&val->u.u, type, desc->word_size);

        if (val->u.u < rmin || rmax < val->u.u) {
            return false;
        } else {
            val->u.u -= (uint64_t)desc->offset;
        }
    }

    return true;
}

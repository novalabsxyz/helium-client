#ifndef CAUTERIZE_UTIL_H
#define CAUTERIZE_UTIL_H

#include "cauterize_types.h"
#include "cauterize_descriptors.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// return error if error
#define RE(EXP) \
    do { \
        S s; if (caut_status_ok != (s = EXP)) {  \
            return s; \
        } \
    } while(0)

#define DEBUG_QUIET 1

#if defined(NDEBUG) || defined(DEBUG_QUIET)
#define DEBUG_CHAR(c)
#define DEBUG_CHAR_IF(cond, c)
#define DEBUG_FMT(fmt, ...)
#else
#define DEBUG_CHAR(c) do { fputc(c, stderr); fflush(stderr); } while (0)
#define DEBUG_CHAR_IF(cond, c) do { if (cond) { DEBUG_CHAR(c); } } while (0)
#define DEBUG_FMT(fmt, ...) do { fprintf(stderr, fmt, __VA_ARGS__); fflush(stderr); } while (0)
#endif

#define STATE_CHECK(cond) do { if (!(cond)) { return caut_status_err_bad_state; } } while (0)

struct range_value {
    bool is_signed;
    union {
        uint64_t u;
        int64_t s;
        uint8_t b[sizeof(uint64_t)];
    } u;
};

size_t caut_tag_size(enum caut_tag tag);
void signed_convert(void const * in, size_t in_size, void * out, size_t out_size);
uint64_t mask_with_width(size_t width);
uint64_t flag_set_at(size_t width);
bool range_convert(void const * type, struct caut_range const * desc, struct range_value * val);

#endif /* CAUTERIZE_UTIL_H */

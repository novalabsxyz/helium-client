#include "cauterize_descriptors.h"

#include <stdlib.h>

#define S enum caut_status
#define SD struct schema_descriptor
#define TD struct type_descriptor

#define U8_ID (-1)
#define U16_ID (-2)
#define U32_ID (-3)
#define U64_ID (-4)
#define S8_ID (-5)
#define S16_ID (-6)
#define S32_ID (-7)
#define S64_ID (-8)
#define F32_ID (-9)
#define F64_ID (-10)
#define BOOL_ID (-11)

#define PROTO_DESC(ID, SIZE) \
    { \
        .type_id = ID, \
        .prototype_tag = caut_proto_primitive, \
        .prototype.c_primitive = { .word_size = SIZE }, \
    }

int const min_prim_id = -11; // bool

struct type_descriptor const primitive_descriptors[CAUT_PRIMITIVE_COUNT] = {
    PROTO_DESC(U8_ID, 1),
    PROTO_DESC(U16_ID, 2),
    PROTO_DESC(U32_ID, 4),
    PROTO_DESC(U64_ID, 8),
    PROTO_DESC(S8_ID, 1),
    PROTO_DESC(S16_ID, 2),
    PROTO_DESC(S32_ID, 4),
    PROTO_DESC(S64_ID, 8),
    PROTO_DESC(F32_ID, 4),
    PROTO_DESC(F64_ID, 8),
    PROTO_DESC(BOOL_ID, 1),
};

S id_check(SD const * sd_set, int type_id) {
    if ((min_prim_id <= type_id) || ((size_t)type_id <= sd_set->type_count)) {
        return caut_status_ok;
    } else {
        return caut_status_err_invalid_type_id;
    }
}

S get_type_desc(SD const * sd_set, int type_id, TD const ** td_out) {
    if (0 > type_id) {
        int prim_idx = abs(type_id) - 1;
        *td_out = &primitive_descriptors[prim_idx];
    } else if ((size_t)type_id < sd_set->type_count) {
        *td_out = &sd_set->types[type_id];
    }

    return caut_status_ok;
}

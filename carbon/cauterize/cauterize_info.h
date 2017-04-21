#ifndef CAUTERIZE_INFO
#define CAUTERIZE_INFO

#include <stddef.h>
#include <stdint.h>

#include "cauterize_types.h"

struct caut_field_info {
    char const * name;
    size_t field_index;
};

struct info_enumeration {
    size_t field_count;
    struct caut_field_info const * fields;
};

struct info_record {
    size_t field_count;
    struct caut_field_info const * fields;
};

struct info_union {
    size_t field_count;
    struct caut_field_info const * fields;
};

struct info_combination {
    size_t field_count;
    struct caut_field_info const * fields;
};

union info_prototype {
    struct info_enumeration i_enumeration;
    struct info_record i_record;
    struct info_union i_union;
    struct info_combination i_combination;
};

struct type_info {
    char const * name;
    uint8_t fingerprint[20];
    size_t min_size;
    size_t max_size;
    size_t depth;
    enum caut_proto_tag prototype_tag;
    union info_prototype prototype;
};

struct schema_info {
    char const * name;
    uint8_t fingerprint[20];
    size_t min_size;
    size_t max_size;
    size_t depth;
    size_t type_count;
    struct type_info const * types;
};

#endif /* CAUTERIZE_INFO */

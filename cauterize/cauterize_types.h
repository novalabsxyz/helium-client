#ifndef CAUTERIZE_TYPES_H
#define CAUTERIZE_TYPES_H

#include <stdint.h>
#include <stddef.h>

enum primitive_type_id {
  primitive_type_id_bool = -11,
  primitive_type_id_f64 = -10,
  primitive_type_id_f32 = -9,
  primitive_type_id_s64 = -8,
  primitive_type_id_s32 = -7,
  primitive_type_id_s16 = -6,
  primitive_type_id_s8 = -5,
  primitive_type_id_u64 = -4,
  primitive_type_id_u32 = -3,
  primitive_type_id_u16 = -2,
  primitive_type_id_u8 = -1,
};

enum caut_proto_tag {
    caut_proto_primitive,
    caut_proto_synonym,
    caut_proto_range,
    caut_proto_enumeration,
    caut_proto_array,
    caut_proto_vector,
    caut_proto_record,
    caut_proto_combination,
    caut_proto_union,
};

enum caut_tag {
    caut_tag_8,
    caut_tag_16,
    caut_tag_32,
    caut_tag_64,
};

typedef uint8_t caut_tag8_t;
typedef uint16_t caut_tag16_t;
typedef uint32_t caut_tag32_t;
typedef uint64_t caut_tag64_t;

#define ERRS_START (1000)

enum caut_status {
    caut_status_ok = 0,
    caut_status_ok_busy,
    caut_status_ok_pop,
    caut_status_ok_pushed,
    caut_status_err_bad_state = ERRS_START,
    caut_status_err_need_byte,
    caut_status_err_invalid_type_id,
    caut_status_err_iter_stack_would_overflow,
    caut_status_err_invalid_range,
    caut_status_err_invalid_enum,
    caut_status_err_invalid_vector,
    caut_status_err_invalid_record,
    caut_status_err_invalid_combination,
    caut_status_err_invalid_union,
    caut_status_err_UNIMPLEMENTED,
};

#endif /* CAUTERIZE_TYPES_H */

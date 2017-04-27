#include "cauterize.h"
#include "cauterize_util.h"

#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define S enum caut_status
#define SD struct schema_descriptor
#define TD struct type_descriptor
#define TEI struct type_encode_iterator
#define TDI struct type_decode_iterator
#define SEI struct schema_encode_iterator
#define SDI struct schema_decode_iterator

static S caut_dec_put_byte_primitive(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte);
static S caut_dec_put_byte_synonym(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte);
static S caut_dec_put_byte_range(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte);
static S caut_dec_put_byte_enumeration(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte);
static S caut_dec_put_byte_array(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte);
static S caut_dec_put_byte_vector(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte);
static S caut_dec_put_byte_record(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte);
static S caut_dec_put_byte_combination(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte);
static S caut_dec_put_byte_union(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte);

S caut_dec_put_byte(SDI * di, uint8_t const * byte, bool * progress) {
    /* The parameter `byte` can be NULL. If it's not null, copy it
     * into the decoding structure. If it is null, pushing and popping
     * of the stack are allowed, but nothing else. If a byte is needed
     * to make progress, `caut_status_err_need_byte` must be returned
     * until a byte is provided. */

    TD const * td = NULL;
    TDI * ti = NULL;
    *progress = false;

    RE(get_type_dec_iter(di, &ti));
    RE(get_type_desc(di->desc, ti->type_id, &td));

    switch (td->prototype_tag) {
    case caut_proto_primitive:
        return caut_dec_put_byte_primitive(di, td, ti, progress, byte);
    case caut_proto_synonym:
        return caut_dec_put_byte_synonym(di, td, ti, progress, byte);
    case caut_proto_range:
        return caut_dec_put_byte_range(di, td, ti, progress, byte);
    case caut_proto_enumeration:
        return caut_dec_put_byte_enumeration(di, td, ti, progress, byte);
    case caut_proto_array:
        return caut_dec_put_byte_array(di, td, ti, progress, byte);
    case caut_proto_vector:
        return caut_dec_put_byte_vector(di, td, ti, progress, byte);
    case caut_proto_record:
        return caut_dec_put_byte_record(di, td, ti, progress, byte);
    case caut_proto_combination:
        return caut_dec_put_byte_combination(di, td, ti, progress, byte);
    case caut_proto_union:
        return caut_dec_put_byte_union(di, td, ti, progress, byte);
    default:
        return caut_status_err_UNIMPLEMENTED;
    }
}

static S caut_dec_put_byte_primitive(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte) {
    struct iter_primitive * iter = &ti->prototype.c_primitive;
    struct caut_primitive const * const desc = &td->prototype.c_primitive;
    uint8_t * const type_bytes = ti->type;

    (void) di;

    STATE_CHECK(iter->word_position < desc->word_size);

    if (NULL == byte) {
        return caut_status_err_need_byte;
    }

    type_bytes[iter->word_position] = *byte;
    iter->word_position += 1;

    *progress = true;

    if (iter->word_position < desc->word_size) {
        return caut_status_ok_busy;
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_dec_put_byte_synonym(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte) {
    struct iter_synonym * const iter = &ti->prototype.c_synonym;
    struct caut_synonym const * const desc = &td->prototype.c_synonym;

    (void)byte;

    *progress = false;

    if (iter->done == false) {
        RE(push_type_dec_iter(di, desc->ref_id, ti->type));
        iter->done = true;

        return caut_status_ok_pushed;
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_dec_put_byte_range(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte) {
    struct iter_range * const iter = &ti->prototype.c_range;
    struct caut_range const * const desc = &td->prototype.c_range;

    (void) di;

    assert(iter->tag_iter.tag_position < caut_tag_size(desc->tag));

    uint8_t * b = (uint8_t *)&iter->tag_iter.tag_buffer;

    if (NULL == byte) {
        return caut_status_err_need_byte;
    } else {
        *progress = true;
        b[iter->tag_iter.tag_position] = *byte;
        iter->tag_iter.tag_position += 1;
    }

    if (iter->tag_iter.tag_position >= caut_tag_size(desc->tag)) {
        if (desc->offset < 0) {
            int64_t const rmin = desc->offset;
            int64_t const rmax = desc->offset + desc->length;
            int64_t s = 0;

            signed_convert(
                &iter->tag_iter.tag_buffer, caut_tag_size(desc->tag),
                &s, sizeof(s));

            s += desc->offset;

            if (s < rmin || rmax < s) {
                return caut_status_err_invalid_range;
            } else {
                signed_convert(
                    &s, sizeof(s),
                    ti->type, desc->word_size);

                return caut_status_ok_pop;
            }
        } else {
            uint64_t const rmin = desc->offset;
            uint64_t const rmax = desc->offset + desc->length;

            uint64_t u = 0;
            memcpy(&u, &iter->tag_iter.tag_buffer, caut_tag_size(desc->tag));

            u += desc->offset;

            if (u < rmin || rmax < u) {
                return caut_status_err_invalid_range;
            } else {
                memcpy(ti->type, &u, desc->word_size);

                return caut_status_ok_pop;
            }
        }
    } else {
        return caut_status_ok_busy;
    }
}

static S caut_dec_put_byte_enumeration(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte) {
    struct iter_enumeration * const iter = &ti->prototype.c_enumeration;
    struct caut_enumeration const * const desc = &td->prototype.c_enumeration;
    uint8_t * const b = (uint8_t *)&iter->tag_iter.tag_buffer;

    (void) di;

    assert(iter->tag_iter.tag_position < caut_tag_size(desc->tag));

    if (NULL == byte) {
        return caut_status_err_need_byte;
    }

    *progress = true;
    b[iter->tag_iter.tag_position] = *byte;
    iter->tag_iter.tag_position += 1;

    if (iter->tag_iter.tag_position >= caut_tag_size(desc->tag)) {
        if (iter->tag_iter.tag_buffer >= desc->length) {
            return caut_status_err_invalid_enum;
        } else {
            memcpy(ti->type, &iter->tag_iter.tag_buffer, caut_tag_size(desc->tag));
            return caut_status_ok_pop;
        }
    } else {
        return caut_status_ok_busy;
    }
}

static S caut_dec_put_byte_array(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte) {
    struct iter_array * const iter = &ti->prototype.c_array;
    struct caut_array const * const desc = &td->prototype.c_array;

    (void) byte;

    *progress = false;

    if (iter->elem_position < desc->length) {
        void * const base =
            (void *)(
                ((uintptr_t)ti->type) +
                (desc->elem_span * iter->elem_position));
        RE(push_type_dec_iter(di, desc->ref_id, base));
        iter->elem_position += 1;
        return caut_status_ok_pushed;
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_dec_put_byte_vector(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte) {
    struct iter_vector * const iter = &ti->prototype.c_vector;
    struct caut_vector const * const desc = &td->prototype.c_vector;
    uint8_t * const b = (uint8_t *)&iter->tag_iter.tag_buffer;
    uint8_t * const t = (uint8_t *)ti->type;

    *progress = false;

    if (iter->tag_iter.tag_position < caut_tag_size(desc->tag)) {
        // Copy the byte into both a tag buffer and the final tag
        // position. It goes in both places so that we can length
        // check using the buffer as a u64 and have the value in place
        // in the final tag memory.

        if (NULL == byte) {
            return caut_status_err_need_byte;
        } else {
            b[iter->tag_iter.tag_position] = *byte;
            t[iter->tag_iter.tag_position] = *byte;

            *progress = true;
            iter->tag_iter.tag_position += 1;

            return caut_status_ok_busy;
        }
    } else if (iter->tag_iter.tag_buffer > desc->max_length) {
        return caut_status_err_invalid_vector;
    } else if (iter->elem_position < iter->tag_iter.tag_buffer) {
        void * const base =
            (void *)(
                ((uintptr_t)ti->type) +
                desc->elem_offset +
                (desc->elem_span * iter->elem_position));

        RE(push_type_dec_iter(di, desc->ref_id, base));
        iter->elem_position += 1;

        return caut_status_ok_pushed;
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_dec_put_byte_record(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte) {
    struct iter_record * const iter = &ti->prototype.c_record;
    struct caut_record const * const desc = &td->prototype.c_record;

    (void) byte;

    *progress = false;

    if (iter->field_position < desc->field_count) {
        struct caut_field const * const field = &desc->fields[iter->field_position];
        void * const base = (void *)(((uintptr_t)ti->type) + field->offset);

        if (field->data == false) {
            return caut_status_err_invalid_record;
        } else {
            RE(push_type_dec_iter(di, field->ref_id, base));
            iter->field_position += 1;
        }

        return caut_status_ok_pushed;

    } else {
        return caut_status_ok_pop;
    }
}

static S caut_dec_put_byte_combination(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte) {
    struct iter_combination * const iter = &ti->prototype.c_combination;
    struct caut_combination const * const desc = &td->prototype.c_combination;
    uint8_t * const b = (uint8_t *)&iter->tag_iter.tag_buffer;
    uint8_t * const t = (uint8_t *)ti->type;

    if (iter->tag_iter.tag_position < caut_tag_size(desc->tag)) {
        if (NULL == byte) {
            return caut_status_err_need_byte;
        }

        *progress = true;

        // still accumulating tag
        b[iter->tag_iter.tag_position] = *byte;
        t[iter->tag_iter.tag_position] = *byte;
        iter->tag_iter.tag_position += 1;

        return caut_status_ok_busy;
    } else {
        uint64_t const mask = mask_with_width(desc->field_count);
        if (iter->tag_iter.tag_buffer > mask) {
            return caut_status_err_invalid_combination;
        }

        while (iter->field_position < desc->field_count) {
            uint64_t const field_flag = flag_set_at(iter->field_position);

            if (0 == (field_flag & iter->tag_iter.tag_buffer)) {
                iter->field_position += 1;
                continue;
            } else {
                struct caut_field const * const field = &desc->fields[iter->field_position];
                void * const base = (void *)(((uintptr_t)ti->type) + field->offset);

                iter->field_position += 1;

                if (field->data) {
                    RE(push_type_dec_iter(di, field->ref_id, base));
                    return caut_status_ok_pushed;
                } else {
                    continue;
                }
            }
        }

        return caut_status_ok_pop;
    }
}

static S caut_dec_put_byte_union(SDI * di, TD const * td, TDI * ti, bool * progress, uint8_t const * byte) {
    struct iter_union * const iter = &ti->prototype.c_union;
    struct caut_union const * const desc = &td->prototype.c_union;
    uint8_t * const b = (uint8_t *)&iter->tag_iter.tag_buffer;
    uint8_t * const t = (uint8_t *)ti->type;

    if (iter->tag_iter.tag_position < caut_tag_size(desc->tag)) {
        if (NULL == byte) {
            return caut_status_err_need_byte;
        }

        *progress = true;

        // still accumulating tag
        b[iter->tag_iter.tag_position] = *byte;
        t[iter->tag_iter.tag_position] = *byte;
        iter->tag_iter.tag_position += 1;

        return caut_status_ok_busy;
    } else {
        struct caut_field const * const field = &desc->fields[iter->tag_iter.tag_buffer];
        void * const base = (void *)(((uintptr_t)ti->type) + field->offset);

        if (iter->tag_iter.tag_buffer > desc->field_count) {
            return caut_status_err_invalid_union;
        }


        if (iter->field_done || !field->data) {
            return caut_status_ok_pop;
        } else {
            RE(push_type_dec_iter(di, field->ref_id, base));
            iter->field_done = true;

            return caut_status_ok_pushed;
        }
    }
}

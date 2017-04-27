#include "cauterize.h"
#include "cauterize_util.h"
#include "cauterize_encode.h"

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

static S caut_enc_get_byte_primitive(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte);
static S caut_enc_get_byte_synonym(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte);
static S caut_enc_get_byte_range(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte);
static S caut_enc_get_byte_enumeration(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte);
static S caut_enc_get_byte_array(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte);
static S caut_enc_get_byte_vector(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte);
static S caut_enc_get_byte_record(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte);
static S caut_enc_get_byte_combination(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte);
static S caut_enc_get_byte_union(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte);

S caut_enc_get_byte(SEI * ei, uint8_t * byte, bool * progress) {
    /* The parameter `byte` can be NULL. If it's not null, copy it
     * into the decoding structure. If it is null, pushing and popping
     * of the stack are allowed, but nothing else. If a byte is needed
     * to make progress, `caut_status_err_need_byte` must be returned
     * until a byte is provided. */

    TD const * td = NULL;
    TEI * ti = NULL;

    *progress = false;

    RE(get_type_enc_iter(ei, &ti));
    RE(get_type_desc(ei->desc, ti->type_id, &td));

    switch (td->prototype_tag) {
    case caut_proto_primitive:
        return caut_enc_get_byte_primitive(ei, td, ti, progress, byte);
    case caut_proto_synonym:
        return caut_enc_get_byte_synonym(ei, td, ti, progress, byte);
    case caut_proto_range:
        return caut_enc_get_byte_range(ei, td, ti, progress, byte);
    case caut_proto_enumeration:
        return caut_enc_get_byte_enumeration(ei, td, ti, progress, byte);
    case caut_proto_array:
        return caut_enc_get_byte_array(ei, td, ti, progress, byte);
    case caut_proto_vector:
        return caut_enc_get_byte_vector(ei, td, ti, progress, byte);
    case caut_proto_record:
        return caut_enc_get_byte_record(ei, td, ti, progress, byte);
    case caut_proto_combination:
        return caut_enc_get_byte_combination(ei, td, ti, progress, byte);
    case caut_proto_union:
        return caut_enc_get_byte_union(ei, td, ti, progress, byte);
    default:
        return caut_status_err_UNIMPLEMENTED;
    }
}

static S caut_enc_get_byte_primitive(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte) {
    struct iter_primitive * iter = &ti->prototype.c_primitive;
    struct caut_primitive const * const desc = &td->prototype.c_primitive;
    uint8_t const * const type_bytes = ti->type;

    (void) ei;

    if (iter->word_position < desc->word_size) {
        if (NULL == byte) {
            return caut_status_err_need_byte;
        } else {
            *progress = true;
            *byte = type_bytes[iter->word_position];
            iter->word_position += 1;

            return caut_status_ok_busy;
        }
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_enc_get_byte_synonym(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte) {
    (void)byte;

    struct iter_synonym * const iter = &ti->prototype.c_synonym;
    struct caut_synonym const * const desc = &td->prototype.c_synonym;

    *progress = false;

    if (iter->done == false) {
        RE(push_type_enc_iter(ei, desc->ref_id, ti->type));
        iter->done = true;

        return caut_status_ok_pushed;
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_enc_get_byte_range(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte) {
    struct iter_range * const iter = &ti->prototype.c_range;
    struct caut_range const * const desc = &td->prototype.c_range;

    (void) ei;

    if (iter->tag_iter.tag_position < caut_tag_size(desc->tag)) {

        struct range_value val = { .is_signed = false };

        if (!range_convert(ti->type, desc, &val)) {
            return caut_status_err_invalid_range;
        }

        if (NULL == byte) {
            return caut_status_err_need_byte;
        } else {
            *progress = true;
            *byte = val.u.b[iter->tag_iter.tag_position];
            iter->tag_iter.tag_position += 1;

            return caut_status_ok_busy;
        }
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_enc_get_byte_enumeration(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte) {
    struct iter_enumeration * const iter = &ti->prototype.c_enumeration;
    struct caut_enumeration const * const desc = &td->prototype.c_enumeration;

    (void) ei;

    if (iter->tag_iter.tag_position < caut_tag_size(desc->tag)) {
        uint64_t word = 0;
        memcpy(&word, ti->type, caut_tag_size(desc->tag));

        if (word >= desc->length) {
            return caut_status_err_invalid_enum;
        } else if (NULL == byte) {
            return caut_status_err_need_byte;
        } else {
            *progress = true;
            *byte = ((uint8_t *)&word)[iter->tag_iter.tag_position];
            iter->tag_iter.tag_position += 1;

            return caut_status_ok_busy;
        }
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_enc_get_byte_array(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte) {
    struct iter_array * const iter = &ti->prototype.c_array;
    struct caut_array const * const desc = &td->prototype.c_array;

    *progress = false;
    (void) byte;

    if (iter->elem_position < desc->length) {
        void const * base =
            (void *)(
                ((uintptr_t)ti->type) +
                (desc->elem_span * iter->elem_position));

        RE(push_type_enc_iter(ei, desc->ref_id, base));
        iter->elem_position += 1;

        return caut_status_ok_pushed;
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_enc_get_byte_vector(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte) {
    struct iter_vector * const iter = &ti->prototype.c_vector;
    struct caut_vector const * const desc = &td->prototype.c_vector;

    uint64_t word = 0;
    memcpy(&word, ti->type, caut_tag_size(desc->tag));

    if (iter->tag_iter.tag_position < caut_tag_size(desc->tag)) {
        // still accumulating tag
        if (word > desc->max_length) {
            return caut_status_err_invalid_vector;
        } else if (NULL == byte) {
            return caut_status_err_need_byte;
        } else {
            *progress = true;
            *byte = ((uint8_t *)&word)[iter->tag_iter.tag_position];
            iter->tag_iter.tag_position += 1;

            return caut_status_ok_busy;
        }
    } else if (iter->elem_position < word) {
        // accumulating elements
        void const * base =
            (void *)(
                ((uintptr_t)ti->type) +
                desc->elem_offset +
                (desc->elem_span * iter->elem_position));

        RE(push_type_enc_iter(ei, desc->ref_id, base));
        iter->elem_position += 1;

        return caut_status_ok_pushed;
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_enc_get_byte_record(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte) {
    struct iter_record * const iter = &ti->prototype.c_record;
    struct caut_record const * const desc = &td->prototype.c_record;

    (void) byte;
    *progress = false;

    if (iter->field_position < desc->field_count) {
        struct caut_field const * const field = &desc->fields[iter->field_position];
        void const * base = (void *)(((uintptr_t)ti->type) + field->offset);

        if (field->data == false) {
            return caut_status_err_invalid_record;
        } else {
            RE(push_type_enc_iter(ei, field->ref_id, base));
            iter->field_position += 1;
        }

        return caut_status_ok_pushed;
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_enc_get_byte_combination(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte) {
    struct iter_combination * const iter = &ti->prototype.c_combination;
    struct caut_combination const * const desc = &td->prototype.c_combination;

    uint64_t word = 0;
    memcpy(&word, ti->type, caut_tag_size(desc->tag));

    if (iter->tag_iter.tag_position < caut_tag_size(desc->tag)) {
        // still accumulating tag
        uint64_t const mask = mask_with_width(desc->field_count);
        if (word > mask) {
            return caut_status_err_invalid_combination;
        } else if (NULL == byte) {
            return caut_status_err_need_byte;
        } else {
            *progress = true;
            *byte = ((uint8_t *)&word)[iter->tag_iter.tag_position];
            iter->tag_iter.tag_position += 1;

            return caut_status_ok_busy;
        }
    } else {
        while (iter->field_position < desc->field_count) {
            uint64_t const field_flag = flag_set_at(iter->field_position);

            if (0 == (field_flag & word)) {
                iter->field_position += 1;
                continue;
            } else {
                struct caut_field const * const field = &desc->fields[iter->field_position];
                void const * base = (void *)(((uintptr_t)ti->type) + field->offset);

                iter->field_position += 1;

                if (field->data) {
                    RE(push_type_enc_iter(ei, field->ref_id, base));
                    return caut_status_ok_pushed;
                } else {
                    continue;
                }
            }
        }

        return caut_status_ok_pop;
    }
}

static S caut_enc_get_byte_union(SEI * ei, TD const * td, TEI * ti, bool * progress, uint8_t * byte) {
    struct iter_union * const iter = &ti->prototype.c_union;
    struct caut_union const * const desc = &td->prototype.c_union;

    uint64_t word = 0;
    memcpy(&word, ti->type, caut_tag_size(desc->tag));

    if (iter->tag_iter.tag_position < caut_tag_size(desc->tag)) {
        // still accumulating tag
        if (word > desc->field_count) {
            return caut_status_err_invalid_union;
        } else if (NULL == byte) {
            return caut_status_err_need_byte;
        } else {
            *progress = true;
            *byte = ((uint8_t *)&word)[iter->tag_iter.tag_position];
            iter->tag_iter.tag_position += 1;

            return caut_status_ok_busy;
        }
    } else {
        struct caut_field const * const field = &desc->fields[word];
        void const * base = (void *)(((uintptr_t)ti->type) + field->offset);

        if (iter->field_done || !field->data) {
            return caut_status_ok_pop;
        } else {
            RE(push_type_enc_iter(ei, field->ref_id, base));
            iter->field_done = true;

            return caut_status_ok_pushed;
        }
    }
}

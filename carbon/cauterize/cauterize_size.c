#include "cauterize.h"
#include "cauterize_util.h"
#include "cauterize_size.h"

#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define S enum caut_status
#define SD struct schema_descriptor
#define TD struct type_descriptor
#define TSI struct type_size_iterator
#define SSI struct schema_size_iterator

static S caut_enc_get_size_primitive(SSI * si, TD const * td, TSI * ti, size_t * size);
static S caut_enc_get_size_synonym(SSI * si, TD const * td, TSI * ti, size_t * size);
static S caut_enc_get_size_range(SSI * si, TD const * td, TSI * ti, size_t * size);
static S caut_enc_get_size_enumeration(SSI * si, TD const * td, TSI * ti, size_t * size);
static S caut_enc_get_size_array(SSI * si, TD const * td, TSI * ti, size_t * size);
static S caut_enc_get_size_vector(SSI * si, TD const * td, TSI * ti, size_t * size);
static S caut_enc_get_size_record(SSI * si, TD const * td, TSI * ti, size_t * size);
static S caut_enc_get_size_combination(SSI * si, TD const * td, TSI * ti, size_t * size);
static S caut_enc_get_size_union(SSI * si, TD const * td, TSI * ti, size_t * size);

enum caut_status caut_enc_get_size(SSI * si, size_t * size) {
    TD const * td = NULL;
    TSI * ti = NULL;

    RE(get_type_size_iter(si, &ti));
    RE(get_type_desc(si->desc, ti->type_id, &td));

    switch (td->prototype_tag) {
    case caut_proto_primitive:
        return caut_enc_get_size_primitive(si, td, ti, size);
    case caut_proto_synonym:
        return caut_enc_get_size_synonym(si, td, ti, size);
    case caut_proto_range:
        return caut_enc_get_size_range(si, td, ti, size);
    case caut_proto_enumeration:
        return caut_enc_get_size_enumeration(si, td, ti, size);
    case caut_proto_array:
        return caut_enc_get_size_array(si, td, ti, size);
    case caut_proto_vector:
        return caut_enc_get_size_vector(si, td, ti, size);
    case caut_proto_record:
        return caut_enc_get_size_record(si, td, ti, size);
    case caut_proto_combination:
        return caut_enc_get_size_combination(si, td, ti, size);
    case caut_proto_union:
        return caut_enc_get_size_union(si, td, ti, size);
    default:
        return caut_status_err_UNIMPLEMENTED;
    }

}

static S caut_enc_get_size_primitive(SSI * si, TD const * td, TSI * ti, size_t * size) {
    (void)si;
    (void)ti;
    struct caut_primitive const * const desc = &td->prototype.c_primitive;

    *size += desc->word_size;

    return caut_status_ok_pop;
}

static S caut_enc_get_size_synonym(SSI * si, TD const * td, TSI * ti, size_t * size) {
    (void)size;
    struct iter_synonym * const iter = &ti->prototype.c_synonym;
    struct caut_synonym const * const desc = &td->prototype.c_synonym;

    if (iter->done == false) {
        RE(push_type_size_iter(si, desc->ref_id, ti->type));
        iter->done = true;

        return caut_status_ok_pushed;
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_enc_get_size_range(SSI * si, TD const * td, TSI * ti, size_t * size) {
    (void)si;
    (void)ti;
    struct caut_range const * const desc = &td->prototype.c_range;

    struct range_value val = { .is_signed = false };

    if (!range_convert(ti->type, desc, &val)) {
        return caut_status_err_invalid_range;
    } else {
        *size += caut_tag_size(desc->tag);
    }

    return caut_status_ok_pop;
}

static S caut_enc_get_size_enumeration(SSI * si, TD const * td, TSI * ti, size_t * size) {
    (void)si;
    struct caut_enumeration const * const desc = &td->prototype.c_enumeration;

    uint64_t word = 0;
    memcpy(&word, ti->type, caut_tag_size(desc->tag));

    if (word >= desc->length) {
        return caut_status_err_invalid_enum;
    } else {
        *size += caut_tag_size(desc->tag);
        return caut_status_ok_pop;
    }
}

static S caut_enc_get_size_array(SSI * si, TD const * td, TSI * ti, size_t * size) {
    (void)size;
    struct iter_array * const iter = &ti->prototype.c_array;
    struct caut_array const * const desc = &td->prototype.c_array;

    if (iter->elem_position < desc->length) {
        void const * base =
            (void *)(
                ((uintptr_t)ti->type) +
                (desc->elem_span * iter->elem_position));

        RE(push_type_size_iter(si, desc->ref_id, base));
        iter->elem_position += 1;

        return caut_status_ok_pushed;
    } else {
        return caut_status_ok_pop;
    }

}

static S caut_enc_get_size_vector(SSI * si, TD const * td, TSI * ti, size_t * size) {
    struct iter_vector * const iter = &ti->prototype.c_vector;
    struct caut_vector const * const desc = &td->prototype.c_vector;

    uint64_t word = 0;
    memcpy(&word, ti->type, caut_tag_size(desc->tag));

    if (word > desc->max_length) {
        return caut_status_err_invalid_vector;
    }

    if (iter->tag_iter.tag_position < caut_tag_size(desc->tag)) {
        // We use this to indicate that we've counted the size for the
        // tag already and don't need to do it again.
        iter->tag_iter.tag_position = caut_tag_size(desc->tag);
        *size += caut_tag_size(desc->tag);
    }

    if (iter->elem_position < word) {
        void const * base =
            (void *)(
                ((uintptr_t)ti->type) +
                desc->elem_offset +
                (desc->elem_span * iter->elem_position));

        RE(push_type_size_iter(si, desc->ref_id, base));
        iter->elem_position += 1;

        return caut_status_ok_pushed;
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_enc_get_size_record(SSI * si, TD const * td, TSI * ti, size_t * size) {
    (void)size;
    struct iter_record * const iter = &ti->prototype.c_record;
    struct caut_record const * const desc = &td->prototype.c_record;

    if (iter->field_position < desc->field_count) {
        struct caut_field const * const field = &desc->fields[iter->field_position];
        void const * base = (void *)(((uintptr_t)ti->type) + field->offset);

        if (field->data == false) {
            return caut_status_err_invalid_record;
        } else {
            RE(push_type_size_iter(si, field->ref_id, base));
            iter->field_position += 1;
        }

        return caut_status_ok_pushed;
    } else {
        return caut_status_ok_pop;
    }
}

static S caut_enc_get_size_combination(SSI * si, TD const * td, TSI * ti, size_t * size) {
    struct iter_combination * const iter = &ti->prototype.c_combination;
    struct caut_combination const * const desc = &td->prototype.c_combination;

    uint64_t word = 0;
    memcpy(&word, ti->type, caut_tag_size(desc->tag));

    if (iter->tag_iter.tag_position < caut_tag_size(desc->tag)) {
        // We use this to indicate that we've counted the size for the
        // tag already and don't need to do it again.
        iter->tag_iter.tag_position = caut_tag_size(desc->tag);

        uint64_t const mask = mask_with_width(desc->field_count);
        if (word > mask) {
            return caut_status_err_invalid_combination;
        } else {
            *size += caut_tag_size(desc->tag);
        }
    }

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
                RE(push_type_size_iter(si, field->ref_id, base));
                return caut_status_ok_pushed;
            } else {
                continue;
            }
        }
    }

    return caut_status_ok_pop;
}

static S caut_enc_get_size_union(SSI * si, TD const * td, TSI * ti, size_t * size) {
    struct iter_union * const iter = &ti->prototype.c_union;
    struct caut_union const * const desc = &td->prototype.c_union;

    uint64_t word = 0;
    memcpy(&word, ti->type, caut_tag_size(desc->tag));

    if (iter->tag_iter.tag_position < caut_tag_size(desc->tag)) {
        // We use this to indicate that we've counted the size for the
        // tag already and don't need to do it again.
        iter->tag_iter.tag_position = caut_tag_size(desc->tag);

        if (word > desc->field_count) {
            return caut_status_err_invalid_union;
        } else {
            *size += caut_tag_size(desc->tag);
        }
    }

    struct caut_field const * const field = &desc->fields[word];
    void const * base = (void *)(((uintptr_t)ti->type) + field->offset);

    if (iter->field_done || !field->data) {
        return caut_status_ok_pop;
    } else {
        RE(push_type_size_iter(si, field->ref_id, base));
        iter->field_done = true;

        return caut_status_ok_pushed;
    }
}

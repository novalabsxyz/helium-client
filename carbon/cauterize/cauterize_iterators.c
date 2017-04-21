#include "cauterize_iterators.h"
#include "cauterize_descriptors.h"
#include "cauterize_util.h"

#include <string.h>
#include <stdlib.h>

#define S enum caut_status
#define SD struct schema_descriptor
#define SEI struct schema_encode_iterator
#define SDI struct schema_decode_iterator
#define SSI struct schema_size_iterator
#define TEI struct type_encode_iterator
#define TDI struct type_decode_iterator
#define TSI struct type_size_iterator
#define TD struct type_descriptor

S type_encode_iterator_init(SD const * sd, TEI * ti, int type_id, void const * type) {
    struct type_descriptor const * td = NULL;

    RE(id_check(sd, type_id));
    RE(get_type_desc(sd, type_id, &td));

    memset(ti, 0, sizeof(*ti));

    ti->proto = td->prototype_tag;
    ti->type = type;
    ti->type_id = type_id;

    return caut_status_ok;
}

S type_decode_iterator_init(SD const * sd, TDI * ti, int type_id, void * type) {
    struct type_descriptor const * td = NULL;

    RE(id_check(sd, type_id));
    RE(get_type_desc(sd, type_id, &td));

    memset(ti, 0, sizeof(*ti));

    ti->proto = td->prototype_tag;
    ti->type = type;
    ti->type_id = type_id;

    return caut_status_ok;
}

S type_size_iterator_init(SD const * sd, TSI * ti, int type_id, void const * type) {
    struct type_descriptor const * td = NULL;

    RE(id_check(sd, type_id));
    RE(get_type_desc(sd, type_id, &td));

    memset(ti, 0, sizeof(*ti));

    ti->proto = td->prototype_tag;
    ti->type = type;
    ti->type_id = type_id;

    return caut_status_ok;
}

S get_type_enc_iter(SEI const * ei, TEI ** ti_out) {
    if (ei->iter_top < ei->iter_count) {
        *ti_out = &ei->iters[ei->iter_top];
        return caut_status_ok;
    } else {
        return caut_status_err_iter_stack_would_overflow;
    }
}

S get_type_dec_iter(SDI const * di, TDI ** ti_out) {
    if (di->iter_top < di->iter_count) {
        *ti_out = &di->iters[di->iter_top];
        return caut_status_ok;
    } else {
        return caut_status_err_iter_stack_would_overflow;
    }
}

S get_type_size_iter(SSI const * si, TSI ** ti_out) {
    if (si->iter_top < si->iter_count) {
        *ti_out = &si->iters[si->iter_top];
        return caut_status_ok;
    } else {
        return caut_status_err_iter_stack_would_overflow;
    }
}

S push_type_enc_iter(SEI * ei, int type_id, void const * type_base) {
    TEI * ti_out = NULL;

    ei->iter_top += 1;
    RE(get_type_enc_iter(ei, &ti_out));
    RE(type_encode_iterator_init(ei->desc, ti_out, type_id, type_base));

    return caut_status_ok;
}

S push_type_dec_iter(SDI * di, int type_id, void * type_base) {
    TDI * ti_out = NULL;

    di->iter_top += 1;
    RE(get_type_dec_iter(di, &ti_out));
    RE(type_decode_iterator_init(di->desc, ti_out, type_id, type_base));

    return caut_status_ok;
}

S push_type_size_iter(SSI * si, int type_id, void const * type_base) {
    TSI * ti_out = NULL;

    si->iter_top += 1;
    RE(get_type_size_iter(si, &ti_out));
    RE(type_size_iterator_init(si->desc, ti_out, type_id, type_base));

    return caut_status_ok;
}

#ifndef CAUTERIZE_H
#define CAUTERIZE_H

#include "cauterize_types.h"
#include "cauterize_descriptors.h"
#include "cauterize_iterators.h"

#include <stdint.h>

enum caut_status caut_enc_get(
    struct schema_encode_iterator * ei,
    void * buf,
    size_t buf_size,
    size_t * enc_bytes);

enum caut_status caut_dec_put(
    struct schema_decode_iterator * di,
    void const * buf,
    size_t buf_size,
    size_t * dec_bytes);

enum caut_status caut_size_get(
    struct schema_size_iterator * di,
    size_t * size);

enum caut_status schema_encode_iterator_init(
    struct schema_encode_iterator * si,
    struct schema_descriptor const * sd,
    struct type_encode_iterator * ti,
    size_t ti_count,
    int type_id,
    void const * src_type);

enum caut_status schema_decode_iterator_init(
    struct schema_decode_iterator * si,
    struct schema_descriptor const * sd,
    struct type_decode_iterator * ti,
    size_t ti_count,
    int type_id,
    void * dst_type);

enum caut_status schema_size_iterator_init(
    struct schema_size_iterator * si,
    struct schema_descriptor const * sd,
    struct type_size_iterator * ti,
    size_t ti_count,
    int type_id,
    void const * src_type);

#endif /* CAUTERIZE_H */

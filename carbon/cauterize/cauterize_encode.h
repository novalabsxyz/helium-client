#ifndef CAUTERIZE_ENCODE_H
#define CAUTERIZE_ENCODE_H

#include <stdint.h>
#include <stdbool.h>

#include "cauterize_types.h"
#include "cauterize_iterators.h"

enum caut_status caut_enc_get_byte(struct schema_encode_iterator * ei, uint8_t * byte, bool * progress);

#endif /* CAUTERIZE_ENCODE_H */

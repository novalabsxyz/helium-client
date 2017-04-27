#ifndef CAUTERIZE_SIZE_H
#define CAUTERIZE_SIZE_H

#include <stdint.h>
#include <stdbool.h>

#include "cauterize_types.h"
#include "cauterize_iterators.h"

enum caut_status caut_enc_get_size(struct schema_size_iterator * ei,
                                   size_t * size);

#endif /* CAUTERIZE_SIZE_H */

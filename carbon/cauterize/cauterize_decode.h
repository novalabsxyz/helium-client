#ifndef CAUTERIZE_DECODE_H
#define CAUTERIZE_DECODE_H

enum caut_status caut_dec_put_byte(struct schema_decode_iterator * di, uint8_t const * byte, bool * progress);

#endif /* CAUTERIZE_DECODE_H */

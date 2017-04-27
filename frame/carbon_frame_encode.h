#ifndef CARBON_FRAME_ENCODE_H
#define CARBON_FRAME_ENCODE_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

enum carbon_frame_encode_byte_status {
    carbon_frame_encode_byte_UNINITIALIZED = 0,

    carbon_frame_encode_byte_OUT_VALID,
    carbon_frame_encode_byte_NEED_INPUT,
    carbon_frame_encode_byte_DONE,
};

enum carbon_frame_encode_buffer_status {
    carbon_frame_encode_buffer_UNINITIALIZED = 0,

    carbon_frame_encode_buffer_BUFFER_VALID,
    carbon_frame_encode_buffer_BUFFER_FULL,
    carbon_frame_encode_buffer_NEED_INPUT,
    carbon_frame_encode_buffer_DONE,
};

enum carbon_frame_encode_give_status {
    carbon_frame_encode_give_OK,
    carbon_frame_encode_give_BUSY,
    carbon_frame_encode_give_OVERFLOW,
};

enum carbon_frame_encode_state {
    carbon_frame_encode_state_UNINITIALIZED = 0,

    carbon_frame_encode_state_SOF,
    carbon_frame_encode_state_LEN_LSB,
    carbon_frame_encode_state_LEN_MSB,
    carbon_frame_encode_state_DATA,
    carbon_frame_encode_state_EOF,
    carbon_frame_encode_state_DONE,
};

struct carbon_frame_encode_ctx {
    enum carbon_frame_encode_state state;
    size_t len;
    size_t pos;

    bool already_escaped;

    void const * given;
    size_t given_len;
    size_t given_pos;
};


/**
 * carbon_frame_encode_init
 *
 * Initializes an encoding context with a length. */
void carbon_frame_encode_init(struct carbon_frame_encode_ctx * ctx, size_t len);

/**
 * carbon_frame_encode_give
 *
 * Give data to be encoded to the context. May be less than the total
 * amount to be transferred. May not overflow the context's length.
 *
 * Returns:
 *   _OK - data will be encoded
 *   _BUSY - previous give was not completed
 *   _OVERFLOW - more data was given than is specified in the context
 *               length
 */
enum carbon_frame_encode_give_status carbon_frame_encode_give(struct carbon_frame_encode_ctx * ctx,
                                                              void const * input,
                                                              size_t len);

/**
 * am_frame_get_byte
 *
 * Encodes a single byte from the given input.
 *
 * Returns:
 *   _OUT_VALID - when `out` contains valid data
 *   _NEED_INPUT - when `carbon_frame_encode_give` needs to be called with
 *                 more input data
 *   _DONE - when the lenght is exhausted
 */
enum carbon_frame_encode_byte_status carbon_frame_encode_byte(struct carbon_frame_encode_ctx * ctx,
                                                              uint8_t * out);

/**
 * carbon_frame_encode_buffer
 *
 * Encodes bytes until we run out of input data or the buffer
 * fills. */
enum carbon_frame_encode_buffer_status carbon_frame_encode_buffer(struct carbon_frame_encode_ctx * const ctx,
                                                                  uint8_t * const buffer,
                                                                  size_t const bufsize,
                                                                  size_t * const used);

#endif /* CARBON_FRAME_ENCODE_H */

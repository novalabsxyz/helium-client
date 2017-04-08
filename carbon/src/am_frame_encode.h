#ifndef AM_FRAME_ENCODE_H
#define AM_FRAME_ENCODE_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

enum am_frame_encode_byte_status {
    afeb_status_UNINITIALIZED = 0,

    afeb_status_OUT_VALID,
    afeb_status_NEED_INPUT,
    afeb_status_DONE,
};

enum am_frame_encode_buffer_status {
    afebu_status_UNINITIALIZED = 0,

    afebu_status_BUFFER_VALID,
    afebu_status_BUFFER_FULL,
    afebu_status_NEED_INPUT,
    afebu_status_DONE,
};

enum am_frame_encode_give_status {
    afeg_status_OK,
    afeg_status_BUSY,
    afeg_status_OVERFLOW,
};

enum am_frame_encode_state {
    afe_state_UNINITIALIZED = 0,

    afe_state_SOF,
    afe_state_LEN_LSB,
    afe_state_LEN_MSB,
    afe_state_DATA,
    afe_state_EOF,
    afe_state_DONE,
};

struct am_frame_encode_ctx {
    enum am_frame_encode_state state;
    size_t len;
    size_t pos;

    bool already_escaped;

    void const * given;
    size_t given_len;
    size_t given_pos;
};


/**
 * am_frame_encode_init
 *
 * Initializes an encoding context with a length. */
void am_frame_encode_init(struct am_frame_encode_ctx * ctx, size_t len);

/**
 * am_frame_encode_give
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
enum am_frame_encode_give_status am_frame_encode_give(struct am_frame_encode_ctx * ctx,
                                                      void const * input,
                                                      size_t len);

/**
 * am_frame_get_byte
 *
 * Encodes a single byte from the given input.
 *
 * Returns:
 *   _OUT_VALID - when `out` contains valid data
 *   _NEED_INPUT - when `am_frame_encode_give` needs to be called with
 *                 more input data
 *   _DONE - when the lenght is exhausted
 */
enum am_frame_encode_byte_status am_frame_encode_byte(struct am_frame_encode_ctx * ctx,
                                                      uint8_t * out);

/**
 * am_frame_encode_buffer
 *
 * Encodes bytes until we run out of input data or the buffer
 * fills. */
enum am_frame_encode_buffer_status am_frame_encode_buffer(struct am_frame_encode_ctx * const ctx,
                                                          uint8_t * const buffer,
                                                          size_t const bufsize,
                                                          size_t * const used);

#endif /* AM_FRAME_ENCODE_H */

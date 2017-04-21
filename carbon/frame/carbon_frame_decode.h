#ifndef CARBON_FRAME_DECODE_H
#define CARBON_FRAME_DECODE_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

enum carbon_frame_decode_state {
    carbon_frame_decode_state_UNINITIALIZED = 0,

    carbon_frame_decode_state_SOF,
    carbon_frame_decode_state_LEN_LSB,
    carbon_frame_decode_state_LEN_MSB,
    carbon_frame_decode_state_DATA,
    carbon_frame_decode_state_EOF,
    carbon_frame_decode_state_DONE,
};

enum carbon_frame_decode_give_status {
    carbon_frame_decode_give_OK,
    carbon_frame_decode_give_BUSY,
};

enum carbon_frame_decode_byte_status {
    carbon_frame_decode_byte_UNINITIALIZED = 0,

    carbon_frame_decode_byte_OUT_VALID,
    carbon_frame_decode_byte_NEED_INPUT,
    carbon_frame_decode_byte_RESTART_FRAME,
    carbon_frame_decode_byte_DONE,
    carbon_frame_decode_byte_DONE_WITH_ERROR,
};

enum carbon_frame_decode_buffer_status {
    carbon_frame_decode_buffer_UNINITIALIZED = 0,

    carbon_frame_decode_buffer_BUFFER_VALID,
    carbon_frame_decode_buffer_BUFFER_FULL,
    carbon_frame_decode_buffer_NEED_INPUT,
    carbon_frame_decode_buffer_RESTART_FRAME,
    carbon_frame_decode_buffer_DONE,
    carbon_frame_decode_buffer_DONE_WITH_ERROR,
};

enum carbon_frame_decode_error {
    carbon_frame_decode_error_NONE,
    carbon_frame_decode_error_BAD_ESCAPE,
    carbon_frame_decode_error_OVERSIZED_FRAME,
    carbon_frame_decode_error_UNDERSIZED_FRAME,
};

enum carbon_frame_decode_reset_status {
    carbon_frame_decode_reset_OK,
    carbon_frame_decode_reset_NOT_DONE,
};

struct carbon_frame_decode_ctx {
    enum carbon_frame_decode_state state;
    size_t len;
    size_t pos;

    bool need_escape;

    enum carbon_frame_decode_error error;

    void const * given;
    size_t given_len;
    size_t given_pos;
};

/**
 * carbon_frame_decode_init
 *
 * Initialize a decoding context. Length will be inferred from the
 * decoded stream. */
void carbon_frame_decode_init(struct carbon_frame_decode_ctx * const ctx);

/**
 * carbon_frame_decode_give
 *
 * Give a buffer of encoded bytes to the context. May be less than the
 * total amount to be decoded. May not be given before the previous
 * give is completely consumed. */
enum carbon_frame_decode_give_status carbon_frame_decode_give(struct carbon_frame_decode_ctx * const ctx,
                                                              void const * const input,
                                                              size_t const len);

/**
 * carbon_frame_decode_byte
 *
 * Decode a single byte from the given input. */
enum carbon_frame_decode_byte_status carbon_frame_decode_byte(struct carbon_frame_decode_ctx * const ctx,
                                                              uint8_t * const byte);

/**
 * carbon_frame_decode_reset
 *
 * Reset the length and position of the context so that additional
 * frames can be parsed out of the given data stream.
 *
 * Function may only be used when the context state has reached a
 * DONE* state. */
enum carbon_frame_decode_reset_status carbon_frame_decode_reset(struct carbon_frame_decode_ctx * const ctx);


/**
 * carbon_frame_decode_buffer
 *
 * Decode a buffer from the given input. `used` will be set to 0
 * unless data was actually decoded. */
enum carbon_frame_decode_buffer_status carbon_frame_decode_buffer(struct carbon_frame_decode_ctx * ctx,
                                                                  uint8_t * const buffer,
                                                                  size_t const bufsize,
                                                                  size_t * const used);

/**
 * carbon_frame_decode_get_error
 *
 * Get the error condition from the context. */
enum carbon_frame_decode_error carbon_frame_decode_get_error(struct carbon_frame_decode_ctx * ctx);

/**
 * carbon_frame_decode_remaining
 *
 * Return how many bytes of data are remaining to be parsed. */
size_t carbon_frame_decode_remaining(struct carbon_frame_decode_ctx * ctx);

#endif /* CARBON_FRAME_DECODE_H */

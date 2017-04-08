#ifndef AM_FRAME_DECODE_H
#define AM_FRAME_DECODE_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

enum am_frame_decode_state {
    afd_state_UNINITIALIZED = 0,

    afd_state_SOF,
    afd_state_LEN_LSB,
    afd_state_LEN_MSB,
    afd_state_DATA,
    afd_state_EOF,
    afd_state_DONE,
};

enum am_frame_decode_give_status {
    afdg_status_OK,
    afdg_status_BUSY,
};

enum am_frame_decode_byte_status {
    afdb_status_UNINITIALIZED = 0,

    afdb_status_OUT_VALID,
    afdb_status_NEED_INPUT,
    afdb_status_RESTART_FRAME,
    afdb_status_DONE,
    afdb_status_DONE_WITH_ERROR,
};

enum am_frame_decode_buffer_status {
    afdbu_status_UNINITIALIZED = 0,

    afdbu_status_BUFFER_VALID,
    afdbu_status_BUFFER_FULL,
    afdbu_status_NEED_INPUT,
    afdbu_status_RESTART_FRAME,
    afdbu_status_DONE,
    afdbu_status_DONE_WITH_ERROR,
};

enum am_frame_decode_error {
    afd_error_NONE,
    afd_error_BAD_ESCAPE,
    afd_error_OVERSIZED_FRAME,
    afd_error_UNDERSIZED_FRAME,
};

enum am_frame_decode_reset_status {
    afdr_status_OK,
    afdr_status_NOT_DONE,
};

struct am_frame_decode_ctx {
    enum am_frame_decode_state state;
    size_t len;
    size_t pos;

    bool need_escape;

    enum am_frame_decode_error error;

    void const * given;
    size_t given_len;
    size_t given_pos;
};

/**
 * am_frame_decode_init
 *
 * Initialize a decoding context. Length will be inferred from the
 * decoded stream. */
void am_frame_decode_init(struct am_frame_decode_ctx * const ctx);

/**
 * am_frame_decode_give
 *
 * Give a buffer of encoded bytes to the context. May be less than the
 * total amount to be decoded. May not be given before the previous
 * give is completely consumed. */
enum am_frame_decode_give_status am_frame_decode_give(struct am_frame_decode_ctx * const ctx,
                                                      void const * const input,
                                                      size_t const len);

/**
 * am_frame_decode_byte
 *
 * Decode a single byte from the given input. */
enum am_frame_decode_byte_status am_frame_decode_byte(struct am_frame_decode_ctx * const ctx,
                                                      uint8_t * const byte);

/**
 * am_frame_decode_reset
 *
 * Reset the length and position of the context so that additional
 * frames can be parsed out of the given data stream.
 *
 * Function may only be used when the context state has reached a
 * DONE* state. */
enum am_frame_decode_reset_status am_frame_decode_reset(struct am_frame_decode_ctx * const ctx);


/**
 * am_frame_decode_buffer
 *
 * Decode a buffer from the given input. `used` will be set to 0
 * unless data was actually decoded. */
enum am_frame_decode_buffer_status am_frame_decode_buffer(struct am_frame_decode_ctx * ctx,
                                                          uint8_t * const buffer,
                                                          size_t const bufsize,
                                                          size_t * const used);

/**
 * am_frame_decode_get_error
 *
 * Get the error condition from the context. */
enum am_frame_decode_error am_frame_decode_get_error(struct am_frame_decode_ctx * ctx);

/**
 * am_frame_decode_remaining
 *
 * Return how many bytes of data are remaining to be parsed. */
size_t am_frame_decode_remaining(struct am_frame_decode_ctx * ctx);

#endif /* AM_FRAME_DECODE_H */

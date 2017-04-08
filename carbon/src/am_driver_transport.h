#ifndef AM_DRIVER_TRANSPORT_H
#define AM_DRIVER_TRANSPORT_H

#include <stdint.h>
#include <stddef.h>

#include "am_frame_encode.h"
#include "am_frame_decode.h"

#include "am_interface.h"

/* This module is responsible for controlling the UART state that
 * communicates with the Atom radio module and defines all the
 * associated interrupt handlers. */

enum amd_uart_tx_stat {
    amdu_tx_err = 0,
    amdu_tx_ok,

    amdu_tx_frame_more,
    amdu_tx_frame_done,
};

enum amd_uart_rx_stat {
    amd_uart_rx_UNINITIALIZED,
    amd_uart_rx_ok,
    amd_uart_rx_timeout,
    amd_uart_rx_os_timeout,
    amd_uart_rx_err,

    amd_uart_rx_frame_more,
    amd_uart_rx_frame_restart,
    amd_uart_rx_frame_done,
    amd_uart_rx_frame_done_with_error,
    amd_uart_rx_frame_timeout,
};

#define UART_RX_BUFFER_SIZE (5)
#define UART_RX_QUEUE_DEPTH (2)
#define TX_FRAME_BUFFER_SIZE (16)

struct uart_rx_buffer {
    enum amd_uart_rx_stat stat;
    size_t used;
    uint8_t data[UART_RX_BUFFER_SIZE];
};

struct uart_tx_ctx {
    struct am_frame_encode_ctx ctx;

    /* True when busy transmitting a frame. */
    volatile bool framed_busy;

    /* Used to hold chukns of an intermediate frame. */
    uint8_t tx_frame_buffer[TX_FRAME_BUFFER_SIZE];
};

struct uart_rx_ctx {
    struct am_frame_decode_ctx ctx;
    struct uart_rx_buffer buf;
};

/* Start transmission over the UART in the Helium Atom framing
 * format. */
void amd_uart_tx_framed_start(struct uart_tx_ctx * ctx,
                              size_t frame_len);

/* Give more data to be transmitted as part of the current frame. */
enum amd_uart_tx_stat amd_uart_tx_framed_give(struct am_transport_iface const * iface,
                                              struct uart_tx_ctx * ctx,
                                              void const * data,
                                              size_t len);

/* Setup to receive data from the UART. Parse it as a (possibly
 * partial) frame into data. `used` will indicate how many bytes were
 * stored in `data`.
 *
 * This context does not ever need to be re-initialized as long as
 * _get and _reset commands are used to fetch frames and reset the
 * fetching context. */
enum amd_uart_rx_stat amd_uart_rx_framed_init(struct uart_rx_ctx * ctx);

/* Parse USARt data as a (possibly partial) frame into data. `used`
 * will indicate how many bytes were stored in `data`. */
enum amd_uart_rx_stat amd_uart_rx_framed_get(struct am_transport_iface const * iface,
                                             struct uart_rx_ctx * ctx,
                                             void * data,
                                             size_t len,
                                             size_t * used);

/* Keep receiving buffers from the UART until the current frame
 * reaches a DONE state. */
enum amd_uart_rx_stat amd_uart_rx_framed_flush(struct am_transport_iface const * iface,
                                               struct uart_rx_ctx * ctx);

/* Using the existing context and data, setup to receive another frame
 * from the UART. */
enum amd_uart_rx_stat amd_uart_rx_framed_reset(struct uart_rx_ctx * ctx);

#endif /* AM_DRIVER_TRANSPORT_H */

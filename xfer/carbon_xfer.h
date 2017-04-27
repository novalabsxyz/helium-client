#ifndef CARBON_XFER_H
#define CARBON_XFER_H

#include <stdint.h>
#include <stddef.h>

#include "frame/carbon_frame_encode.h"
#include "frame/carbon_frame_decode.h"
#include "carbon_interface.h"

/* This module is responsible for controlling the UART state that
 * communicates with the Atom radio module and defines all the
 * associated interrupt handlers. */

struct carbon_xfer_tx_ctx {
    /* The frame encoding context. */
    struct carbon_frame_encode_ctx ctx;

    /* True when busy transmitting a frame. */
    volatile bool framed_busy;

    /* Used to hold chukns of an intermediate frame. */
    struct carbon_tx_buffer buffer;
};

struct carbon_xfer_rx_ctx {
    /* The frame decoding context. */
    struct carbon_frame_decode_ctx ctx;

    /* The intermediate receive buffer. */
    struct carbon_rx_buffer buf;
};

/* Start transmission over some transfer media in the Helium Atom
 * framing format. */
void carbon_xfer_tx_start(struct carbon_xfer_tx_ctx * ctx,
                          size_t frame_len);

/* Give more data to be transmitted as part of the current frame. */
enum carbon_xfer_tx_give_status {
    carbon_xfer_tx_give_ERR,
    carbon_xfer_tx_give_DONE,
    carbon_xfer_tx_give_MORE,
};
enum carbon_xfer_tx_give_status carbon_xfer_tx_give(struct carbon_transport_iface const * iface,
                                                    struct carbon_xfer_tx_ctx * ctx,
                                                    void const * data,
                                                    size_t len);

/* Setup to receive data from the UART. Parse it as a (possibly
 * partial) frame into data. `used` will indicate how many bytes were
 * stored in `data`.
 *
 * This context does not ever need to be re-initialized as long as
 * _get and _reset commands are used to fetch frames and reset the
 * fetching context. */
void carbon_xfer_rx_init(struct carbon_xfer_rx_ctx * ctx);

/* Parse transfer data as a (possibly partial) frame into data. `used`
 * will indicate how many bytes were stored in `data`. */
enum carbon_xfer_rx_get_status {
    carbon_xfer_rx_get_MORE,
    carbon_xfer_rx_get_DONE,
    carbon_xfer_rx_get_RESTART,
    carbon_xfer_rx_get_ERR_TIMEOUT,
    carbon_xfer_rx_get_ERR_DONE_WITH_ERROR,
};

enum carbon_xfer_rx_get_status carbon_xfer_rx_get(struct carbon_transport_iface const * iface,
                                                  struct carbon_xfer_rx_ctx * ctx,
                                                  void * data,
                                                  size_t len,
                                                  size_t * used);

/* Keep receiving buffers from the UART until the current frame
 * reaches a DONE state. Return values behave like _rx_get. All
 * received data is discarded. */
enum carbon_xfer_rx_get_status carbon_xfer_rx_flush(struct carbon_transport_iface const * iface,
                                                    struct carbon_xfer_rx_ctx * ctx);

#endif /* CARBON_XFER_H */

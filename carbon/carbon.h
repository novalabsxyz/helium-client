#ifdef __cplusplus
extern "C"
{
#endif

#ifndef CARBON_H
#define CARBON_H

#include <stdbool.h>
#include <stdint.h>

#include "api/carbon_api.h"

struct carbon_ctx {
    /* The sequence number for Atom API type. */
    uint16_t seq;

    /* The Atom API framing context. */
    struct carbon_api_ctx cactx;

    /* The memory for our command type. */
    struct a_cmd_t cmd;

    /* The system time in milliseconds at which we last synchronized
     * the atom info. */
    uint64_t atom_info_sync_time;

    /* The most recent Atom Info. */
    struct a_resp_get_atom_info atom_info;

    /* The memory in which we store our cached quick-connect
     * connection. */
    struct n_connection connection;
};



#define CARBON_CONNECTION_TIMEOUT (1 * 60) /* seconds */
#define CARBON_MAC_ADDRESS_SIZE (8)

/* Called once at application startup. */
void carbon_init(struct carbon_ctx * ctx, struct carbon_transport_iface const * iface);

/* Called after _init to validate the Atom schema fingerprint. */
bool carbon_check_atom_fingerprint(struct carbon_ctx * ctx);

/* Called to enable communication with the Atom by powering it on. */
void carbon_enable(struct carbon_ctx * ctx);

/* Called to disable communication with the Atom and save power by turning it off. */
void carbon_disable(struct carbon_ctx * ctx);

/* Return the time in seconds since the Unix Epoch. 0 is returned if
 * there is not enough information to calculate calendar time. */
uint32_t carbon_calendar_time(struct carbon_ctx * ctx);

/* Return the system time in milliseconds. This time should always be
 * valid and does not have to have the same epoch as
 * `carbon_calendar_time`. */
uint64_t carbon_system_time(struct carbon_ctx * ctx);

/* Return the MAC address as a little-endian 64 bit value. */
enum carbon_read_mac_status {
    carbon_read_mac_OK,
    carbon_read_mac_ERR_COMMUNICATION,
};
enum carbon_read_mac_status carbon_read_mac(struct carbon_ctx * ctx, uint64_t * mac);

enum carbon_connection_state_status {
    carbon_connection_state_CONNECTED,
    carbon_connection_state_NOT_CONNECTED,
    carbon_connection_state_ERR_COMMUNICATION,
};
enum carbon_connection_state_status carbon_connection_state(struct carbon_ctx * ctx);

enum carbon_connect_status {
    carbon_connect_OK,
    carbon_connect_ERR_TIMEOUT,
    carbon_connect_ERR_AUTONOMOUS, // TODO: change name to hide autonomous
    carbon_connect_ERR_CONNECT,
    carbon_connect_ERR_CONNECT_WAIT,
    carbon_connect_ERR_CONNECT_TIMEOUT,
    carbon_connect_ERR_GET_INFO,
};
enum carbon_connect_status carbon_connect(struct carbon_ctx * ctx);

// TODO: rename to disconnect OR merge into disable
enum carbon_sleep_status {
    carbon_sleep_OK,
    carbon_sleep_ERR_COMMUNICATION,
};
enum carbon_sleep_status carbon_sleep(struct carbon_ctx * ctx);

enum carbon_send_data_status {
    /* Send was ACKed by the bridge. */
    carbon_send_data_OK,

    /* A temporary condition prevented us from sending. */
    // TODO: drop ERR from these names
    carbon_send_data_ERR_RECOVERABLE_CHANNEL_ACCESS_FAILURE,
    carbon_send_data_ERR_RECOVERABLE_NACK,

    /* Unable to communicate with the Atom module. */
    carbon_send_data_ERR_XFER_COMMUNICATION,

    /* Some other Atom module condition caused us to fail. */
    carbon_send_data_ERR_NOT_CONNECTED,
    carbon_send_data_ERR_CAN_NOT_SEND,
    carbon_send_data_ERR_DROPPED, // TODO: figure out what DROPPED actually means
    carbon_send_data_ERR_PAYLOAD_LENGTH,
    carbon_send_data_ERR_NOT_AUTONOMOUS,
};
enum carbon_send_data_status carbon_send_data(struct carbon_ctx * ctx, void const * data, size_t len);

static inline bool carbon_send_data_is_recoverable(enum carbon_send_data_status s) {
    bool ret = false;

    switch (s) {
    case carbon_send_data_OK:
    case carbon_send_data_ERR_RECOVERABLE_CHANNEL_ACCESS_FAILURE:
    case carbon_send_data_ERR_RECOVERABLE_NACK:
        ret = true;
        break;

    case carbon_send_data_ERR_XFER_COMMUNICATION:
    case carbon_send_data_ERR_NOT_CONNECTED:
    case carbon_send_data_ERR_CAN_NOT_SEND:
    case carbon_send_data_ERR_DROPPED:
    case carbon_send_data_ERR_PAYLOAD_LENGTH:
    case carbon_send_data_ERR_NOT_AUTONOMOUS:
        break;
    }

    return ret;
}


/* Poll the Atom for received data. If the buffer provided is not
 * large enough to hold the received frame, as much as possible will
 * be copied in and a status of _OK_TRUNCATED will be returned.
 *
 * Parameters:
 *   - ctx: the carbon context (required)
 *   - data: the buffer to copy RX data into (required)
 *   - len: the length of the buffer (required)
 *   - used: how much of the buffer was used (required)
 *   - drops: how many packets have been dropped due to a low polling
 *            rate since the Atom was last powered on (optional)
 *
 * Returns:
 *   - _OK_DATA: when received bytes are copied into data
 *   - _OK_DATA_TRUNCATED: when the buffer was not large enough to hold
 *       the entire RX packet
 *   - _OK_NO_DATA: no data was received
 *   - _NEEDS_RESET: the atom received a firmware upgrade and needs to
 *       be reset
 */
enum carbon_poll_data_status {
    carbon_poll_data_OK_DATA,
    carbon_poll_data_OK_DATA_TRUNCATED,
    carbon_poll_data_OK_NO_DATA,
    carbon_poll_data_OK_NEEDS_RESET,

    carbon_poll_data_ERR_XFER_COMMUNICATION,
};
enum carbon_poll_data_status carbon_poll_data(struct carbon_ctx * ctx,
                                              void * data, size_t len, size_t * used,
                                              uint32_t * drops);

/* This is defined by the PAN frame. We set it here as a helper to
 * users of Carbon so that they can avoid ever getting a
 * `_DATA_TRUNCATED` response. */
#define CARBON_TX_MAX_SIZE (107)
#define CARBON_POLL_MAX_RX_SIZE (107)

#endif /* CARBON_H */

#ifdef __cplusplus
}
#endif

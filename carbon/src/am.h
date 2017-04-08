#ifndef AM_H
#define AM_H

#include <stdbool.h>
#include <stdint.h>

#include "am_frame_atom_api.h"

struct am_ctx {
    /* The sequence number for Atom API type. */
    uint16_t seq;

    /* The Atom API framing context. */
    struct amfaa_ctx aactx;

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



#define AM_CONNECTION_TIMEOUT (1 * 60) /* seconds */

/* Called once at application startup. */
void am_init(struct am_ctx * ctx, struct am_transport_iface const * iface);

/* Called after _init to validate the Atom schema fingerprint. */
bool am_check_atom_fingerprint(struct am_ctx * ctx);

/* Called to enable communication with the Atom by powering it on. */
void am_enable(struct am_ctx * ctx);

/* Called to disable communication with the Atom and save power by turning it off. */
void am_disable(struct am_ctx * ctx);

/* Return the time in seconds since the Unix Epoch. 0 is returned if
 * there is not enough information to calculate calendar time. */
uint32_t am_calendar_time(struct am_ctx * ctx);

enum am_connect_status {
    am_connect_OK,
    am_connect_ERR_TIMEOUT,
    am_connect_ERR_AUTONOMOUS,
    am_connect_ERR_CONNECT,
    am_connect_ERR_CONNECT_WAIT,
    am_connect_ERR_GET_INFO,
};
enum am_connect_status am_connect(struct am_ctx * ctx);

enum am_sleep_status {
    am_sleep_OK,
    am_sleep_ERR_COMMUNICATION,
};
enum am_sleep_status am_sleep(struct am_ctx * ctx);

// poll for data
// send data

#endif /* AM_H */

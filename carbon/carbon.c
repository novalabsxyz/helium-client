#include "carbon.h"

#include "api/carbon_api_constructors.h"
#include "api/carbon_api_extractors.h"
#include "xfer/carbon_xfer.h"

#include "carbon_interface_helpers.h"

#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#define ATOM_INFO_MESSAGE_SIZE (  \
    20 /* the hash */ +                         \
    4 /* the version */ +                       \
    4 /* the uptime */)

struct atom_info {
    uint8_t fingerprint[20];
    uint8_t version[4];
    uint32_t uptime;
};

static uint16_t next_seq(struct carbon_ctx * ctx);
static void log_info(struct carbon_transport_iface const * iface, struct atom_info const * info);

void carbon_init(struct carbon_ctx * ctx, struct carbon_transport_iface const * iface) {
    assert(iface->tx);
    assert(iface->rx);
    assert(iface->delay_quarter_seconds);
    assert(iface->get_system_time);

    *ctx = (struct carbon_ctx) {
        .seq = 0,
        .cactx = {
            .iface = iface,
        },
    };
    transport_init(ctx->cactx.iface);
}

void carbon_enable(struct carbon_ctx * ctx) {
    transport_enable(ctx->cactx.iface);
}

void carbon_disable(struct carbon_ctx * ctx) {
    transport_disable(ctx->cactx.iface);
}

uint32_t carbon_calendar_time(struct carbon_ctx * ctx) {
    assert(ctx);

    struct a_resp_get_atom_info * const ai = &ctx->atom_info;
    if (ai->status != a_status_success) {
        /* Not enough info to derive a calendar time. */
        return 0;
    }

    uint64_t * const sync_time = &ctx->atom_info_sync_time;
    uint64_t const now = time_get_system_time(ctx->cactx.iface);
    assert(now >= *sync_time);

    uint64_t const ai_milliseconds = (uint64_t)ai->time.msec + ((uint64_t)ai->time.sec * 1000llu);
    uint64_t const sync_delta = now - *sync_time;
    uint64_t const calendar_now_msec = ai_milliseconds + sync_delta;
    uint64_t const calendar_now_sec = calendar_now_msec / 1000;

    assert(calendar_now_sec <= UINT32_MAX);

    return (uint32_t)calendar_now_sec;
}

uint64_t carbon_system_time(struct carbon_ctx * ctx) {
    return time_get_system_time(ctx->cactx.iface);
}

bool carbon_check_atom_fingerprint(struct carbon_ctx * ctx) {
    (void)ctx;

    /* A union to cast a buffer to an object. */
    union {
        struct atom_info obj;
        uint8_t buff[ATOM_INFO_MESSAGE_SIZE];
    } info = { .obj = { .uptime = 0 } };

    uint8_t const dummy = 0;

    {
        enum carbon_xfer_tx_give_status tstat;
        struct carbon_xfer_tx_ctx tx_ctx;

        /* Sending a frame with no payload will cause the Atom to
         * reply with its fingerprint information, version
         * information, and uptime. */
        carbon_xfer_tx_start(&tx_ctx, 0);
        tstat = carbon_xfer_tx_give(ctx->cactx.iface, &tx_ctx, &dummy, 0);
        assert(carbon_xfer_tx_give_DONE == tstat);
    }

    {
        enum carbon_xfer_rx_get_status rstat;
        struct carbon_xfer_rx_ctx rx_ctx;

        carbon_xfer_rx_init(&rx_ctx);

        size_t used;
        /* We ignore the return value and rely on used entirely. */
        rstat = carbon_xfer_rx_get(ctx->cactx.iface, &rx_ctx, info.buff, sizeof(info.buff), &used);
        assert(carbon_xfer_rx_get_MORE == rstat);
        assert(used == sizeof(info.buff));

        rstat = carbon_xfer_rx_flush(ctx->cactx.iface, &rx_ctx);
        assert(carbon_xfer_rx_get_DONE == rstat);
    }

    uint8_t const exp_fingerprint[] = SCHEMA_FP_helium_atom_api;
    assert(sizeof(exp_fingerprint) == sizeof(info.obj.fingerprint));

    log_info(ctx->cactx.iface, &info.obj);

    if (0 == memcmp(exp_fingerprint, info.obj.fingerprint, sizeof(info.obj.fingerprint))) {
        logging_printf(ctx->cactx.iface, "fingerprint ok\n");
        return true;
    } else {
        return false;
    }
}

enum carbon_read_mac_status carbon_read_mac(struct carbon_ctx * ctx, uint64_t * mac) {
    enum carbon_api_status astat;

    astat = carbon_api(&ctx->cactx, new__config_cmd__read_mac(&ctx->cmd, next_seq(ctx)));
    struct a_resp_u64 const * r_mac_resp = extract__config_cmd__read_mac(&ctx->cmd);

    if (carbon_api_status_ok == astat && r_mac_resp && r_mac_resp->status == a_status_success) {
        *mac = r_mac_resp->value;
        return carbon_read_mac_OK;
    } else {
        return carbon_read_mac_ERR_COMMUNICATION;
    }
}

enum carbon_connection_state_status carbon_connection_state(struct carbon_ctx * ctx) {
    enum carbon_api_status astat;

    astat = carbon_api(&ctx->cactx, new__node_cmd__connection_status(&ctx->cmd, next_seq(ctx)));
    bool const * r_connection_state = extract__node_cmd__connection_status(&ctx->cmd);

    if (carbon_api_status_ok == astat && r_connection_state) {
        if (*r_connection_state) {
            return carbon_connection_state_CONNECTED;
        } else {
            return carbon_connection_state_NOT_CONNECTED;
        }
    } else {
        return carbon_connection_state_ERR_COMMUNICATION;
    }
}

enum carbon_connect_status carbon_connect(struct carbon_ctx * ctx) {
    enum carbon_api_status astat;

    // TODO: check the connection state before we actually connect

    logging_printf(ctx->cactx.iface, "enter autonomous mode\n");
    astat = carbon_api(&ctx->cactx, new__node_cmd__set_mode(&ctx->cmd, next_seq(ctx), n_mode_autonomous));
    enum a_status const * r_set_mode = extract__node_cmd__set_mode(&ctx->cmd);
    if (!((carbon_api_status_ok == astat) &&
          r_set_mode &&
          (*r_set_mode == a_status_success))) {
        logging_printf(ctx->cactx.iface, "....error\n");
        return carbon_connect_ERR_AUTONOMOUS;
    }

    logging_printf(ctx->cactx.iface, "perform connect\n");
    uint32_t const cal_time = carbon_calendar_time(ctx);
    astat = carbon_api(&ctx->cactx,
                       new__node_cmd__connect__quick(&ctx->cmd,
                                                     next_seq(ctx),
                                                     cal_time,
                                                     &ctx->connection));
    enum n_cmd_connect_resp const * r_connect = extract__node_cmd__connect(&ctx->cmd);
    if (carbon_api_status_ok == astat && r_connect) {
        if (*r_connect == n_cmd_connect_resp_ok) {
            logging_printf(ctx->cactx.iface, "....using quick connect\n");
        } else if (*r_connect == n_cmd_connect_resp_err_fallback_to_slow_connect) {
            logging_printf(ctx->cactx.iface, "....using slow connect\n");
        } else {
            logging_printf(ctx->cactx.iface, "....error\n");
            return carbon_connect_ERR_CONNECT;
        }
    } else {
        logging_printf(ctx->cactx.iface, "....error\n");
        return carbon_connect_ERR_CONNECT;
    }

    logging_printf(ctx->cactx.iface, "wait for connection\n");
    uint32_t remaining_quarters = CARBON_CONNECTION_TIMEOUT * 4;
    while (--remaining_quarters) {
        enum carbon_connection_state_status ccss;
        ccss = carbon_connection_state(ctx);

        if (ccss == carbon_connection_state_CONNECTED) {
            logging_printf(ctx->cactx.iface, "....connected\n");
            break;
        } else if (ccss == carbon_connection_state_NOT_CONNECTED) {
            logging_printf(ctx->cactx.iface, "....not connected yet\n");
            time_delay_quarter_seconds(ctx->cactx.iface, 1);
        } else if (ccss == carbon_connection_state_ERR_COMMUNICATION) {
            logging_printf(ctx->cactx.iface, "....error\n");
            return carbon_connect_ERR_CONNECT_WAIT;
        } else {
            assert(0);
        }
    }

    if (0 == remaining_quarters) {
        logging_printf(ctx->cactx.iface, "....connect timeout\n");
        return carbon_connect_ERR_CONNECT_TIMEOUT;
    }

    logging_printf(ctx->cactx.iface, "get atom info\n");
    astat = carbon_api(&ctx->cactx,
                       new__config_cmd__get_atom_info(&ctx->cmd, next_seq(ctx)));
    struct a_resp_get_atom_info const * r_atom_info = extract__config_cmd__get_atom_info(&ctx->cmd);
    if (!((carbon_api_status_ok == astat) &&
          r_atom_info &&
          (r_atom_info->status == a_status_success))) {
        logging_printf(ctx->cactx.iface, "....error\n");
        return carbon_connect_ERR_GET_INFO;
    } else {
        ctx->atom_info_sync_time = ctx->cactx.iface->get_system_time(ctx->cactx.iface->param);
        ctx->atom_info = *r_atom_info;
        logging_printf(ctx->cactx.iface, "....info saved\n");
    }

    return carbon_connect_OK;
}

enum carbon_sleep_status carbon_sleep(struct carbon_ctx * ctx) {
    enum carbon_api_status astat;

    logging_printf(ctx->cactx.iface, "going to sleep\n");
    astat = carbon_api(&ctx->cactx, new__node_cmd__sleep(&ctx->cmd, next_seq(ctx)));
    struct n_connection const * r_connection = extract__node_cmd__sleep(&ctx->cmd);
    if (carbon_api_status_ok == astat && r_connection) {
        ctx->connection = *r_connection;
        return carbon_sleep_OK;
    } else {
        return carbon_sleep_ERR_COMMUNICATION;
    }
}

enum carbon_send_data_status carbon_send_data(struct carbon_ctx * ctx, void const * data, size_t len) {
    enum carbon_api_status astat;

    logging_printf(ctx->cactx.iface, "sending %" PRIu32 " bytes\n", (uint32_t)len);
    astat = carbon_api(&ctx->cactx, new__node_cmd__node_send(&ctx->cmd, next_seq(ctx), data, len));
    struct n_send_resp const * r_send_resp = extract__node_cmd__node_send(&ctx->cmd);

    enum carbon_send_data_status ret = carbon_send_data_ERR_XFER_COMMUNICATION;

    if (carbon_api_status_ok == astat && r_send_resp) {
        switch (r_send_resp->_tag) {
        case n_send_resp_tag_err:
            switch (r_send_resp->err) {
            case n_send_err_not_connected:
                ret = carbon_send_data_ERR_NOT_CONNECTED;
                break;
            case n_send_err_radio_cant_send:
                ret = carbon_send_data_ERR_CAN_NOT_SEND;
                break;
            case n_send_err_dropped:
                ret = carbon_send_data_ERR_DROPPED;
                break;
            case n_send_err_payload_len:
                ret = carbon_send_data_ERR_PAYLOAD_LENGTH;
                break;
            case n_send_err_not_autonomous:
                ret = carbon_send_data_ERR_NOT_AUTONOMOUS;
                break;
            }
            break;
        case n_send_resp_tag_ok:
            switch (r_send_resp->ok.tx_status) {
            case n_send_tx_status_channel_access_failure:
                ret = carbon_send_data_ERR_RECOVERABLE_CHANNEL_ACCESS_FAILURE;
                break;
            case n_send_tx_status_nack:
                ret = carbon_send_data_ERR_RECOVERABLE_NACK;
                break;
            case n_send_tx_status_ack:
                ret = carbon_send_data_OK;
                break;
            }
            break;
        }
    }

    return ret;
}

enum carbon_poll_data_status carbon_poll_data(struct carbon_ctx * ctx,
                                              void * data, size_t len, size_t * used,
                                              uint32_t * drops) {
    assert(ctx);
    assert(data);
    assert(used);

    enum carbon_api_status astat;

    *used = 0;
    if (drops) {
        *drops = 0;
    }

    astat = carbon_api(&ctx->cactx, new__node_cmd__poll_data(&ctx->cmd, next_seq(ctx)));
    struct n_cmd_poll_data_resp const * r_poll_resp = extract__node_cmd__poll_data(&ctx->cmd);

    enum carbon_poll_data_status ret = carbon_poll_data_OK_NO_DATA;

    if (carbon_api_status_ok == astat && r_poll_resp) {
        if (drops) {
            *drops = r_poll_resp->frames_droped;
        }

        switch (r_poll_resp->poll_data._tag) {
        case n_poll_data_tag_none:
            /* No receive data was waiting on the Atom. */
            return carbon_poll_data_OK_NO_DATA;
        case n_poll_data_tag_frame:
        {
            /* Receive data was waiting on the Atom. */
            struct h_buf const * buf = &r_poll_resp->poll_data.frame.buf;
            size_t const rxlen = buf->_length;
            size_t const copylen = rxlen > len ? len : rxlen;

            memcpy(data, buf->elems, copylen);
            *used = copylen;

            if (rxlen > len) {
                return carbon_poll_data_OK_DATA_TRUNCATED;
            } else {
                return carbon_poll_data_OK_DATA;
            }
        }
        case n_poll_data_tag_err_not_autonomous:
            return carbon_poll_data_ERR_XFER_COMMUNICATION;
        case n_poll_data_tag_need_reset:
            return carbon_poll_data_OK_NEEDS_RESET;
        }
    } else {
        return carbon_poll_data_ERR_XFER_COMMUNICATION;
    }

    return ret;
}

static uint16_t next_seq(struct carbon_ctx * ctx) {
    return ctx->seq++;
}

static void log_info(struct carbon_transport_iface const * iface, struct atom_info const * info) {
    uint8_t const * f = info->fingerprint;
    char sha[41] = { 0 };
    snprintf(
        sha, sizeof(sha),
        "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X"
        "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
        f[0], f[1], f[2], f[3], f[4],
        f[5], f[6], f[7], f[8], f[9],
        f[10], f[11], f[12], f[13], f[14],
        f[15], f[16], f[17], f[18], f[19]);

    logging_printf(iface,
                   "fingerprint: %s, "
                   "uptime: %" PRIu32 ", "
                   "version: %u.%u.%u.%u\n",
                   sha, info->uptime,
                   info->version[0],
                   info->version[1],
                   info->version[2],
                   info->version[3]);
}

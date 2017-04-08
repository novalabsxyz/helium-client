#include "am.h"

#include "am_atom_api_constructors.h"
#include "am_atom_api_extractors.h"
#include "am_driver_transport.h"

#include <string.h>
#include <stdio.h>

#ifdef HOST_BUILD
#define LOG(FMT, ...) printf(FMT, __VA_ARGS__)
#define LOGSTR(STR) printf("%s: %s\n", __FUNCTION__, STR)
#else
#include "serial.h"
#define LOG(FMT, ...) serial_tx_f(NULL, NULL, FMT, __VA_ARGS__)
#define LOGSTR(STR) serial_tx_f(NULL, NULL, "%s: %s\n", __FUNCTION__, STR)
#endif

#define ATOM_INFO_MESSAGE_SIZE (  \
    20 /* the hash */ +                         \
    4 /* the version */ +                       \
    4 /* the uptime */)

struct atom_info {
    uint8_t fingerprint[20];
    uint8_t version[4];
    uint32_t uptime;
};

static uint16_t next_seq(struct am_ctx * ctx);
static void log_info(struct atom_info const * info);

void am_init(struct am_ctx * ctx, struct am_transport_iface const * iface) {
    assert(iface->init);
    assert(iface->enable);
    assert(iface->disable);
    assert(iface->tx);
    assert(iface->rx);
    assert(iface->delay_quarter_seconds);
    assert(iface->get_system_time);

    *ctx = (struct am_ctx) {
        .seq = 0,
        .aactx = {
            .iface = iface,
        },
    };
    ctx->aactx.iface->init(ctx->aactx.iface->param);
}

void am_enable(struct am_ctx * ctx) {
    ctx->aactx.iface->enable(ctx->aactx.iface->param);
}

void am_disable(struct am_ctx * ctx) {
    ctx->aactx.iface->disable(ctx->aactx.iface->param);
}

uint32_t am_calendar_time(struct am_ctx * ctx) {
    assert(ctx);

    struct a_resp_get_atom_info * const ai = &ctx->atom_info;
    if (ai->status != a_status_success) {
        /* Not enough info to derive a calendar time. */
        return 0;
    }

    uint64_t * const sync_time = &ctx->atom_info_sync_time;
    uint64_t const now = ctx->aactx.iface->get_system_time(ctx->aactx.iface->param);
    assert(now >= *sync_time);

    uint64_t const ai_milliseconds = (uint64_t)ai->time.msec + ((uint64_t)ai->time.sec * 1000llu);
    uint64_t const sync_delta = now - *sync_time;
    uint64_t const calendar_now_msec = ai_milliseconds + sync_delta;
    uint64_t const calendar_now_sec = calendar_now_msec / 1000;

    assert(calendar_now_sec <= UINT32_MAX);

    return (uint32_t)calendar_now_sec;
}

bool am_check_atom_fingerprint(struct am_ctx * ctx) {
    (void)ctx;

    /* A union to cast a buffer to an object. */
    union {
        struct atom_info obj;
        uint8_t buff[ATOM_INFO_MESSAGE_SIZE];
    } info = { .obj = { .uptime = 0 } };

    uint8_t const dummy = 0;

    {
        enum amd_uart_tx_stat tstat;
        struct uart_tx_ctx tx_ctx;

        /* Sending a frame with no payload will cause the Atom to
         * reply with its fingerprint information, version
         * information, and uptime. */
        amd_uart_tx_framed_start(&tx_ctx, 0);
        tstat = amd_uart_tx_framed_give(ctx->aactx.iface, &tx_ctx, &dummy, 0);
        assert(amdu_tx_frame_done == tstat);
    }

    {
        enum amd_uart_rx_stat rstat;
        struct uart_rx_ctx rx_ctx;

        rstat = amd_uart_rx_framed_init(&rx_ctx);
        assert(amd_uart_rx_ok == rstat);

        size_t used;
        /* We ignore the return value and rely on used entirely. */
        rstat = amd_uart_rx_framed_get(ctx->aactx.iface, &rx_ctx, info.buff, sizeof(info.buff), &used);
        assert(amd_uart_rx_frame_more == rstat);
        assert(used == sizeof(info.buff));

        rstat = amd_uart_rx_framed_flush(ctx->aactx.iface, &rx_ctx);
        assert(amd_uart_rx_frame_done == rstat);
    }

    uint8_t const exp_fingerprint[] = SCHEMA_FP_helium_atom_api;
    assert(sizeof(exp_fingerprint) == sizeof(info.obj.fingerprint));

    log_info(&info.obj);

    if (0 == memcmp(exp_fingerprint, info.obj.fingerprint, sizeof(info.obj.fingerprint))) {
        LOGSTR("fingerprint ok");
        return true;
    } else {
        return false;
    }
}

enum am_connect_status am_connect(struct am_ctx * ctx) {
    enum amf_atom_api_status astat;

    LOGSTR("enter autonomous mode");
    astat = amf_atom_api(&ctx->aactx, new__node_cmd__set_mode(&ctx->cmd, next_seq(ctx), n_mode_autonomous));
    enum a_status const * r_set_mode = extract__node_cmd__set_mode(&ctx->cmd);
    if (!((amfaa_status_ok == astat) &&
          r_set_mode &&
          (*r_set_mode == a_status_success))) {
        LOGSTR("....error");
        return am_connect_ERR_AUTONOMOUS;
    }

    LOGSTR("perform connect");
    uint32_t const cal_time = am_calendar_time(ctx);
    astat = amf_atom_api(&ctx->aactx,
                         new__node_cmd__connect__quick(&ctx->cmd,
                                                       next_seq(ctx),
                                                       cal_time,
                                                       &ctx->connection));
    enum n_cmd_connect_resp const * r_connect = extract__node_cmd__connect(&ctx->cmd);
    if (amfaa_status_ok == astat && r_connect) {
        if (*r_connect == n_cmd_connect_resp_ok) {
            LOGSTR("....using quick connect");
        } else if (*r_connect == n_cmd_connect_resp_err_fallback_to_slow_connect) {
            LOGSTR("....using slow connect");
        } else {
            LOGSTR("....error");
            return am_connect_ERR_CONNECT;
        }
    } else {
        LOGSTR("....error");
        return am_connect_ERR_CONNECT;
    }

    LOGSTR("wait for connection");
    while (true) {
        astat = amf_atom_api(&ctx->aactx, new__node_cmd__connection_status(&ctx->cmd, next_seq(ctx)));
        bool const * r_connected = extract__node_cmd__connection_status(&ctx->cmd);

        if (!((amfaa_status_ok == astat) && r_connected)) {
            LOGSTR("....error");
            return am_connect_ERR_CONNECT_WAIT;
        } else {
            if (*r_connected) {
                LOGSTR("....connected");
                break;
            } else {
                ctx->aactx.iface->delay_quarter_seconds(ctx->aactx.iface->param, 1);
            }
        }
    }

    LOGSTR("get atom info");
    astat = amf_atom_api(&ctx->aactx,
                         new__config_cmd__get_atom_info(&ctx->cmd, next_seq(ctx)));
    struct a_resp_get_atom_info const * r_atom_info = extract__config_cmd__get_atom_info(&ctx->cmd);
    if (!((amfaa_status_ok == astat) &&
          r_atom_info &&
          (r_atom_info->status == a_status_success))) {
        LOGSTR("....error");
        return am_connect_ERR_GET_INFO;
    } else {
        ctx->atom_info_sync_time = ctx->aactx.iface->get_system_time(ctx->aactx.iface->param);
        ctx->atom_info = *r_atom_info;
        LOGSTR("....info saved");
        LOG("%s: ....%u\n", __FUNCTION__, ctx->atom_info.time.sec);
    }

    return am_connect_OK;
}

enum am_sleep_status am_sleep(struct am_ctx * ctx) {
    enum amf_atom_api_status astat;

    LOGSTR("going to sleep");
    astat = amf_atom_api(&ctx->aactx, new__node_cmd__sleep(&ctx->cmd, next_seq(ctx)));
    struct n_connection const * r_connection = extract__node_cmd__sleep(&ctx->cmd);
    if (amfaa_status_ok == astat && r_connection) {
        ctx->connection = *r_connection;
        return am_sleep_OK;
    } else {
        return am_sleep_ERR_COMMUNICATION;
    }
}

static uint16_t next_seq(struct am_ctx * ctx) {
    return ctx->seq++;
}

static void log_info(struct atom_info const * info) {
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

    LOG("sha: %s, "
        "uptime: %u, "
        "version: %u.%u.%u.%u\n",
        sha, info->uptime,
        info->version[0],
        info->version[1],
        info->version[2],
        info->version[3]);
}

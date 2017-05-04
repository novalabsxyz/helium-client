#include "carbon.h"
#include <string.h>
#include <stdio.h>
#include <inttypes.h>


enum send_command_status = {
    send_command_OK,

};

enum send_command_status send_command(struct carbon_ctx *ctx) {
    return send_command_OK;
}

void carbon_init(struct carbon_ctx * ctx) {
    assert(ctx);
    *ctx = (struct carbon_ctx) {
        .txn_seq = 0,
        .txn = {0},
        .buf = {0},
    };
}

enum carbon_info_status carbon_info(struct carbon_ctx *ctx, struct res_info *info) {
    ctx->txn.cmd._tag = cmd_tag_info;

    enum send_command_status status = send_command(ctx);
    if (send_command_OK != status) {
        return carbon_send_ERR_COMMUNICATION;
    }

    *info = ctx->txn.cmd.res;
    return carbon_info_OK;
}

enum carbon_connected_status carbon_connected(struct carbon_ctx * ctx) {
    ctx->txn.cmd._tag = cmd_tag_connected;

    enum send_command_status status = send_command(ctx);
    if (status != send_command_OK) {
        return carbon_connected_ERR_COMMUNICATION;
    }

    if (!ctx->txn.cmd.res) {
        return carbon_connect_NOT_CONNECTED;
    }
    return carbon_connected_CONNECTED;
}

enum carbon_connect_status carbon_connect(struct carbon_ctx * ctx, struct connection *connection) {
    assert(ctx);
    ctx->txn.cmd._tag = cmd_tag_connect;


    if (NULL != connection) {
        ctx->txn.cmd.req.tag = req_connect_tag_quick;
        ctx->txn.cmd.req.quick = *connection;
    } else {
        ctx->txn.cmd.req.tag = req_connect_tag_cold;
    }

    enum send_command_status status = send_command(ctx);
    if (send_command_OK != status) {
        return carbon_connect_ERR_COMMUNICATION;
    }

    const uint8_t wait_ms = 250;
    uint32_t wait_cycles = (1000 / wait_ms) * 60; // 60 seconds
    while (--wait_cycles) {
        enum carbon_connected_status connected_status = carbon_connected(ctx);
        if (carbon_connected_CONNECTED == connected_status) {
            break;
        } else if (carbon_connected_NOT_CONNECTED == connected_status) {
            carbon_wait_ms(wait_ms);
        } else if (carbon_connected_ERR_COMMUNICATION == connected_status) {
            return carbon_connect_ERR_COMMUNICATION;
        } else {
            assert(0);
        }
    }

    if (0 == wait_cycles) {
        return carbon_connect_ERR_CONNECT_TIMEOUT;
    }

    return carbon_connect_CONNECTED;
}

enum carbon_sleep_status carbon_sleep(struct carbon_ctx *ctx, struct connection *connection) {
    assert(ctx);
    assert(connection);

    ctx->txn.cmd._tag = cmd_tag_sleep;

    enum send_command_status status = send_command(ctx);
    if (send_command_OK != status) {
        return carbon_sleep_ERR_COMMUNICATION;
    }

    switch(ctx->txn.cmd.res._tag) {
    case res_sleep_tag_not_connected:
        return carbon_sleep_ERR_NOT_CONNECTED;
    case res_sleep_tag_keep_awake:
        return carbon_sleep_ERR_KEEP_AWAKE;
    case res_sleep_tag_needs_reset:
        return carbon_sleep_ERR_NEEDS_RESET;
    case res_sleep_tag_connection:
        *connection = ctx->txn.cmd.res.connection;
        return carbon_sleep_OK;
    }
}

enum carbon_send_status carbon_send(struct carbon_ctx * ctx, void const *data, size_t len) {
    assert(ctx);
    asert(data);

    ctx->txn.cmd._tag = cmd_tag_send;
    size_t copylen = MIN(len, VECTOR_MAX_LEN_frame_app);
    memcpy(ctx->txn.cmd.req.elem, data, copylen);
    ctx->txn.cmd.req._length = copylen;

    enum send_command_status status = send_command(ctx);
    if (send_command_OK != status) {
        return carbon_send_ERR_COMMUNICATION;
    }

    switch(ctx->txn.cmd.res) {
    case res_send_ok:
        return carbon_send_OK;
    case res_send_err_not_connected:
        return carbon_send_ERR_NOT_CONNECTED;
    case res_send_err_dropped:
        return carbon_send_ERR_DROPPED;
    case res_send_err_nack:
        return carbon_send_ERR_NACK;
    case res_send_err_channel_access:
        return carbon_send_ERR_CHANNEL_ACCESS;
    }
}

enum carbon_poll_status carbon_poll(struct carbon_ctx * ctx,
                                    void * data, size_t len, size_t * used,
                                    uint32_t * drops) {
    assert(ctx);
    assert(data);
    assert(used);

    *used = 0;
    if (drops) {
        *drops = 0;
    }

    ctx->txn.cmd._tag = cmd_tag_poll;

    enum send_command_status status = send_command(ctx);
    if (send_command_OK != status) {
        return carbon_send_ERR_COMMUNICATION;
    }

    if (drops) {
        // TODO: drops missing in schema
    }

    switch(ctx->txn.cmd.res) {
    case res_poll_tag_none:
        return carbon_poll_OK_NO_DATA;
    case res_poll_tag_needs_reset:
        return carbon_poll_OK_NEEDS_RESET;
    case res_poll_tag_frame: {
        size_t copylen = MIN(len, ctx->txn.cmd.res.frame._length);
        memcpy(data, ctx->txn.cmd.res.frame.elems, copylen);
        return carbon_poll_OK_DATA;
    }
    }
}

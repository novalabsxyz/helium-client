#include "carbon.h"
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>


enum send_command_status {
    send_command_OK,
    send_command_ERR_ENCODE,
    send_command_ERR_DECODE,
    send_command_ERR_COMMUNICATION,
};


enum send_command_status send_command(struct carbon_ctx *ctx) {
    uint16_t seq = ctx->txn_seq++;

    ctx->txn.seq = seq;

    struct caut_encode_iter ei;
    caut_encode_iter_init(&ei, ctx->buf, sizeof(ctx->buf));
    if (caut_status_ok != encode_txn(&ei, &ctx->txn)) {
        return send_command_ERR_ENCODE;;
    }

    size_t len = carbon_write(ctx->param, ctx->buf, ei.position);
    if (len != ei.position) {
        return send_command_ERR_COMMUNICATION;
    }

    len = carbon_read(ctx->param, ctx->buf, sizeof(ctx->buf));
    struct caut_decode_iter di;
    caut_decode_iter_init(&di, ctx->buf, len);
    if (caut_status_ok != decode_txn(&di, &ctx->txn)) {
        return send_command_ERR_DECODE;
    }

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

    *info = ctx->txn.cmd.info.res;
    return carbon_info_OK;
}

enum carbon_connected_status carbon_connected(struct carbon_ctx * ctx) {
    ctx->txn.cmd._tag = cmd_tag_connected;

    enum send_command_status status = send_command(ctx);
    if (status != send_command_OK) {
        return carbon_connected_ERR_COMMUNICATION;
    }

    if (!ctx->txn.cmd.connected.res) {
        return carbon_connect_NOT_CONNECTED;
    }
    return carbon_connected_CONNECTED;
}

enum carbon_connect_status carbon_connect(struct carbon_ctx * ctx, struct connection *connection) {
    assert(ctx);
    ctx->txn.cmd._tag = cmd_tag_connect;


    if (NULL != connection) {
        ctx->txn.cmd.connect.req._tag = req_connect_tag_quick;
        ctx->txn.cmd.connect.req.quick = *connection;
    } else {
        ctx->txn.cmd.connect.req._tag = req_connect_tag_cold;
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

    switch(ctx->txn.cmd.sleep.res._tag) {
    case res_sleep_tag_not_connected:
        return carbon_sleep_ERR_NOT_CONNECTED;
    case res_sleep_tag_keep_awake:
        return carbon_sleep_ERR_KEEP_AWAKE;
    case res_sleep_tag_needs_reset:
        return carbon_sleep_ERR_NEEDS_RESET;
    case res_sleep_tag_connection:
        *connection = ctx->txn.cmd.sleep.res.connection;
        return carbon_sleep_OK;
    }
    return carbon_sleep_ERR_COMMUNICATION;
}

enum carbon_send_status carbon_send(struct carbon_ctx * ctx, void const *data, size_t len) {
    assert(ctx);
    assert(data);

    ctx->txn.cmd._tag = cmd_tag_send;
    size_t copylen = len;
    if (len > VECTOR_MAX_LEN_frame_app) {
        len = VECTOR_MAX_LEN_frame_app;
    }
    memcpy(ctx->txn.cmd.send.req.elems, data, copylen);
    ctx->txn.cmd.send.req._length = copylen;

    enum send_command_status status = send_command(ctx);
    if (send_command_OK != status) {
        return carbon_send_ERR_COMMUNICATION;
    }

    switch(ctx->txn.cmd.send.res) {
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
    return carbon_send_ERR_COMMUNICATION;
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

    switch(ctx->txn.cmd.poll.res._tag) {
    case res_poll_tag_none:
        return carbon_poll_OK_NO_DATA;
    case res_poll_tag_needs_reset:
        return carbon_poll_OK_NEEDS_RESET;
    case res_poll_tag_frame: {
        size_t copylen = ctx->txn.cmd.poll.res.frame._length;
        if (len > copylen) {
            copylen = len;
        }
        memcpy(data, ctx->txn.cmd.poll.res.frame.elems, copylen);
        return carbon_poll_OK_DATA;
    }
    }
    return carbon_poll_ERR_COMMUNICATION;
}

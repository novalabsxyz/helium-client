#include "carbon.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>


#define SOF_CHAR (0x7E) ///< Start-of-frame character.

enum decode_state
{
    sof,
    len_msb,
    len_lsb,
    payload,
    checksum
};

// 1 second timeout
#define SERIAL_WAIT_TIMEOUT 2000
static inline bool
_wait_for_byte(struct carbon_ctx * ctx, size_t timeout)
{
    while (timeout--)
    {
        if (carbon_serial_readable(ctx->param))
        {
            return true;
        }
        else
        {
            carbon_wait_us(ctx->param, 500);
        }
    }
    return false;
}

static size_t
_read_frame(struct carbon_ctx * ctx, uint8_t * frame, size_t len)
{
    enum decode_state state            = sof;
    size_t            payload_size     = 0;
    uint8_t           payload_checksum = 0;

    while (_wait_for_byte(ctx, SERIAL_WAIT_TIMEOUT))
    {
        uint8_t ch;
        if (!carbon_serial_getc(ctx->param, &ch))
        {
            // Error reading
            return -3;
        }

        switch (state)
        {
        case sof:
            // Waiting for SOF
            if (ch == SOF_CHAR)
            {
                state = len_msb;
            }
            break;
        case len_msb:
            // Length high byte
            payload_size = ch << 8;
            state        = len_lsb;
            break;
        case len_lsb:
        {
            // Length low byte
            payload_size += ch;
            // Overflow error
            if (payload_size > len)
            {
                return -1;
            }
            len   = payload_size;
            state = payload;
        }
        break;
        case payload:
            *frame++ = ch;
            payload_checksum += ch;
            if (--len == 0)
            {
                payload_checksum = 0xFF - payload_checksum;
                state            = checksum;
            }
            break;
        case checksum:
            if (ch == payload_checksum)
            {
                return payload_size;
            }
            else
            {
                // Checksum error
                return -2;
            }
        default:
            break;
        }
    }
    // Timeout error
    return 0;
}

static size_t
_write_frame(struct carbon_ctx * ctx, uint8_t * frame, size_t len)
{
    if (len == 0)
    {
        return 0;
    }

    size_t written = 0;
#define CHECK_WRITE(ch, inc)                                                   \
    if (!carbon_serial_putc(ctx->param, (ch)))                                 \
    {                                                                          \
        return -1;                                                             \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        written += (inc);                                                      \
    }

    CHECK_WRITE(SOF_CHAR, 0);
    CHECK_WRITE(len >> 8, 0);
    CHECK_WRITE(len & 0xFF, 0);

    uint8_t checksum = 0;
    while (len--)
    {
        int8_t ch = *frame++;
        CHECK_WRITE(ch, 1);
        checksum += ch;
    }
    checksum = 0xFF - checksum;
    CHECK_WRITE(checksum, 0);

    return written;
}

enum send_command_status
{
    send_command_OK,
    send_command_ERR_ENCODE,
    send_command_ERR_DECODE,
    send_command_ERR_COMMUNICATION,
};

static enum send_command_status
send_command(struct carbon_ctx * ctx)
{
    uint16_t seq = ctx->txn_seq++;

    ctx->txn.seq = seq;

    struct caut_encode_iter ei;
    caut_encode_iter_init(&ei, ctx->buf, sizeof(ctx->buf));
    if (caut_status_ok != encode_txn(&ei, &ctx->txn))
    {
        return send_command_ERR_ENCODE;
    }

    size_t len = _write_frame(ctx, ctx->buf, ei.position);
    if (len != ei.position)
    {
        return send_command_ERR_COMMUNICATION;
    }

    len = _read_frame(ctx, ctx->buf, sizeof(ctx->buf));
    if ((int)len <= 0)
    {
        return send_command_ERR_COMMUNICATION;
    }

    struct caut_decode_iter di;
    caut_decode_iter_init(&di, ctx->buf, len);
    if (caut_status_ok != decode_txn(&di, &ctx->txn))
    {
        return send_command_ERR_DECODE;
    }

    return send_command_OK;
}

void
carbon_init(struct carbon_ctx * ctx, void * param)
{
    memset(ctx, 0, sizeof(*ctx));
    if (NULL != param)
    {
        ctx->param = param;
    }
}

bool
carbon_needs_reset(struct carbon_ctx * ctx)
{
    return ctx->txn.needs_reset;
}

int
carbon_baud(struct carbon_ctx * ctx, enum carbon_baud baud)
{
    ctx->txn.cmd._tag      = cmd_tag_baud;
    ctx->txn.cmd.baud._tag = cmd_baud_tag_req;

    enum atom_baud atom_baud = atom_baud_b9600;
    switch (baud)
    {
    case carbon_baud_b115200:
        atom_baud = atom_baud_b115200;
        break;
    case carbon_baud_b57600:
        atom_baud = atom_baud_b57600;
        break;
    case carbon_baud_b38400:
        atom_baud = atom_baud_b38400;
        break;
    case carbon_baud_b19200:
        atom_baud = atom_baud_b19200;
        break;
    case carbon_baud_b14400:
        atom_baud = atom_baud_b14400;
        break;
    case carbon_baud_b9600:
        atom_baud = atom_baud_b9600;
        break;
    }
    ctx->txn.cmd.baud.req = atom_baud;

    enum send_command_status status = send_command(ctx);
    if (send_command_OK != status)
    {
        return carbon_info_ERR_COMMUNICATION;
    }

    return carbon_info_OK;
}

int
carbon_info(struct carbon_ctx * ctx, struct carbon_info * info)
{
    ctx->txn.cmd._tag      = cmd_tag_info;
    ctx->txn.cmd.info._tag = cmd_info_tag_req;

    enum send_command_status status = send_command(ctx);
    if (send_command_OK != status)
    {
        return carbon_info_ERR_COMMUNICATION;
    }

    info->mac         = ctx->txn.cmd.info.res.mac;
    info->uptime      = ctx->txn.cmd.info.res.uptime;
    info->time        = ctx->txn.cmd.info.res.time;
    info->fw_version  = ctx->txn.cmd.info.res.fw_version;
    info->radio_count = ctx->txn.cmd.info.res.radio_count;

    return carbon_info_OK;
}

int
carbon_connected(struct carbon_ctx * ctx)
{
    ctx->txn.cmd._tag           = cmd_tag_connected;
    ctx->txn.cmd.connected._tag = cmd_connected_tag_req;

    enum send_command_status status = send_command(ctx);
    if (status != send_command_OK)
    {
        return carbon_connected_ERR_COMMUNICATION;
    }

    if (!ctx->txn.cmd.connected.res)
    {
        return carbon_connected_NOT_CONNECTED;
    }
    return carbon_connected_CONNECTED;
}

int
carbon_connect(struct carbon_ctx * ctx, struct connection * connection)
{
    ctx->txn.cmd._tag         = cmd_tag_connect;
    ctx->txn.cmd.connect._tag = cmd_connect_tag_req;

    if (NULL != connection)
    {
        ctx->txn.cmd.connect.req._tag  = req_connect_tag_quick;
        ctx->txn.cmd.connect.req.quick = *connection;
    }
    else
    {
        ctx->txn.cmd.connect.req._tag = req_connect_tag_cold;
    }

    return send_command(ctx);
}

int
carbon_sleep(struct carbon_ctx * ctx, struct connection * connection)
{
    ctx->txn.cmd._tag       = cmd_tag_sleep;
    ctx->txn.cmd.sleep._tag = cmd_sleep_tag_req;

    enum send_command_status status = send_command(ctx);
    if (send_command_OK != status)
    {
        return carbon_sleep_ERR_COMMUNICATION;
    }

    switch (ctx->txn.cmd.sleep.res._tag)
    {
    case res_sleep_tag_not_connected:
        return carbon_sleep_ERR_NOT_CONNECTED;
    case res_sleep_tag_keep_awake:
        return carbon_sleep_ERR_KEEP_AWAKE;
    case res_sleep_tag_connection:
        if (connection)
        {
            *connection = ctx->txn.cmd.sleep.res.connection;
        }
        return carbon_sleep_OK;
    }
    return carbon_sleep_ERR_COMMUNICATION;
}


enum carbon_send_status
{
    carbon_send_OK,
    /* Some other Atom module condition caused us to fail. */
    carbon_send_ERR_NOT_CONNECTED,
    carbon_send_ERR_DROPPED,
    carbon_send_ERR_COMMUNICATION,
};

static enum carbon_send_status
carbon_send(struct carbon_ctx * ctx, void const * data, size_t len)
{
    ctx->txn.cmd._tag      = cmd_tag_send;
    ctx->txn.cmd.send._tag = cmd_send_tag_req;

    size_t copylen = data ? len : 0;
    if (copylen > VECTOR_MAX_LEN_frame_app)
    {
        copylen = VECTOR_MAX_LEN_frame_app;
    }

    if (data)
    {
        memcpy(ctx->txn.cmd.send.req.elems, data, copylen);
    }
    ctx->txn.cmd.send.req._length = copylen;

    // Atom already retries a number of times itself. This additional
    // retry count covers the application level errors.
    uint8_t retries = 3;
    while (retries-- > 0)
    {
        enum send_command_status status = send_command(ctx);
        if (send_command_OK != status)
        {
            return carbon_send_ERR_COMMUNICATION;
        }

        switch (ctx->txn.cmd.send.res)
        {
        case res_send_ok:
            return carbon_send_OK;
        case res_send_err_not_connected:
            return carbon_send_ERR_NOT_CONNECTED;
        case res_send_err_dropped:
            return carbon_send_ERR_DROPPED;
        case res_send_err_nack:
        case res_send_err_channel_access:
            // Loop back around to retry
            // No need to delay here since serial comms will add enough overhead
            break;
        }
    }
    return carbon_send_ERR_COMMUNICATION;
}

enum carbon_poll_status
{
    carbon_poll_OK_DATA,
    carbon_poll_OK_NO_DATA,
    carbon_poll_ERR_COMMUNICATION,
};

#define CARBON_POLL_WAIT_US 500000
#define CARBON_POLL_RETRIES_60S ((1000000 / CARBON_POLL_WAIT_US) * 60)

static enum carbon_poll_status
carbon_poll(struct carbon_ctx * ctx,
            void *              data,
            const size_t        len,
            size_t *            used,
            uint32_t            retries)
{
    ctx->txn.cmd._tag      = cmd_tag_poll;
    ctx->txn.cmd.poll._tag = cmd_poll_tag_req;

    while (retries-- > 0)
    {
        enum send_command_status status = send_command(ctx);
        if (send_command_OK != status)
        {
            return carbon_poll_ERR_COMMUNICATION;
        }

        switch (ctx->txn.cmd.poll.res._tag)
        {
        case res_poll_tag_none:
            break;
        case res_poll_tag_frame:
        {
            size_t copylen = ctx->txn.cmd.poll.res.frame._length;
            if (copylen > len)
            {
                copylen = len;
            }
            if (data)
            {
                memcpy(data, ctx->txn.cmd.poll.res.frame.elems, copylen);
            }
            if (used)
            {
                *used = copylen;
            }
            return carbon_poll_OK_DATA;
        }
        }
        if (retries > 0)
        {
            carbon_wait_us(ctx->param, CARBON_POLL_WAIT_US);
        }
    }

    return carbon_poll_OK_NO_DATA;
}


#define CHANNEL_CREATE 0x8b
#define CHANNEL_CREATED 0x8d
#define CHANNEL_CREATE_FAILED 0x8e

int
carbon_channel_create(struct carbon_ctx * ctx,
                      const char *        name,
                      size_t              len,
                      uint8_t *           channel_id)
{
    uint8_t * frame = ctx->buf;
    if (len > CARBON_MAX_CHANNEL_NAME_SIZE)
    {
        len = CARBON_MAX_CHANNEL_NAME_SIZE;
    }

    *frame++ = CHANNEL_CREATE;
    memcpy(frame, name, len);
    frame += len;

    enum carbon_send_status status = carbon_send(ctx, ctx->buf, frame - ctx->buf);
    switch (status)
    {
    case carbon_send_OK:
        break; // successfully transmitted
    case carbon_send_ERR_NOT_CONNECTED:
        return carbon_channel_create_ERR_NOT_CONNECTED;
    case carbon_send_ERR_DROPPED:
        return carbon_channel_create_ERR_DROPPED;
    case carbon_send_ERR_COMMUNICATION:
        return carbon_channel_create_ERR_COMMUNICATION;
    }

    // Now receive
    frame                               = ctx->buf;
    size_t                  used        = 0;
    enum carbon_poll_status poll_status = carbon_poll(ctx,
                                                      frame,
                                                      CARBON_MAX_DATA_SIZE,
                                                      &used,
                                                      CARBON_POLL_RETRIES_60S);

    switch (poll_status)
    {
    case carbon_poll_OK_DATA:
        break; // received some data
    case carbon_poll_OK_NO_DATA:
        return carbon_channel_create_ERR_TIMEOUT;
    case carbon_poll_ERR_COMMUNICATION:
        return carbon_channel_create_ERR_COMMUNICATION;
    }

    // poll_status == carbon_poll_OK_DATA
    if (used < 1)
    {
        return carbon_channel_create_ERR_COMMUNICATION;
    }

    switch (frame[0])
    {
    case CHANNEL_CREATED:
        if (used != 2)
        {
            return carbon_channel_create_ERR_COMMUNICATION;
        }
        *channel_id = frame[1];
        return carbon_channel_create_OK;
    case CHANNEL_CREATE_FAILED:
        return carbon_channel_create_ERR_FAILED;
    }

    return carbon_channel_create_ERR_COMMUNICATION;
}

#define CHANNEL_SEND 0x8c
#define CHANNEL_SEND_RESULT 0x90
#define CHANNEL_NOT_FOUND 0x8f

int
carbon_channel_send(struct carbon_ctx * ctx,
                    uint8_t             channel_id,
                    void const *        data,
                    size_t              len,
                    uint8_t *           result)
{
    uint8_t * frame = ctx->buf;
    if (len > CARBON_MAX_DATA_SIZE)
    {
        len = CARBON_MAX_DATA_SIZE;
    }

    *frame++ = CHANNEL_SEND;
    *frame++ = channel_id;
    *frame++ = 0;
    memcpy(frame, data, len);
    frame += len;

    enum carbon_send_status status = carbon_send(ctx, ctx->buf, frame - ctx->buf);
    switch (status)
    {
    case carbon_send_OK:
        break; // successfully transmitted
    case carbon_send_ERR_NOT_CONNECTED:
        return carbon_channel_send_ERR_NOT_CONNECTED;
    case carbon_send_ERR_DROPPED:
        return carbon_channel_send_ERR_DROPPED;
    case carbon_send_ERR_COMMUNICATION:
        return carbon_channel_send_ERR_COMMUNICATION;
    }

    // Now receive
    frame                               = ctx->buf;
    size_t                  used        = 0;
    enum carbon_poll_status poll_status = carbon_poll(ctx,
                                                      frame,
                                                      CARBON_MAX_DATA_SIZE,
                                                      &used,
                                                      CARBON_POLL_RETRIES_60S);

    switch (poll_status)
    {
    case carbon_poll_OK_DATA:
        break; // received some data
    case carbon_poll_OK_NO_DATA:
        return carbon_channel_send_ERR_TIMEOUT;
    case carbon_poll_ERR_COMMUNICATION:
        return carbon_channel_send_ERR_COMMUNICATION;
    }

    // poll_status == carbon_poll_OK_DATA
    if (used < 1)
    {
        return carbon_channel_send_ERR_COMMUNICATION;
    }
    switch (frame[0])
    {
    case CHANNEL_SEND_RESULT:
        if (used != 2)
        {
            return carbon_channel_send_ERR_COMMUNICATION;
        }
        if (result)
        {
            *result = frame[1];
        }
        return carbon_channel_send_OK;
    case CHANNEL_NOT_FOUND:
        return carbon_channel_send_ERR_NOT_FOUND;
    }

    return carbon_channel_send_ERR_COMMUNICATION;
}

#include "carbon.h"
#include <assert.h>
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
    assert(ctx);
    memset(ctx, 0, sizeof(*ctx));
    if (NULL != param)
    {
        ctx->param = param;
    }
}

int
carbon_info(struct carbon_ctx * ctx, struct res_info * info)
{
    ctx->txn.cmd._tag      = cmd_tag_info;
    ctx->txn.cmd.info._tag = cmd_info_tag_req;

    enum send_command_status status = send_command(ctx);
    if (send_command_OK != status)
    {
        return carbon_info_ERR_COMMUNICATION;
    }

    *info = ctx->txn.cmd.info.res;
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
    assert(ctx);
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

    enum send_command_status status = send_command(ctx);
    if (send_command_OK != status)
    {
        return carbon_connect_ERR_COMMUNICATION;
    }

    const uint32_t wait_us     = 2500;
    uint32_t       wait_cycles = (100000 / wait_us) * 60; // 60 seconds
    while (--wait_cycles)
    {
        enum carbon_connected_status connected_status = carbon_connected(ctx);
        if (carbon_connected_CONNECTED == connected_status)
        {
            break;
        }
        else if (carbon_connected_NOT_CONNECTED == connected_status)
        {
            carbon_wait_us(ctx->param, wait_us);
        }
        else if (carbon_connected_ERR_COMMUNICATION == connected_status)
        {
            return carbon_connect_ERR_COMMUNICATION;
        }
        else
        {
            assert(0);
        }
    }

    if (0 == wait_cycles)
    {
        return carbon_connect_ERR_CONNECT_TIMEOUT;
    }

    return carbon_connect_CONNECTED;
}

int
carbon_sleep(struct carbon_ctx * ctx, struct connection * connection)
{
    assert(ctx);
    assert(connection);

    ctx->txn.cmd._tag       = cmd_tag_sleep;
    ctx->txn.cmd.sleep._tag = cmd_sleep_tag_req;

    enum send_command_status status = send_command(ctx);
    if (send_command_OK != status)
    {
        return carbon_sleep_ERR_COMMUNICATION;
    }

    switch (ctx->txn.cmd.sleep.res.connection._tag)
    {
    case sleep_connection_tag_not_connected:
        return carbon_sleep_ERR_NOT_CONNECTED;
    case sleep_connection_tag_keep_awake:
        return carbon_sleep_ERR_KEEP_AWAKE;
    case sleep_connection_tag_connection:
        *connection = ctx->txn.cmd.sleep.res.connection.connection;
        return carbon_sleep_OK;
    case sleep_connection_tag_needs_reset:
        // TODO: REMOVE once schema fixes land
        return carbon_sleep_ERR_COMMUNICATION;
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
    assert(ctx);
    assert(data);

    ctx->txn.cmd._tag      = cmd_tag_send;
    ctx->txn.cmd.send._tag = cmd_send_tag_req;

    size_t copylen = len;
    if (copylen > VECTOR_MAX_LEN_frame_app)
    {
        copylen = VECTOR_MAX_LEN_frame_app;
    }
    memcpy(ctx->txn.cmd.send.req.elems, data, copylen);
    ctx->txn.cmd.send.req._length = copylen;

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
        assert(0); // TDB: Should ideally resend
    }
    return carbon_send_ERR_COMMUNICATION;
}

enum carbon_poll_status
{
    carbon_poll_OK_DATA,
    carbon_poll_OK_NO_DATA,
    carbon_poll_ERR_COMMUNICATION,
};

/* Poll the Atom for received data.
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
 *   - _OK_NO_DATA: no data was received
 *       be reset
 */
static enum carbon_poll_status
carbon_poll(struct carbon_ctx * ctx,
            void *              data,
            const size_t        len,
            size_t *            used,
            uint32_t *          drops)
{
    assert(ctx);
    assert(data);
    assert(used);

    *used = 0;
    if (drops)
    {
        *drops = 0;
    }

    ctx->txn.cmd._tag      = cmd_tag_poll;
    ctx->txn.cmd.poll._tag = cmd_poll_tag_req;

    enum send_command_status status = send_command(ctx);
    if (send_command_OK != status)
    {
        return carbon_poll_ERR_COMMUNICATION;
    }

    if (drops)
    {
        // TODO: drops missing in schema
    }

    switch (ctx->txn.cmd.poll.res.frame._tag)
    {
    case poll_frame_tag_none:
        return carbon_poll_OK_NO_DATA;
    case poll_frame_tag_frame:
    {
        size_t copylen = ctx->txn.cmd.poll.res.frame.frame._length;
        if (copylen > len)
        {
            copylen = len;
        }
        memcpy(data, ctx->txn.cmd.poll.res.frame.frame.elems, copylen);
        if (used)
        {
            *used = copylen;
        }
        return carbon_poll_OK_DATA;
    }
    }
    return carbon_poll_ERR_COMMUNICATION;
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
    frame                        = ctx->buf;
    size_t                  used = 0;
    enum carbon_poll_status poll_status;
    while (carbon_poll_OK_NO_DATA
           == (poll_status =
                   carbon_poll(ctx, frame, CARBON_MAX_DATA_SIZE, &used, NULL)))
    {
        carbon_wait_us(ctx->param, 500000);
    }

    switch (poll_status)
    {
    case carbon_poll_OK_DATA:
        break; // received some data
    case carbon_poll_OK_NO_DATA:
        // Should not happen
        return carbon_channel_create_ERR_COMMUNICATION;
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
    frame                        = ctx->buf;
    size_t                  used = 0;
    enum carbon_poll_status poll_status;
    while (carbon_poll_OK_NO_DATA
           == (poll_status =
                   carbon_poll(ctx, frame, CARBON_MAX_DATA_SIZE, &used, NULL)))
    {
        carbon_wait_us(ctx->param, 500000);
    }

    switch (poll_status)
    {
    case carbon_poll_OK_DATA:
        break; // received some data
    case carbon_poll_OK_NO_DATA:
        // Should not happen
        return carbon_channel_send_ERR_COMMUNICATION;
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

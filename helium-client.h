#ifndef HELIUM_CLIENT_H
#define HELIUM_CLIENT_H

#include "cauterize/atom_api.h"
#include "helium-client-error.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HELIUM_MAX_DATA_SIZE (VECTOR_MAX_LEN_frame_app)
#define HELIUM_MAX_CHANNEL_NAME_SIZE (VECTOR_MAX_LEN_frame_app - 1)

enum helium_baud
{
    helium_baud_b9600,
    helium_baud_b14400,
    helium_baud_b19200,
    helium_baud_b38400,
    helium_baud_b57600,
    helium_baud_b115200,
};

struct helium_info
{
    uint64_t mac;
    uint32_t uptime;
    uint32_t time;
    uint32_t fw_version;
    uint8_t  radio_count;
};

struct helium_ctx
{
    void * param;

    /* Internal state */
    uint16_t   txn_seq;
    struct txn txn;
    uint8_t    buf[HELIUM_MAX_DATA_SIZE];
};

void
helium_init(struct helium_ctx * ctx, void * param);

bool
helium_needs_reset(struct helium_ctx * ctx);

int
helium_baud(struct helium_ctx * ctx, enum helium_baud baud);

int
helium_info(struct helium_ctx * ctx, struct helium_info * info);

int
helium_connected(struct helium_ctx * ctx);

int
helium_connect(struct helium_ctx * ctx, struct connection * connection);

int
helium_sleep(struct helium_ctx * ctx, struct connection * connection);

int
helium_channel_create(struct helium_ctx * ctx,
                      const char *        name,
                      size_t              len,
                      uint8_t *           channel_id);
int
helium_channel_send(struct helium_ctx * ctx,
                    uint8_t             channel_id,
                    void const *        data,
                    size_t              len,
                    uint8_t *           result);

extern bool
helium_serial_readable(void * param);
extern bool
helium_serial_getc(void * param, uint8_t * ch);
extern bool
helium_serial_putc(void * param, uint8_t ch);
extern void
helium_wait_us(void * param, uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* HELIUM_CLIENT_H */

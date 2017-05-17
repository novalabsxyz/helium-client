#ifndef CARBON_H
#define CARBON_H

#include "carbon-error.h"
#include "cauterize/atom_api.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CARBON_MAX_DATA_SIZE (VECTOR_MAX_LEN_frame_app)
#define CARBON_MAX_CHANNEL_NAME_SIZE (VECTOR_MAX_LEN_frame_app - 1)

struct carbon_ctx
{
    void * param;
    /* The sequence number for Atom transactions. */
    uint16_t   txn_seq;
    struct txn txn;
    uint8_t    buf[CARBON_MAX_DATA_SIZE];
};

/* Called once at application startup. */
void
carbon_init(struct carbon_ctx * ctx, void * param);
int
carbon_info(struct carbon_ctx * ctx, struct res_info * info);
int
carbon_connected(struct carbon_ctx * ctx);
int
carbon_connect(struct carbon_ctx * ctx, struct connection * connection);
int
carbon_sleep(struct carbon_ctx * ctx, struct connection * connection);

int
carbon_channel_create(struct carbon_ctx * ctx,
                      const char *        name,
                      size_t              len,
                      uint8_t *           channel_id);
int
carbon_channel_send(struct carbon_ctx * ctx,
                    uint8_t             channel_id,
                    void const *        data,
                    size_t              len,
                    uint8_t *           result);

extern bool
carbon_serial_readable(void * param);
extern bool
carbon_serial_getc(void * param, uint8_t * ch);
extern bool
carbon_serial_putc(void * param, uint8_t ch);
extern void
carbon_wait_us(void * param, uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* CARBON_H */

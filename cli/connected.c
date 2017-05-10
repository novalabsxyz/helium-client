#include "options.h"
#include "carbon.h"

static inline const char *str_connected_status(enum carbon_connected_status status) {
    switch (status) {
    case carbon_connected_CONNECTED:
        return NULL;
    case carbon_connected_NOT_CONNECTED:
        return NULL;
    case carbon_connected_ERR_COMMUNICATION:
        return "Error communicating with Atom";
    }

    return NULL;
}

int cli_connected(struct carbon_ctx *ctx, struct options *options) {
    (void)options;

    enum carbon_connected_status status = carbon_connected(ctx);

    if (status == carbon_connected_ERR_COMMUNICATION) {
        printf("%s\n", str_connected_status(status));
        return -1;
    }

    return status == carbon_connected_CONNECTED ? 0 : 1;
}

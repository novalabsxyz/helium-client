#include "options.h"
#include "carbon.h"
#include <inttypes.h>

static inline const char *str_info_status(enum carbon_info_status status) {
    switch (status) {
    case carbon_info_OK:
        return NULL;
    case carbon_info_ERR_COMMUNICATION:
        return "Error communicating with Atom";
    }

    return NULL;
}

int cli_info(struct carbon_ctx *ctx, struct options *options) {
    (void)options;

    struct res_info info;
    enum carbon_info_status status = carbon_info(ctx, &info);

    if (status != carbon_info_OK) {
        printf("%s\n", str_info_status(status));
        return -1;
    }

    printf("MAC:     %" PRIx64 "\n", info.mac);
    printf("Uptime:  %d\n", info.uptime);
    printf("Time:    %d\n", info.time);
    printf("Version: %x\n", info.fw_version);
    printf("Radios:  %d\n", info.radio_count);
    return 0;
}

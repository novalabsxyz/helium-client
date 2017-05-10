#include "options.h"
#include "carbon.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

static inline const char *str_connect_status(enum carbon_connect_status status) {
    switch (status) {
    case carbon_connect_CONNECTED:
        return NULL;
    case carbon_connect_NOT_CONNECTED:
        return "Atom failed to connect to network";
    case carbon_connect_ERR_CONNECT_TIMEOUT:
        return "Atom timeout while trying to connect to network";
    case carbon_connect_ERR_COMMUNICATION:
        return "Error communicating with Atom";
    }
    return NULL;
}

int cli_connect(struct carbon_ctx *ctx, struct options *options) {
    struct connection connection;
    if (options->filename) {
        int fd = open(options->filename, O_RDONLY);
        if (fd == -1) {
            printf("Error opening file: %s\n", strerror(errno));
            return -1;
        }
        if (read(fd, &connection, sizeof(connection)) != sizeof(connection)) {
            printf("Error reading connection data: %s", strerror(errno));
            return -1;
        }
        close(fd);
    }

    enum carbon_connect_status status =
        carbon_connect(ctx, options->filename ? &connection : NULL);

    if (status != carbon_connect_CONNECTED) {
        printf("%s\n", str_connect_status(status));
        return -1;
    }

    return 0;
}

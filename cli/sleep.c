#include "options.h"
#include "carbon.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


const char *str_sleep_status(enum carbon_sleep_status status) {
    switch(status){
    case carbon_sleep_OK:
        return NULL;
    case carbon_sleep_ERR_NOT_CONNECTED:
        return "Atom not connected to the network";
    case carbon_sleep_ERR_KEEP_AWAKE:
        return "Atom needs to stay awake";
    case carbon_sleep_ERR_NEEDS_RESET:
        return "Atom requires a reset";
    case carbon_sleep_ERR_COMMUNICATION:
        return "Error communicating with Atom";
    }

    return NULL;
}

int cli_sleep(struct carbon_ctx *ctx, struct options *options) {
    (void)options;
    (void)ctx;

    const char *outfile = options->filename ? options->filename : "connection.dat";

    struct connection connection;
    enum carbon_sleep_status status = carbon_sleep(ctx, &connection);

    if (status != carbon_sleep_OK) {
        printf("%s\n", str_sleep_status(status));
        return -1;
    }

    int fd = open(outfile, O_CREAT | O_WRONLY);
    if (fd == -1) {
        printf("Error opening output file: %s\n", strerror(errno));
        return -1;
    }

    if (write(fd, &connection, sizeof(connection)) != sizeof(connection)) {
        printf("Error writing connection data: %s\n", strerror(errno));
        return -1;
    }

    close(fd);
    return 0;
}

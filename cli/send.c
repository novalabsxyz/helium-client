#include "options.h"
#include "carbon.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

static inline const char *str_send_status(enum carbon_send_status status) {
    switch (status) {
    case carbon_send_OK:
        return NULL;
    case carbon_send_ERR_CHANNEL_ACCESS:
        return "Atom failed to acquire a network channel";
    case carbon_send_ERR_NACK:
        return "Atom failed to receive a network ack";
    case carbon_send_ERR_NOT_CONNECTED:
        return "Atom not connected to the network";
    case carbon_send_ERR_DROPPED:
        return "Atom dropped the packet";
    case carbon_send_ERR_COMMUNICATION:
        return "Error communicating with Atom";
    }
}

int cli_send(struct carbon_ctx *ctx, struct options *options) {
    if (!options->filename) {
        printf("Sending requires a filename (-f)\n");
        return -1;
    }

    int fd = open(options->filename, O_RDONLY);
    if (fd == -1) {
        printf("Error opening file: %s\n", strerror(errno));
        return -1;
    }

    struct stat stat;
    if (fstat(fd, &stat) == -1) {
        printf("Error getting file stats: %s", strerror(errno));
        return -1;
    }

    if (stat.st_size > CARBON_MAX_DATA_SIZE) {
        printf("File size %lld is too big to be sent (max: %d)",
               stat.st_size, CARBON_MAX_DATA_SIZE);
        return -1;
    }

    uint8_t data[CARBON_MAX_DATA_SIZE];
    if (read(fd, data, stat.st_size) != stat.st_size) {
        printf("Error reading data: %s", strerror(errno));
        return -1;
    }
    close(fd);

    enum carbon_send_status status = carbon_send(ctx, data, stat.st_size);

    if (status != carbon_send_OK) {
        printf("%s\n", str_send_status(status));
        return -1;
    }

    return 0;
}

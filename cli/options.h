#ifndef CARBON_CLI_OPTIONS_H
#define  CARBON_CLI_OPTIONS_H

#define OPTPARSE_IMPLEMENTATION
#define OPTPARSE_API static inline
#include "optparse.h"

#define DEFAULT_PORT "/dev/tty.usbserial-DN01IQCD"

struct options {
    struct optparse optparse;
    const char **argv;
    const char *port;
    const char *filename;
};

static inline void options_init(struct options *options, char **argv) {
    optparse_init(&options->optparse, argv);
    options->port = DEFAULT_PORT;
    options->filename = 0;
}

#endif // CARBON_CLI_OPTIONS_H

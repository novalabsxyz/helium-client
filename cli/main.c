#include "carbon.h"
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <poll.h>
#include <assert.h>
#include <inttypes.h>
#include "options.h"

bool carbon_serial_readable(void *param) {
    struct pollfd pollfd = {
        .fd = (int)param,
        .events = POLLIN,
    };
    if (poll(&pollfd, 1, -1) == 1) {
        return pollfd.revents & POLLIN;
    }
    return false;
}

bool carbon_serial_getc(void *param, uint8_t *ch) {
    return read((int)param, ch, 1) > 0;
}

bool carbon_serial_putc(void *param, uint8_t ch) {
    return write((int)param, &ch, 1) == 1;
}

void carbon_wait_ms(void *param, uint32_t ms) {
    (void)param;
    usleep(ms * 1000);
}


int set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

int open_serial_port(const char *portname)
{
    int fd;

    fd = open(portname, O_RDWR | O_NOCTTY | O_NONBLOCK);

    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
        return -1;
    }

    if (ioctl(fd, TIOCEXCL) < 0) {
        printf("Error setting TIOCEXCL on %s - %s(%d).\n",
               portname, strerror(errno), errno);
        return -1;
    }

    if (fcntl(fd, F_SETFL, 0) < 0) {
        printf("Error clearing O_NONBLOCK %s - %s(%d).\n",
               portname, strerror(errno), errno);
        return -1;
    }

    /*baudrate 115200, 8 bits, no parity, 1 stop bit */
    set_interface_attribs(fd, B115200);
    return fd;
}

static int usage(const char *app, const char *error) {
    if (error) {
        printf("%s: %s\n", app, error);
        return -1;
    }
    printf("Usage\n");
    return 0;
}

int (cli_connect)   (struct carbon_ctx *ctx, struct options *options);
int (cli_connected) (struct carbon_ctx *ctx, struct options *options);
int (cli_sleep)     (struct carbon_ctx *ctx, struct options *options);
int (cli_info)      (struct carbon_ctx *ctx, struct options *options);
int (cli_send)      (struct carbon_ctx *ctx, struct options *options);

struct cli_command {
    const char *name;
    int (*func)(struct carbon_ctx *ctx, struct options *options);
} commands[] = {
    { .name = "connect", .func = cli_connect},
    { .name = "connected", .func = cli_connected},
    { .name = "sleep", .func = cli_sleep},
    { .name = "info", .func = cli_info},
    { .name = "send", .func = cli_send},
    { 0, 0},
};

int main(int argc, char **argv) {
    (void)argc;
    int opt, longindex;

    struct options options;
    struct optparse_long longopts[] = {
        {"help", 'h', OPTPARSE_NONE},
        {"port", 'p', OPTPARSE_REQUIRED},
        {"file", 'f', OPTPARSE_REQUIRED},
        {0, 0, 0}
    };

    options_init(&options, argv);
    while((opt = optparse_long(&options.optparse, longopts, &longindex)) != -1) {
        switch(opt) {
        case 'h':
            return usage(argv[0], NULL);
        case 'p':
            options.port = options.optparse.optarg;
            break;
        case 'f':
            options.filename = options.optparse.optarg;
            break;
        case '?':
            return usage(argv[0], options.optparse.errmsg);
        }
    }

    char *arg_cmd = optparse_arg(&options.optparse);
    if (arg_cmd == NULL) {
        return usage(argv[0], "Missing command");
    }

    int fd = open_serial_port(options.port);
    if (fd < 0) {
        return fd;
    }

    struct carbon_ctx ctx;
    carbon_init(&ctx, (void *)(intptr_t)fd);

    int result = -1;
    for (struct cli_command *cmd = commands; cmd->name; cmd++) {
        if (strcmp(cmd->name, arg_cmd) == 0) {
            result = cmd->func(&ctx, &options);
            goto exit;
        }
    }

    return usage(argv[0], "Invalid command");

exit:
    close(fd);
    return result;
}

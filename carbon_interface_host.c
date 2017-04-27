#include "carbon_interface_host.h"

#include <unistd.h>
#include <assert.h>
#include <time.h>

static void host_transport_init(void * param) {
    (void)param;
}

static void host_transport_enable(void * param) {
    (void)param;
}

static void host_transport_disable(void * param) {
    (void)param;
}

static enum carbon_iface_tx_stat host_transport_tx(void * param, struct carbon_tx_buffer const * buffer) {
    (void)param;
    (void)buffer;

    assert(0);

    return carbon_iface_tx_ERR;
}

static enum carbon_iface_rx_stat host_transport_rx(void * param, struct carbon_rx_buffer * buffer) {
    (void)param;
    (void)buffer;

    assert(0);

    return carbon_iface_rx_ERR_TIMEOUT;
}

static void host_transport_delay_quarter_seconds(void * param, uint32_t quarters) {
    (void)param;
    usleep(1000 * 250 * quarters);
}

static uint64_t host_transport_get_system_time(void * param) {
    (void)param;

    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);

    time_t s = spec.tv_sec;
    uint64_t ms = spec.tv_nsec / 1000000;

    return (s * 1000) + ms;
}

struct carbon_transport_iface const carbon_transport_iface_host = {
    .param = NULL,
    .init = host_transport_init,
    .enable = host_transport_enable,
    .disable = host_transport_disable,
    .tx = host_transport_tx,
    .rx = host_transport_rx,
    .delay_quarter_seconds = host_transport_delay_quarter_seconds,
    .get_system_time = host_transport_get_system_time,
};

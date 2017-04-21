#ifndef CARBON_INTERFACE_HELPERS_H
#define CARBON_INTERFACE_HELPERS_H

#include "xfer/carbon_xfer.h"
#include "carbon_interface.h"
#include <assert.h>

static inline void transport_init(struct carbon_transport_iface const * iface) {
    assert(iface);

    if (iface->init) {
        iface->init(iface->param);
    }
}

static inline void transport_enable(struct carbon_transport_iface const * iface) {
    assert(iface);

    if (iface->enable) {
        iface->enable(iface->param);
    }
}

static inline void transport_disable(struct carbon_transport_iface const * iface) {
    assert(iface);

    if (iface->disable) {
        iface->disable(iface->param);
    }
}

static inline enum carbon_iface_tx_stat transport_tx(struct carbon_transport_iface const * iface,
                                                     struct carbon_tx_buffer const * buffer) {
    assert(iface);
    assert(iface->tx);

    return iface->tx(iface->param, buffer);
}

static inline enum carbon_iface_rx_stat transport_rx(struct carbon_transport_iface const * iface,
                                                     struct carbon_rx_buffer * buffer) {
    assert(iface);
    assert(iface->rx);

    return iface->rx(iface->param, buffer);
}

static inline void time_delay_quarter_seconds(struct carbon_transport_iface const * iface, uint32_t quarters) {
    assert(iface);
    assert(iface->delay_quarter_seconds);

    iface->delay_quarter_seconds(iface->param, quarters);
}

static inline uint64_t time_get_system_time(struct carbon_transport_iface const * iface) {
    assert(iface);
    assert(iface->get_system_time);

    return iface->get_system_time(iface->param);
}

static inline int logging_printf(struct carbon_transport_iface const * iface, char const * fmt, ...) {
    assert(iface);
    assert(fmt);

    if (iface->vprintf) {
        va_list args;
        va_start(args, fmt);

        int r = iface->vprintf(iface->param, fmt, args);

        va_end(args);

        return r;
    } else {
        return 0;
    }
}

#endif /*  AM_INTERFACE_HELPERS_H */

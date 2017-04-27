#ifndef CARBON_INTERFACE_H
#define CARBON_INTERFACE_H

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

#define CARBON_RX_BUFFER_SIZE (8)
#define CARBON_TX_BUFFER_SIZE (8)

enum carbon_iface_rx_stat {
    carbon_iface_rx_MORE,
    carbon_iface_rx_DONE,

    carbon_iface_rx_ERR_TIMEOUT,
};

enum carbon_iface_tx_stat {
    carbon_iface_tx_ERR,
    carbon_iface_tx_OK,
};

struct carbon_rx_buffer {
    enum carbon_iface_rx_stat stat;
    size_t used;
    uint8_t data[CARBON_RX_BUFFER_SIZE];
};

struct carbon_tx_buffer {
    size_t used;
    uint8_t data[CARBON_TX_BUFFER_SIZE];
};


typedef void transport_init_fn(void * param);
typedef void transport_enable_fn(void * param);
typedef void transport_disable_fn(void * param);
typedef enum carbon_iface_tx_stat transport_tx_fn(void * param, struct carbon_tx_buffer const * buffer);
typedef enum carbon_iface_rx_stat transport_rx_fn(void * param, struct carbon_rx_buffer * buffer);

typedef void time_delay_quarter_seconds_fn(void * param, uint32_t quarters);
typedef uint64_t time_get_system_time_fn(void * param);

typedef int logging_vprintf_fn(void * param, char const * fmt, va_list ap);

struct carbon_transport_iface {
    void * param;

    transport_init_fn * init;
    transport_enable_fn * enable;
    transport_disable_fn * disable;
    transport_tx_fn * tx;
    transport_rx_fn * rx;

    time_delay_quarter_seconds_fn * delay_quarter_seconds;
    time_get_system_time_fn * get_system_time;

    logging_vprintf_fn * vprintf;
};

#endif /* CARBON_INTERFACE_H */

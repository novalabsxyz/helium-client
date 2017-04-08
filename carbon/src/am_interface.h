#ifndef AM_INTERFACE_H
#define AM_INTERFACE_H

#ifndef AM_DRIVER_TRANSPORT_H
  #error "please include am_driver_transport.h before including this file"
#endif

#include <stdint.h>

struct uart_rx_buffer;

typedef void transport_init_fn(void * param);
typedef void transport_enable_fn(void * param);
typedef void transport_disable_fn(void * param);
typedef enum amd_uart_tx_stat transport_tx_fn(void * param, void const * data, size_t len);
typedef enum amd_uart_rx_stat transport_rx_fn(void * param, struct uart_rx_buffer * buffer);

typedef void transport_delay_quarter_seconds_fn(void * param, uint32_t quarters);
typedef uint64_t transport_get_system_time_fn(void * param);

struct am_transport_iface {
    void * param;

    transport_init_fn * init;
    transport_enable_fn * enable;
    transport_disable_fn * disable;
    transport_tx_fn * tx;
    transport_rx_fn * rx;
    transport_delay_quarter_seconds_fn * delay_quarter_seconds;
    transport_get_system_time_fn * get_system_time;
};

#endif /* AM_INTERFACE_H */

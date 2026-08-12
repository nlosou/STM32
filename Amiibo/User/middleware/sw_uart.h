#ifndef SW_UART_H
#define SW_UART_H

#include "gpio_port.h"
#include "uart_port.h"
#include "timer_port.h"
#include "stm32f10x_it.h"

typedef struct {
    gpio_port_t *RX;
    gpio_port_t *TX;
    Timer_port_t *timer;
    uint16_t RX_PIN;  
    uint16_t TX_PIN;  
}sw_uart_ctx_t; 

extern const uart_ops_t uart_ops;

#endif

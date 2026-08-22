#ifndef SW_UART_H
#define SW_UART_H

#include "gpio_port.h"
#include "uart_port.h"
#include "timer_port.h"
#include "exti_port.h"
#include "nvic_port.h"

typedef struct {
    gpio_port_t *RX;
    gpio_port_t *TX;
    Timer_port_t *time_tx;
    Timer_port_t *time_rx;
    exti_port_t *exti;
    nvic_port_t *nvic_timer_tx; 
    nvic_port_t *nvic_timer_rx; 
    nvic_port_t *nvic_exti; 
    uint16_t RX_PIN;  
    uint16_t TX_PIN;  
}sw_uart_ctx_t; 

typedef enum {
    Idel,
    Wait_start_bit,
    Sampling,
    Completed
}Uart_rx_sate;

typedef enum {
    TX_IDLE,
    TX_START,
    TX_DATA,
    TX_STOP,
    TX_COMPLETE,
}Uart_tx_sate;

extern const                uart_ops_t uart_ops;
extern volatile             Uart_rx_sate sw_uart_recieve_state;
extern volatile             Uart_tx_sate sw_uart_sate;

extern volatile uint8_t     Uart_tx_busy;
extern volatile uint8_t     Uart_tx_idx;
extern volatile uint8_t     uart_receive_data;
extern volatile uint8_t     bit_idx;
extern volatile uint8_t     fetch_complete;
extern volatile uint8_t     uart_transfer_idx;
extern volatile uint8_t     get_pin_level;
extern volatile uint32_t    flag;

extern uint8_t TX_tmep_bit[10];                      //默认填入开始位
#endif

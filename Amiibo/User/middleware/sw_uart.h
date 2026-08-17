#ifndef SW_UART_H
#define SW_UART_H

#include "gpio_port.h"
#include "uart_port.h"
#include "timer_port.h"
#include "exti_port.h"
#include "nvic_port.h"
#include "stm32f10x_it.h"

typedef struct {
    gpio_port_t *RX;
    gpio_port_t *TX;
    Timer_port_t *timer;
    exti_port_t *exti;
    nvic_port_t *nvic_timer; 
    nvic_port_t *nvic_exti; 
    uint16_t RX_PIN;  
    uint16_t TX_PIN;  
}sw_uart_ctx_t; 

typedef enum {
    Idel,
    Wait_start_bit,
    Check_start_bit,
    Sampling,
    Completed
}Uart_recieve_sate;


extern const uart_ops_t uart_ops;
extern volatile Uart_recieve_sate sw_uart_recieve_state;
extern volatile uint8_t uart_receive_data;
extern volatile uint8_t bit_idx;

#endif

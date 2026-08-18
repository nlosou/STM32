#ifndef UART_PORT_H
#define UART_PORT_H


#include <stdint.h>
#include <string.h>



#define parity_bits_on  1
#define parity_bits_off 0


typedef enum mode{
    Half_duplex,
    ful_duplex,
}Communicate_mode;

typedef struct {
    uint16_t tranfer_buf;
    uint16_t* recieve_buf;
    uint16_t tranfer_buf_len;
    uint16_t recieve_buf_len;
    uint8_t  parity_bits;
    Communicate_mode mode;
}uart_msg_t;


typedef struct {
    void (*init)(void *ctx);
    uint8_t (*transmit)(void*ctx,uart_msg_t* msg,uint16_t msg_num);
}uart_ops_t;

typedef struct {
    const uart_ops_t* ops;
    void *ctx;
}uart_port_t;

static inline void uart_init(uart_port_t *port)
{
    if(port != NULL&&port->ctx!=NULL&&port->ops!=NULL&&port->ops->init!=NULL)
    {
        port->ops->init(port->ctx);
    }
}

static inline void uart_transmit(uart_port_t *port,uart_msg_t* msg,uint16_t msg_num)
{
    if(port != NULL&&port->ctx!=NULL&&port->ops!=NULL&&port->ops->transmit!=NULL)
    {
        port->ops->transmit(port->ctx,msg,msg_num);
    }
}


#endif

#ifndef SPI_PORT_H
#define SPI_PORT_H
#include <stdint.h>
#define NULL 0
#define Read  1
#define Write 0
typedef struct {
    uint8_t len;
    uint8_t flags;
    uint8_t get_buf_len;
    uint8_t *buf;
}spi_msg_t;

typedef struct {
    void (*init)(void*ctx);
    uint32_t (*transmit)(void*ctx,spi_msg_t *msg,uint16_t num);
}spi_ops_t;


typedef struct {
    const spi_ops_t *ops;
   void *ctx; 
}spi_port_t;


static inline void spi_init(spi_port_t *port)
{
    if(port!=NULL && port->ops!=NULL && port->ctx!=NULL)
    {
        port->ops->init(port->ctx);
    }
}
static inline uint32_t spi_transmit(spi_port_t *port,spi_msg_t *msg,uint16_t num)
{
    if(port!=NULL && port->ops!=NULL && port->ctx!=NULL)
    {
        return port->ops->transmit(port->ctx,msg,num);
    }
    return 0;
}
#endif

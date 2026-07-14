#ifndef SPI_SELECT_OPP_H
#define SPI_SELECT_OPP_H


#include<stdint.h>
#include<stddef.h>

typedef struct {
    void (*select_device)(void*ctx,uint16_t cs_pin,uint8_t level);
}spi_select_ops_t;

typedef struct {
    const spi_select_ops_t *ops;
    void *ctx;
}spi_select_port_t;

static inline void spi_select(spi_select_port_t *port,uint16_t cs_pin, uint8_t level)
{
    if(port!=NULL && port->ops!=NULL && port->ctx!=NULL)
    {
        port->ops->select_device(port->ctx,cs_pin,level);
    }
}

#endif

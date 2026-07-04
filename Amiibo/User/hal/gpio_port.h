#ifndef GPIO_PORT_H
#define GPIO_PORT_H



#include <stdint.h>
#include <stdbool.h>
    
#define NULL 0

typedef enum {
    GPIO_LEVEL_LOW = 0,
    GPIO_LEVEL_HIGH= 1
}gpio_level_t;

typedef struct {
    void (*init)(void *ctx);
    void (*write)(void *ctx,uint16_t pins,gpio_level_t level);
    uint32_t (*read)(void *ctx,uint16_t pins);
    void (*toggle)(void *ctx,uint16_t pins);
}gpio_ops_t;

typedef struct {
    const gpio_ops_t *ops;
    void *ctx;
}gpio_port_t;

static inline void gpio_port_init(gpio_port_t *port)
{
    if((port!= NULL) && (port->ops!=NULL) && (port->ops->init != NULL))
    {
        port->ops->init(port->ctx);        
    }
}
static inline void gpio_port_write(gpio_port_t *port, uint16_t pins, gpio_level_t level)
{
    if ((port != NULL) && (port->ops != NULL) && (port->ops->write != NULL)) {
        port->ops->write(port->ctx, pins, level);
    }
}

static inline uint32_t gpio_port_read(gpio_port_t *port,uint16_t pins)
{
    uint32_t bit = 0;
    if ((port != NULL) && (port->ops != NULL) && (port->ops->write != NULL)) {
        bit = port->ops->read(port->ctx, pins);
    }
    return bit;
}

static inline void gpio_port_toggle(gpio_port_t *port, uint16_t pins)
{
    if ((port != NULL) && (port->ops != NULL) && (port->ops->toggle != NULL)) {
        port->ops->toggle(port->ctx, pins);
    }
}



#endif

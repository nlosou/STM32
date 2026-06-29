#ifndef I2C_PORT_H
#define I2C_PORT_H


#include <stdint.h>
#define NULL 0
typedef struct {
    void (*init)(void* ctx);
    uint8_t (*write)(void* ctx, uint8_t buf);
    uint8_t (*read)(void* ctx);
    void (*start)(void*ctx);
    void (*stop)(void*ctx);
}i2c_ops_t;

typedef struct {
    const i2c_ops_t *ops;
    void *ctx;
}i2c_port_t;

static inline void i2c_init(i2c_port_t *port)
{
    if(port!=NULL && port->ctx!=NULL  && port->ops->init!=NULL)
    {
        port->ops->init(port->ctx);
    }
}
static inline uint8_t i2c_write(i2c_port_t *port,uint8_t buf)
{
    return port->ops->write(port->ctx,buf);
}

static inline uint8_t i2c_read(i2c_port_t *port)
{
    if(port!=NULL && port->ctx!=NULL  && port->ops->read!=NULL)
    {
       return  port->ops->read(port->ctx);
    }
    return 0;
}

static inline void i2c_start(i2c_port_t *port)
{
    if(port!=NULL && port->ctx!=NULL  && port->ops->start!=NULL)
    {
       return  port->ops->start(port->ctx);
    }
}


static inline void i2c_stop(i2c_port_t *port)
{
    if(port!=NULL && port->ctx!=NULL  && port->ops->stop!=NULL)
    {
       return  port->ops->stop(port->ctx);
    }
}

#endif

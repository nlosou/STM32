#ifndef I2C_PORT_H
#define I2C_PORT_H


#include <stdint.h>
#define NULL 0
typedef struct {
    void (*init)(void* ctx);
    int (*write)(void* ctx,uint8_t dev_addr,const uint8_t *buf,uint32_t len);
    int (*read)(void* ctx,uint8_t dev_addr,uint8_t *buf,uint32_t len);
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
static inline int i2c_write(i2c_port_t *port,uint8_t dev_addr,uint8_t *buf,uint32_t len)
{
    if(port!=NULL && port->ctx!=NULL  && port->ops->write!=NULL)
    {
        port->ops->write(port->ctx,dev_addr,buf,len);
    }
}

static inline int i2c_read(i2c_port_t *port,uint8_t dev_addr,uint8_t *buf,uint32_t len)
{
    if(port!=NULL && port->ctx!=NULL  && port->ops->write!=NULL)
    {
        port->ops->read(port->ctx,dev_addr,buf,len);
    }
}

#endif

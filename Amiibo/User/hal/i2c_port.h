#ifndef I2C_PORT_H
#define I2C_PORT_H
#define I2C_M_RD 0x0001

#include <stdint.h>
#define NULL 0
typedef struct {
    uint16_t addr; // 
    uint16_t flags;
    uint16_t len;
    uint8_t *buf;
}i2c_msg_t;
typedef struct {
    void (*init)(void* ctx);
    uint16_t (*transfer)(void*ctx,i2c_msg_t *msgs,uint16_t num);
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
static inline  uint16_t i2c_transfer(i2c_port_t* port ,i2c_msg_t* msgs,uint16_t num)
{
    if(port!=NULL && port->ctx!=NULL  && port->ops->transfer!=NULL)
    {
        return  port->ops->transfer(port->ctx,msgs,num);     
    }
    return 0;
}
#endif

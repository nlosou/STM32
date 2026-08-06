#ifndef NVIC_PORT_H
#define  NVIC_PORT_H

#include <string.h>

typedef struct {
    void (*init)(void*ctx);
}nvic_ops;


typedef struct {
    void *ctx;
    const nvic_ops *ops;
}nvic_port_t;


static inline void nvic_init(nvic_port_t *port)
{
    if(port!=NULL&&port->ops!=NULL&&port->ctx!=NULL&&port->ops->init!=NULL)
    {
        port->ops->init(port);
    }
}



#endif

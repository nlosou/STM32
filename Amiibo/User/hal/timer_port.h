#ifndef TIMER_PORT_H
#define TIMER_PORT_H
#include <stddef.h>

typedef struct{
    void (*init)(void*ctx);
    void (*start_count)(void*ctx);
}Timer_ops_t;


typedef struct {
    void* ctx;
    const Timer_ops_t*ops;
}Timer_port_t;


static inline void Timer_init(Timer_port_t* port)
{
    if(port!=NULL && port->ops!=NULL && port->ctx!=NULL && port->ops->init!=NULL)
    {
        port->ops->init(port->ctx);
    }
}

static inline void Timer_start(Timer_port_t *port)
{
    if(port!=NULL && port->ops!=NULL && port->ctx!=NULL && port->ops->start_count!=NULL)
    {
        port->ops->start_count(port->ctx);
    }
}

#endif

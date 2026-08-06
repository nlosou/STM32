#ifndef EXTI_PORT_H_
#define EXTI_PORT_H_

#define NULL 0

typedef struct {
    void (*init)(void*ctx);
    void (*clear)(void*ctx);
}exti_ops_t;

typedef struct {
    const exti_ops_t* ops;
    void *ctx;
}exti_port_t;

static inline void  exti_init(exti_port_t *port)
{
    if(port!=NULL && port->ops->init!=NULL && port->ctx!=NULL)
    {
       port->ops->init(port->ctx);  
    }
}

static inline void  exti_clear(exti_port_t *port)
{
    if(port!=NULL && port->ops->clear!=NULL && port->ctx!=NULL)
    {
       port->ops->clear(port->ctx);  
    }
}



#endif

#ifndef NFC_HAL_H
#define NFC_HAL_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t* (*select_card)(void* ctx);
    uint8_t* (*card_transmit)(void *ctx,uint8_t* data,uint8_t datalength);
    uint8_t* (*card_cmd)(void *ctx,uint8_t* data,uint8_t datalength);
}nfc_ops_t;

typedef struct {
    void *ctx;
    const nfc_ops_t *ops;
}nfc_port_ctx_t;

inline static uint8_t* select_card(nfc_port_ctx_t* port)
{
   if(port!=NULL && port->ops!=NULL && port->ctx!=NULL && port->ops->select_card!=NULL) 
   {
        return port->ops->select_card(port->ctx);
   }
   return NULL;
}
inline static uint8_t* card_transmit(nfc_port_ctx_t* port,uint8_t* data,uint8_t datalength)
{
   if(port!=NULL && port->ops!=NULL && port->ctx!=NULL&&port->ops->card_transmit!=NULL) 
   {
        return port->ops->card_transmit(port->ctx,data,datalength);
   }
   return NULL;
}


inline static uint8_t* card_cmd(nfc_port_ctx_t* port,uint8_t* data,uint8_t datalength)
{
   if(port!=NULL && port->ops!=NULL && port->ctx!=NULL&&port->ops->card_cmd!=NULL) 
   {
        return port->ops->card_cmd(port->ctx,data,datalength);
   }
   return NULL;

}

#endif

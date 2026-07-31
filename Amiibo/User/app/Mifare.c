#include "Mifare.h"
#include <string.h>


uint8_t* Mifare_read(void *ctx)
{
   if(ctx == NULL) 
   {
       return NULL;
   }
    Mifare_ctx_t* mifare = (Mifare_ctx_t*)ctx;
    uint8_t* uid = select_card(mifare->nfc);

    uint8_t data[13] = {0x01,Auth,0x04,0xff,0xff,0xff,0xff,0xff,0xff};
    memcpy(data + 9,uid,4);
    card_transmit(mifare->nfc,data,13);
    uint8_t cmd[] = {0x01,Mifare_read_cmd,0x04};
    card_transmit(mifare->nfc,cmd,sizeof(cmd));
}

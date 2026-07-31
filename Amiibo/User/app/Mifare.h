#ifndef MIFARE_H_
#define MIFARE_H_

#include "nfc_hal.h"


#define Auth 0x60
#define Mifare_read_cmd 0x30

typedef struct {
    nfc_port_ctx_t* nfc;
}Mifare_ctx_t;
void Mifare_Authentication(void *ctx);
uint8_t* Mifare_read(void *ctx);

#endif

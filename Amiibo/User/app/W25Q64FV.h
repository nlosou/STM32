#ifndef W25Q64FV_H_
#define W25Q64FV_H_
#include "spi_port.h"


typedef struct {
    spi_port_t* port;
}W25Q64xx_ctx_t;

void W25Q64FV_init(W25Q64xx_ctx_t *ctx);

uint8_t* W25Q64FV_Read_ManuID_DeviceID(W25Q64xx_ctx_t *ctx);

#endif

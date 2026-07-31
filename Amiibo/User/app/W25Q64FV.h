#ifndef W25Q64FV_H_
#define W25Q64FV_H_
#include "spi_port.h"
#include "middleware/spi_select_opp.h"



typedef struct {
    spi_port_t* port;
    spi_select_port_t* select; 
    uint16_t CS;
    uint8_t bit_order;
}W25Q64xx_ctx_t;

void W25Q64FV_init(W25Q64xx_ctx_t *ctx);

uint8_t* W25Q64FV_Read_ManuID_DeviceID(W25Q64xx_ctx_t *ctx);
uint8_t* W25Q64FV_Read_JEDEC(W25Q64xx_ctx_t *ctx);
uint8_t* W25Q64FV_Read_Status_Reg1_and_Status_Reg2(W25Q64xx_ctx_t *ctx);
uint8_t* W25Q64FV_Read(W25Q64xx_ctx_t *ctx,uint32_t data_address,uint16_t length);
void W25Q64FV_Write(W25Q64xx_ctx_t *ctx,uint32_t data_address,const uint8_t data[],uint16_t length);


#endif

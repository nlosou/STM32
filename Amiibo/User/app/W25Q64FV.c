#include "W25Q64FV.h"




void W25Q64FV_init(W25Q64xx_ctx_t *ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    spi_init(ctx->port);
}


uint8_t* W25Q64FV_Read_ManuID_DeviceID(W25Q64xx_ctx_t *ctx)
{
    if(ctx == NULL) 
    {
        return 0;
    }
    uint8_t cmd[] = {0x90,0x00,0x00,0x00};
    static uint8_t getbuf[2] = {0};
    spi_msg_t  msg[] = {
         sizeof(cmd),  Read, sizeof(getbuf),cmd,getbuf
    };

    spi_transmit(ctx->port,msg,1);
    return getbuf;
}



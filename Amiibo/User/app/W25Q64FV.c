#include "W25Q64FV.h"
#include <string.h>

void W25Q64FV_init(W25Q64xx_ctx_t *ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    spi_init(ctx->port);
}


void W25Q64xx_transmit(W25Q64xx_ctx_t *ctx,spi_msg_t *msg,uint16_t num)
{
    for(uint16_t transmit_num = 0 ; transmit_num < num ; transmit_num++)
    {
        spi_select(ctx->select,ctx->CS,1);//片选
        spi_select(ctx->select,ctx->CS,0);
  
        spi_transmit(ctx->port,msg+transmit_num,2);
       
        spi_select(ctx->select,ctx->CS,1);//片选
    }
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
         sizeof(cmd),  Read, sizeof(getbuf),ctx->bit_order,cmd,getbuf
    };

    spi_transmit(ctx->port,msg,1);
    return getbuf;
}

uint8_t* W25Q64FV_Read_JEDEC(W25Q64xx_ctx_t *ctx)
{
    if(ctx == NULL) 
    {
        return 0;
    }
    uint8_t cmd[] = {0x9F};
    static uint8_t getbuf[3] = {0};
    spi_msg_t  msg[] = {
         sizeof(cmd),  Read, sizeof(getbuf),ctx->bit_order,cmd,getbuf
    };

    spi_transmit(ctx->port,msg,1);
    return getbuf;
}

uint8_t* W25Q64FV_Read_Status_Reg1_and_Status_Reg2(W25Q64xx_ctx_t *ctx)
{
    if(ctx == NULL) 
    {
        return 0;
    }
    uint8_t Read_reg1[] = {0x05};
    uint8_t Read_reg2[] = {0x35};
    static uint8_t getbuf[2] = {0};
    spi_msg_t  msg[2] = {
         sizeof(Read_reg1),  Read, 1,ctx->bit_order,Read_reg1,getbuf,

         sizeof(Read_reg2),  Read, 1,ctx->bit_order,Read_reg2,getbuf+1
    };
    W25Q64xx_transmit(ctx,msg,2);
    return getbuf;
}

uint8_t* W25Q64FV_Write(W25Q64xx_ctx_t *ctx,uint32_t data_address,uint8_t data[],uint8_t length)
{
    if(ctx == NULL) 
    {
        return 0;
    }
    uint8_t Write_enable[] = {0x06};
    uint8_t Sector_Erase[] = {0x20,(data_address>>16) & 0xFF,(data_address>>8) & 0xFF,data_address & 0xFF};
    uint8_t Page_Program[] = {0x02,(data_address>>16) & 0xFF,(data_address>>8) & 0xFF,data_address & 0xFF};
    memcpy(Page_Program + 4,data,length);
    static uint8_t getbuf[2] = {0};
        //擦除
    spi_msg_t  msg_Sector_Erase[2] = {
         sizeof(Write_enable),  Write, 0,MSB,Write_enable,getbuf,

         sizeof(Sector_Erase),  Write, 0,MSB,Sector_Erase,getbuf+1
    };

    //写入
    spi_msg_t  msg_Page_Program[2] = {
         sizeof(Write_enable),  Write, 0,ctx->bit_order,Write_enable,getbuf,

         sizeof(Page_Program) + length,  Write, 0,ctx->bit_order,Page_Program,getbuf+1
    };


    W25Q64xx_transmit(ctx,msg_Sector_Erase,2);
       
    while(W25Q64FV_Read_Status_Reg1_and_Status_Reg2(ctx)[0] & 0x01)
    {

    }
       
    W25Q64xx_transmit(ctx,msg_Page_Program,2);

    while(W25Q64FV_Read_Status_Reg1_and_Status_Reg2(ctx)[0] & 0x01)
    {

    }
    return getbuf;
}
uint8_t* W25Q64FV_Read(W25Q64xx_ctx_t *ctx,uint32_t data_address,uint8_t length)
{
    if(ctx == NULL) 
    {
        return 0;
    }
    //组装命令
    uint8_t Read_data[] = {0x03,(data_address>>16) & 0xFF,(data_address>>8) & 0xFF,data_address & 0xFF};
    static uint8_t getbuf[] = {0};
    //擦除
    spi_msg_t  msg_Read_data[1] = {
         sizeof(Read_data),  Read, length,ctx->bit_order,Read_data,getbuf,

    };
    W25Q64xx_transmit(ctx,msg_Read_data,1);
    return getbuf;
}

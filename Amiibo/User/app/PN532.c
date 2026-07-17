#include <PN532.h>
#include <string.h>
#include "osal/OSAL.h"

//=================frame=====================
#define PREAMBLE           0x00
#define POSTAMBLE          0x00
#define M_TO_S             0xD4
#define S_TO_M             0xD5
static uint8_t  START_CODE[] = {0x00,0xFF};

//=================command==================
#define GetFirmwareVersion 0x02
#define GetGeneralStatus   0x04


static uint8_t DW[20] = {0x01};
static uint8_t DR[] = {0x11};
static uint8_t SR[] = {0x10};



void PN532_transmit(PN532_ctx_t *ctx,spi_msg_t *msg,uint16_t num)
{
    for(uint16_t transmit_num = 0 ; transmit_num < num ; transmit_num++)
    {
        spi_select(ctx->select,ctx->CS,1);//片选
        spi_select(ctx->select,ctx->CS,0);
        osal_delay_ms(50);
  
        spi_transmit(ctx->port,msg+transmit_num,num);
       
        spi_select(ctx->select,ctx->CS,1);//片选
    }
}


static uint8_t PN532_read_status_reg(PN532_ctx_t* PN532)
{
    if(PN532 == NULL)    
    {
        return 0;
    }

    uint8_t getbuf[16]= {0};
    uint8_t command_frame[]={0x02};
    spi_msg_t msg[] = {
        1,1,1,LSB,command_frame,getbuf
    };
    PN532_transmit(PN532,msg,1);
    return getbuf[0] & 0x01 ;
}
static uint8_t Master_recieve_Ack_frame(PN532_ctx_t* PN532)
{
    if(PN532 == NULL)    
    {
        return 0;
    }

    uint8_t getbuf[6]= {0};
    uint8_t command_frame[]={0x03};
    spi_msg_t msg[] = {
        1,1,6,LSB,command_frame,getbuf
    };
    PN532_transmit(PN532,msg,1);
    return getbuf[5] & 0x01 ;
}
static uint8_t Master_recieve(PN532_ctx_t* PN532)
{
    if(PN532 == NULL)    
    {
        return 0;
    }

    uint8_t getbuf[16]= {0};
    uint8_t command_frame[]={0x03};
    spi_msg_t msg[] = {
        1,1,16,LSB,command_frame,getbuf
    };
    PN532_transmit(PN532,msg,1);
    return getbuf[5] & 0x01 ;
}


//轮询
uint8_t PN532_getgirmwareversion(PN532_ctx_t* PN532)
{
    if(PN532 == NULL) 
    {
        return 0;
    }
    uint8_t packet_data[]={GetFirmwareVersion};
    uint8_t command_frame[]={PREAMBLE,START_CODE[0],START_CODE[1],2,0xFE,M_TO_S,packet_data[0],0x2a,POSTAMBLE};
    uint8_t getbuf[] = {0};
    memcpy(DW+1,command_frame,sizeof(command_frame));
    spi_msg_t msg[] = {   
        1 + sizeof(command_frame),0,0,LSB,DW,getbuf
    };

    PN532_transmit(PN532,msg,1);
    while(!PN532_read_status_reg(PN532))
    {
        
    }
    Master_recieve_Ack_frame(PN532);
    while(!PN532_read_status_reg(PN532))
    {
        
    }
    Master_recieve(PN532);
    return 0;
}
//轮询
uint8_t PN532_GetGeneralStatus(PN532_ctx_t* PN532)
{
    if(PN532 == NULL) 
    {
        return 0;
    }
    uint8_t packet_data[]={GetGeneralStatus};
    uint8_t command_frame[]={PREAMBLE,START_CODE[0],START_CODE[1],2,0xFE,M_TO_S,packet_data[0],0x28,POSTAMBLE};
    uint8_t getbuf[] = {0};
    memcpy(DW+1,command_frame,sizeof(command_frame));
    spi_msg_t msg[] = {   
        1 + sizeof(command_frame),0,0,LSB,DW,getbuf
    };

    PN532_transmit(PN532,msg,1);
    while(!PN532_read_status_reg(PN532))
    {
        
    }
    Master_recieve_Ack_frame(PN532);
    while(!PN532_read_status_reg(PN532))
    {
        
    }
    Master_recieve(PN532);
    return 0;
}

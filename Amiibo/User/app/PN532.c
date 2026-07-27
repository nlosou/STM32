#include <PN532.h>
#include <string.h>
#include "osal/OSAL.h"
#include "oled.h"

//=================frame=====================
#define PREAMBLE           0x00
#define POSTAMBLE          0x00
#define M_TO_S             0xD4
#define S_TO_M             0xD5
static uint8_t  START_CODE[] = {0x00,0xFF};
static uint8_t  Frame_Header[] = {0x00,0x00,0xFF};
static uint8_t  Frame_End[] = {0x00};


static uint8_t DW[256] = {0x01};
static uint8_t DR[] = {0x11};
static uint8_t SR[] = {0x10};


uint8_t calculate_dcs(const uint8_t *buf, uint8_t len) {
    uint8_t sum = 0;
    
    for (uint8_t i = 0; i < len; i++) {
        sum += buf[i];
    }

    return (uint8_t)(-sum);
}

static void PN532_transmit(PN532_ctx_t *ctx,spi_msg_t *msg,uint16_t num)
{
    for(uint16_t transmit_num = 0 ; transmit_num < num ; transmit_num++)
    {
        spi_select(ctx->select,ctx->CS,1);//片选
        spi_select(ctx->select,ctx->CS,0);
        //osal_delay_ms(50);
  
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
static uint8_t Master_recieve(PN532_ctx_t* PN532,uint8_t *getbuf,uint32_t recieve_length)
{
    if(PN532 == NULL)    
    {
        return 0;
    }

    uint8_t command_frame[]={0x03};
    spi_msg_t msg[] = {
        1,1,recieve_length,LSB,command_frame,getbuf
    };
    PN532_transmit(PN532,msg,1);
    return getbuf[5] & 0x01 ;
}


//轮询
static uint8_t PN532_getgirmwareversion(PN532_ctx_t* PN532)
{
    if(PN532 == NULL) 
    {
        return 0;
    }
    uint8_t packet_data[]={GetFirmwareVersion};
    uint8_t command_frame[]={PREAMBLE,START_CODE[0],START_CODE[1],0x02,0xFE,M_TO_S,packet_data[0],0x2a,POSTAMBLE};
    uint8_t getbuf[16] = {0};
    memcpy(DW+1,command_frame,sizeof(command_frame));
    spi_msg_t msg[] = {   
        1 + sizeof(command_frame),0,1,LSB,DW,getbuf
    };

    PN532_transmit(PN532,msg,1);
    while(!PN532_read_status_reg(PN532))
    {
        
    }
    Master_recieve_Ack_frame(PN532);
    while(!PN532_read_status_reg(PN532))
    {
        
    }
    Master_recieve(PN532,getbuf,16);
    return 0;
}
//轮询
static uint8_t PN532_GetGeneralStatus(PN532_ctx_t* PN532)
{
    if(PN532 == NULL) 
    {
        return 0;
    }
    uint8_t packet_data[]={GetGeneralStatus};
    uint8_t command_frame[]={PREAMBLE,START_CODE[0],START_CODE[1],2,0xFE,M_TO_S,packet_data[0],0x28,POSTAMBLE};
    uint8_t getbuf[16] = {0};
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
    Master_recieve(PN532,getbuf,16);
    return 0;
}
uint8_t* PN532_InListPassiveTarget(PN532_ctx_t* PN532,uint8_t* card_id)
{
    if(PN532 == NULL) 
    {
        return 0;
    }
    uint8_t packet_data[]={InListPassiveTarget,0x01,0x00};
    uint8_t command_frame[]={PREAMBLE,START_CODE[0],START_CODE[1],04,0xFC,M_TO_S,packet_data[0],packet_data[1],packet_data[2],0xE1,POSTAMBLE};
    uint8_t getbuf[25] = {0};
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
    Master_recieve(PN532,getbuf,sizeof(getbuf));
    card_id[0] = getbuf[13];
    card_id[1] = getbuf[14];
    card_id[2] = getbuf[15];
    card_id[3] = getbuf[16];
    return card_id;
}
uint8_t PN532_SAMConfiguration(PN532_ctx_t* PN532)
{
    if(PN532 == NULL) 
    {
        return 0;
    }
    //设置为普通模式状态
    uint8_t packet_data[]={SAMConfiguration,0x01};
    uint8_t command_frame[]={PREAMBLE,START_CODE[0],START_CODE[1],03,0xFD,M_TO_S,packet_data[0],packet_data[1],0x17,POSTAMBLE};
    uint8_t getbuf[16] = {0};
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
    Master_recieve(PN532,getbuf,16);
    return 0;
}

static uint8_t PN532_TgGetTargetStatus(PN532_ctx_t* PN532)
{
    if(PN532 == NULL) 
    {
        return 0;
    }
    uint8_t packet_data[]={TgGetTargetStatus};
    uint8_t command_frame[]={PREAMBLE,START_CODE[0],START_CODE[1],02,0xFE,M_TO_S,packet_data[0],0xA2,POSTAMBLE};
    uint8_t getbuf[16] = {0};
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
    Master_recieve(PN532,getbuf,16);
    return 0;
}
static uint8_t PN532_RFConfiguration(PN532_ctx_t* PN532)
{
    if(PN532 == NULL) 
    {
        return 0;
    }
    uint8_t packet_data[]={RFConfiguration,0x01,0x03 ,0x01};
    uint8_t command_frame[]={PREAMBLE,START_CODE[0],START_CODE[1],0x05,0xFB,M_TO_S,packet_data[0],packet_data[1],packet_data[2],packet_data[3],0x22,POSTAMBLE};
    uint8_t getbuf[16] = {0};
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
    Master_recieve(PN532,getbuf,16);
    return 0;
}


uint8_t* PN532_InDataExchange(PN532_ctx_t* PN532,uint8_t* data,uint8_t datalength)
{
    if(PN532 == NULL) 
    {
        return 0;
    }
    //uint8_t packet_data[256]={InDataEXchange,0x01,0x60,0x03 ,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    uint8_t packet_data[256]={InDataEXchange};
    memcpy(packet_data+1,data,datalength);
    uint8_t command_frame[256];
    memcpy(command_frame,Frame_Header,3);
    uint8_t LEN = 2 + datalength;
    uint8_t LCS =~LEN + 1; 
    command_frame[3] = LEN;
    command_frame[4] = LCS;
    command_frame[5] = M_TO_S;
    memcpy(command_frame + 6,packet_data,1 + datalength);
    uint8_t DCS = calculate_dcs(command_frame + 5 ,2 + datalength);    
    command_frame[7 + datalength] = DCS;
    command_frame[8 + datalength] = Frame_End[0];

    static uint8_t getbuf[32] = {0};
    memcpy(DW+1,command_frame,8+datalength);
    spi_msg_t msg[] = {   
        10+datalength,0,0,LSB,DW,getbuf
    };
    PN532_transmit(PN532,msg,1);
    while(!PN532_read_status_reg(PN532))
    {
        
    }
    Master_recieve_Ack_frame(PN532);
    while(!PN532_read_status_reg(PN532))
    {
        
    }
    Master_recieve(PN532,getbuf,sizeof(getbuf));
    return getbuf;
}

uint8_t* PN532_InCommunicateThru(PN532_ctx_t* PN532,uint8_t* data,uint8_t datalength)
{
    if(PN532 == NULL) 
    {
        return 0;
    }
    //uint8_t packet_data[256]={InDataEXchange,0x01,0x60,0x03 ,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    uint8_t packet_data[256]={InCommunicateThru};
    memcpy(packet_data+1,data,datalength);
    uint8_t command_frame[256];
    memcpy(command_frame,Frame_Header,3);
    uint8_t LEN = 2 + datalength;
    uint8_t LCS =~LEN + 1; 
    command_frame[3] = LEN;
    command_frame[4] = LCS;
    command_frame[5] = M_TO_S;
    memcpy(command_frame + 6,packet_data,1 + datalength);
    uint8_t DCS = calculate_dcs(command_frame + 5 ,2 + datalength);    
    command_frame[7 + datalength] = DCS;
    command_frame[8 + datalength] = Frame_End[0];

    static uint8_t getbuf[32] = {0};
    memcpy(DW+1,command_frame,8+datalength);
    spi_msg_t msg[] = {   
        10+datalength,0,0,LSB,DW,getbuf
    };
    PN532_transmit(PN532,msg,1);
    while(!PN532_read_status_reg(PN532))
    {
        
    }
    Master_recieve_Ack_frame(PN532);
    while(!PN532_read_status_reg(PN532))
    {
        
    }
    Master_recieve(PN532,getbuf,sizeof(getbuf));
    return getbuf;
}








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

//=================command==================
#define GetFirmwareVersion 0x02
#define GetGeneralStatus   0x04
#define SAMConfiguration   0x14
#define TgGetTargetStatus  0x8A
#define InCommunicateThru  0x42


#define RFConfiguration     0x32
#define InListPassiveTarget 0x4A
#define InDataEXchange      0x40


static uint8_t DW[256] = {0x01};
static uint8_t DR[] = {0x11};
static uint8_t SR[] = {0x10};


static unsigned char final_test_bin[] = {
  0x04, 0xc1, 0x1a, 0x57, 0x65, 0x8e, 0x61, 0x81, 0x0b, 0x48, 0x00, 0x00,
  0xf1, 0x10, 0xff, 0xee, 0xa5, 0x00, 0x01, 0x00, 0x99, 0x7f, 0x4b, 0xd3,
  0x45, 0xc4, 0x71, 0x55, 0x92, 0xb6, 0xe0, 0x2f, 0x6e, 0xf9, 0xa0, 0x7b,
  0x59, 0xc7, 0x39, 0x91, 0x38, 0x46, 0x8e, 0xfa, 0x37, 0x95, 0xaa, 0xe4,
  0xb0, 0xbf, 0x37, 0x48, 0x0b, 0x92, 0x37, 0xe9, 0x53, 0xe6, 0xe6, 0x4e,
  0xb1, 0x0e, 0x1a, 0x2b, 0xea, 0x1f, 0xfb, 0x37, 0x7b, 0x66, 0x1f, 0x55,
  0x6b, 0x40, 0x8b, 0x6e, 0xa9, 0xb6, 0x6d, 0xf4, 0xb6, 0x18, 0x88, 0x61,
  0x01, 0x00, 0x00, 0x00, 0x03, 0x53, 0x09, 0x02, 0x0d, 0x12, 0xc6, 0x0f,
  0x27, 0x75, 0xf8, 0xb7, 0xe8, 0x60, 0xfa, 0xa2, 0xa6, 0x40, 0xe5, 0x1a,
  0x4d, 0xe9, 0xf5, 0x3d, 0xa1, 0xbd, 0x46, 0x53, 0x71, 0x98, 0x86, 0x3c,
  0x5f, 0x8d, 0x14, 0xb9, 0xb9, 0x21, 0x21, 0x69, 0x10, 0x3c, 0x45, 0xae,
  0x9f, 0x69, 0x01, 0xbf, 0x5b, 0x8d, 0x04, 0x6f, 0x1c, 0x26, 0xb3, 0x6c,
  0xcd, 0xad, 0x8a, 0x72, 0x9f, 0x1a, 0x12, 0xea, 0xa6, 0xf5, 0x7b, 0x60,
  0xce, 0x2c, 0xf2, 0xb4, 0x47, 0x97, 0xe8, 0x79, 0x60, 0xbb, 0xca, 0x39,
  0x12, 0x88, 0x4b, 0x38, 0xa5, 0x42, 0x46, 0xfe, 0x36, 0x44, 0x89, 0xc9,
  0x05, 0x89, 0xaf, 0x36, 0xac, 0x1f, 0x6c, 0x10, 0x85, 0xfe, 0xc1, 0x01,
  0x40, 0xb0, 0x7b, 0x73, 0x1a, 0x34, 0x5f, 0xf1, 0x72, 0x58, 0x67, 0xcf,
  0x01, 0xb1, 0x6d, 0xb7, 0xfc, 0x0f, 0xa8, 0x49, 0x8a, 0xa3, 0x2e, 0xdd,
  0x56, 0xb0, 0x6f, 0x2c, 0x6c, 0xe1, 0x6d, 0xd3, 0x8e, 0x26, 0xbb, 0xec,
  0xb9, 0x94, 0xa6, 0x8a, 0x29, 0xe0, 0x47, 0x2e, 0x6b, 0x46, 0x08, 0xb5,
  0x5a, 0xa8, 0xe3, 0x15, 0xd4, 0x7d, 0xa7, 0x21, 0xdf, 0x39, 0x4f, 0xe2,
  0xbf, 0x0c, 0x69, 0xa3, 0x91, 0xfb, 0x7e, 0xc6, 0x1b, 0xb3, 0x3d, 0x9c,
  0x47, 0xc4, 0xf4, 0x43, 0x57, 0x92, 0xe8, 0x9e, 0xc4, 0xe3, 0x88, 0x69,
  0x23, 0x37, 0xf8, 0x29, 0x72, 0xd9, 0xb2, 0xf8, 0xee, 0xa9, 0x08, 0x1c,
  0x5b, 0x58, 0xb4, 0xcc, 0xf7, 0xe6, 0xe0, 0x01, 0xf1, 0x03, 0x94, 0xfa,
  0x58, 0x3e, 0x1c, 0x2c, 0xf6, 0x89, 0xfe, 0xb3, 0xfe, 0xaf, 0xe9, 0x62,
  0xe3, 0xeb, 0x8d, 0xd5, 0x15, 0xf7, 0x2a, 0x20, 0x53, 0xa0, 0x29, 0xb0,
  0x66, 0x77, 0x56, 0x1b, 0x2d, 0x28, 0x86, 0x9c, 0xe4, 0x91, 0xa8, 0x43,
  0xa9, 0x5d, 0x80, 0x6d, 0x10, 0x49, 0xdb, 0x87, 0xb3, 0x7b, 0xfd, 0xf5,
  0x39, 0xc8, 0xa1, 0x4e, 0xf8, 0x68, 0x1f, 0xb4, 0x59, 0x32, 0xff, 0x14,
  0x69, 0xb9, 0x19, 0x40, 0x95, 0x64, 0xe0, 0xa5, 0x61, 0x1a, 0x0f, 0x09,
  0x06, 0x96, 0x0b, 0x68, 0xe3, 0x76, 0x3d, 0x62, 0xf3, 0x02, 0x73, 0x61,
  0x06, 0x0c, 0x90, 0xd2, 0xd2, 0x1c, 0x93, 0x09, 0xea, 0xae, 0xd7, 0x7b,
  0x55, 0x71, 0x9b, 0x14, 0x68, 0x40, 0x20, 0x85, 0x63, 0xe5, 0x0b, 0x08,
  0xff, 0x2a, 0xa8, 0x23, 0x48, 0xf1, 0x2a, 0x60, 0xa4, 0xcc, 0xb7, 0x93,
  0x91, 0x42, 0x61, 0x19, 0x6d, 0x5d, 0x9e, 0x8b, 0xb9, 0xe9, 0x34, 0xfb,
  0x85, 0x46, 0x41, 0x35, 0x6c, 0xd9, 0x4b, 0x33, 0x61, 0x06, 0x48, 0x75,
  0xb7, 0x89, 0xdd, 0x22, 0x30, 0x09, 0x36, 0x3c, 0x88, 0x05, 0x8d, 0xed,
  0x79, 0xe6, 0xf1, 0xfa, 0x68, 0xbe, 0xb1, 0x33, 0x7e, 0x1b, 0x99, 0xdd,
  0x74, 0x05, 0xbe, 0xf7, 0x84, 0x65, 0x78, 0xb2, 0x12, 0xfd, 0x24, 0xb3,
  0x61, 0x8d, 0x07, 0x9e, 0xfa, 0x92, 0xa2, 0xa2, 0x11, 0x18, 0x18, 0xa5,
  0x8a, 0x16, 0x6a, 0xea, 0xc1, 0x1c, 0x9a, 0xbd, 0xc7, 0x1a, 0x92, 0x1f,
  0xef, 0xdd, 0xfd, 0x2f, 0x05, 0x20, 0x67, 0x46, 0xf4, 0x6a, 0x26, 0x7b,
  0xe0, 0x3f, 0x00, 0xf7, 0x00, 0x00, 0x00, 0xbd, 0x00, 0x00, 0x00, 0x04,
  0x5f, 0x00, 0x00, 0x00, 0x0e, 0xc1, 0xae, 0x5a, 0x80, 0x80, 0x00, 0x00
};

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
static uint8_t* PN532_InListPassiveTarget(PN532_ctx_t* PN532,uint8_t* card_id)
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
static uint8_t PN532_SAMConfiguration(PN532_ctx_t* PN532)
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


static uint8_t* PN532_InDataExchange(PN532_ctx_t* PN532,uint8_t* data,uint8_t datalength)
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

static uint8_t* PN532_InCommunicateThru(PN532_ctx_t* PN532,uint8_t* data,uint8_t datalength)
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


uint8_t PN532_write_card(PN532_ctx_t* PN532,uint8_t* need_write_data)
{
    uint8_t card_id[4];
    PN532_SAMConfiguration(PN532);
    PN532_InListPassiveTarget(PN532,card_id);
    uint8_t card_cmd[7]={0x01,0xA2};
    uint16_t page_head;
    for(uint8_t page_idx = 3 ; page_idx <=129 ; page_idx ++ )
    {
        page_head = page_idx *4;
        card_cmd[2] = page_idx;
        card_cmd[3] = final_test_bin[page_head + 0];
        card_cmd[4] = final_test_bin[page_head + 1];
        card_cmd[5] = final_test_bin[page_head + 2];
        card_cmd[6] = final_test_bin[page_head + 3];
        PN532_InDataExchange(PN532,card_cmd,7);
    }
    for(uint8_t idx = 131 ; idx <=134 ; idx ++ )
    {
        page_head = idx *4;
        card_cmd[2] = idx;
        card_cmd[3] = final_test_bin[page_head + 0];
        card_cmd[4] = final_test_bin[page_head + 1];
        card_cmd[5] = final_test_bin[page_head + 2];
        card_cmd[6] = final_test_bin[page_head + 3];
        PN532_InDataExchange(PN532,card_cmd,7);
    }

    return 0;
}
uint8_t PN532_write_card_test(PN532_ctx_t* PN532,uint8_t* need_write_data)
{
    uint8_t card_cmd[7]={0x01,0xA2,0x86,0x80,0x80,00,00};
    PN532_InDataExchange(PN532,card_cmd,7);

    return 0;
}

uint8_t PN532_read_card(PN532_ctx_t* PN532,uint8_t page_address)
{
    uint8_t card_id[4];
    PN532_SAMConfiguration(PN532);
    PN532_InListPassiveTarget(PN532,card_id);

    uint8_t card_cmd[]={0x01,0x30,page_address};
    //读取
    if(PN532_InDataExchange(PN532,card_cmd,3)[7] == 0x00)
    {
        OLED_ShowString(0,0,"Card OK!");
    }
    return 0;
}
uint8_t PN532_PWD_AUTH(PN532_ctx_t* PN532)
{
    uint8_t card_id[4];
    PN532_SAMConfiguration(PN532);
    PN532_InListPassiveTarget(PN532,card_id);

    uint8_t card_cmd[]={0x1B,0x0e,0xc1,0xae,0x5a};
    PN532_InCommunicateThru(PN532,card_cmd,sizeof(card_cmd));
    return 0;
}

uint8_t PN532_write_lock(PN532_ctx_t* PN532,uint8_t* need_write_data)
{
    uint8_t card_id[4];
    /*
    PN532_SAMConfiguration(PN532);
    PN532_InListPassiveTarget(PN532,card_id);
    */
    uint8_t card_cmd[7]={0x01,0xA2,0x82,0x01,0x00,0x0F,0xBD};
    uint8_t card_cmd2[7]={0x01,0xA2,0x02,0x00,0x00,0x0F,0xE0};

    PN532_InDataExchange(PN532,card_cmd,7);
    //PN532_InDataExchange(PN532,card_cmd2,7);
    return 0;
}

/*
uint8_t PN532_write_card(PN532_ctx_t* PN532,uint8_t* need_write_data)
{
    uint8_t card_id[4];
    PN532_SAMConfiguration(PN532);
    PN532_InListPassiveTarget(PN532,card_id);
    uint8_t packet_data[256]={0x01,0x60,0x04,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

    uint8_t write_packet_data[256] = {0x01,0xA0,0x04}; 
    memcpy(packet_data + 9,card_id,4);
    memcpy(write_packet_data + 3,need_write_data,16);
    //认证
    if(PN532_InDataExchange(PN532,packet_data,13)[7] == 0x00)
    {
        OLED_ShowString(0,0,"Card OK!");
    }
    //写入
    if(PN532_InDataExchange(PN532,write_packet_data,19)[7] == 0x00)
    {
        OLED_ShowString(0,0,"Card Write OK!");
    }
    return 0;
}
uint8_t PN532_read_card(PN532_ctx_t* PN532)
{
    uint8_t card_id[4];
    PN532_SAMConfiguration(PN532);
    PN532_InListPassiveTarget(PN532,card_id);
    uint8_t packet_data[256]={0x01,0x60,0x04,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

    uint8_t card_cmd[]={0x01,0x30,0x04};
    memcpy(packet_data + 9,card_id,4);
    //认证
    if(PN532_InDataExchange(PN532,packet_data,13)[7] == 0x00)
    {
        OLED_ShowString(0,0,"Card OK!");
    }
    //读取
    if(PN532_InDataExchange(PN532,card_cmd,3)[7] == 0x00)
    {
        OLED_ShowString(0,0,"Card OK!");
    }
    return 0;
}
*/

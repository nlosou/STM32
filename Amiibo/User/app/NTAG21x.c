#include "NTAG21x.h"


uint8_t NTAG21x_write_data(void *ctx,uint8_t start_addr,uint8_t end_addr,uint8_t need_write_data[])
{
    if(ctx == NULL)
    {
        return 0;
    }
    uint8_t card_id[4];
    uint8_t card_cmd[7]={0x01,NTAG_WRITE};
    uint16_t page_head;
    NTAG21x_t *NTAG21x = (NTAG21x_t*)ctx;
    uint8_t  Page_per_bytes_cnt =NTAG21x->Page_per_bytes;
    for(uint8_t page_idx =start_addr ; page_idx <=end_addr ; page_idx ++ )
    {
        page_head = page_idx * Page_per_bytes_cnt;
        card_cmd[2] = page_idx;
        card_cmd[3] =need_write_data[page_head + 0];
        card_cmd[4] =need_write_data[page_head + 1];
        card_cmd[5] =need_write_data[page_head + 2];
        card_cmd[6] =need_write_data[page_head + 3];
        card_transmit(NTAG21x->ctx,card_cmd,7);
    }
    return 0;
}
uint8_t* NTAG21x_Read(void *ctx,uint8_t page_address)
{   
    if(ctx == NULL)
    {
        return 0;
    }

    uint8_t card_id[4];
    uint8_t* getbuf = NULL;
    
    NTAG21x_t *NTAG21x = (NTAG21x_t*)ctx;
    uint8_t card_cmd[]={0x01,NTAG_READ,page_address};
    //读取
    getbuf = card_transmit(NTAG21x->ctx,card_cmd,sizeof(card_cmd));
    if(getbuf == NULL)
    {
        return NULL;
    }
    if(getbuf[7] == 0x00)
    {
       return getbuf + 8;
    }
    else
    {
        return NULL;
    }
}

uint8_t* NTAG21x_CaculatePwd(void *ctx)
{
    if(ctx == NULL)
    {
        return 0;
    }

    static  uint8_t pwd[4] = {0};
    NTAG21x_t *NTAG21x = (NTAG21x_t*)ctx;
    uint8_t* UID = NTAG21x_Read(ctx,0x00);    
    pwd[0] = 0xAA ^ UID[1] ^ UID[3];
    pwd[1] = 0x55 ^ UID[2] ^ UID[4];
    pwd[2] = 0xAA ^ UID[3] ^ UID[5];
    pwd[3] = 0x55 ^ UID[4] ^ UID[6];
    return pwd;
}

uint8_t NTAG21x_Pwd_Auth(void* ctx)
{
    if(ctx == NULL)
    {
        return 0;
    }

    NTAG21x_t *NTAG21x = (NTAG21x_t*)ctx;
    uint8_t *pwd = NTAG21x_CaculatePwd(NTAG21x);
    
    uint8_t cmd[]={NTAG_PWD_AUTH,pwd[0],pwd[1],pwd[2],pwd[3]};
    card_cmd(NTAG21x->ctx,cmd,sizeof(card_cmd));
    return 0;

}

uint8_t* NTAG21x_Select_Card(void*ctx)
{
    if(ctx == NULL)
    {
        return 0;
    }

    NTAG21x_t *NTAG21x = (NTAG21x_t*)ctx;
    return select_card(NTAG21x->ctx);
}

uint8_t NTAG21x_Write_lock(void *ctx)
{
    if(ctx == NULL)
    {
        return 0;
    }

    NTAG21x_t *NTAG21x = (NTAG21x_t*)ctx;
    uint8_t card_id[4];
    uint8_t card_cmd[7]={0x01,NTAG_WRITE,NTAG21x->Dynamic_lock_bytes_Address,0x01,0x00,0x0F,0xBD};
    uint8_t card_cmd2[7]={0x01,NTAG_WRITE,0x02,0x00,0x00,0x0F,0xE0};
    card_transmit(NTAG21x->ctx,card_cmd,7);
    card_transmit(NTAG21x->ctx,card_cmd2,7);
    return 0;
}

uint8_t NTAG21x_Read_Back_Comparison(void*ctx,uint8_t* need_compariosn_data)
{
    if(ctx == NULL)
    {
        return 1;
    }
    return 0;
}


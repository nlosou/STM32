#include "amiibo.h"


uint8_t* Amiibo_gen_data(Amiibo_ctx_t *Amiibo)
{
   static uint8_t* amiibo_data;
   return amiibo_data;
}


uint8_t Amiibo_write(Amiibo_ctx_t* amiibo)
{
    uint8_t *amiibo_data = Amiibo_gen_data(amiibo);

    //选择卡片
    NTAG21x_Select_Card(amiibo->card_info);

    NTAG21x_write_data(amiibo->card_info,amiibo->card_info->CC_Address,amiibo->card_info->User_memory_Address_End,amiibo_data);
    NTAG21x_write_data(amiibo->card_info,amiibo->card_info->Configuration_pages_Start,amiibo->card_info->Configuration_pages_End,amiibo_data);
    
    NTAG21x_Read_Back_Comparison(amiibo->card_info,amiibo_data);

    NTAG21x_Pwd_Auth(amiibo->card_info);
    //写锁
    NTAG21x_Write_lock(amiibo->card_info); 

    return 0;
}

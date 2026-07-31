#include "bsp_devices.h"
#include "test_data.h"
#include <stdint.h>

int main(void)
{   
    uint8_t data[] = {0x23,0xa0,3,4,5,6,7,77};
    oled_t *oled = bsp_get_oled();
    W25Q64xx_ctx_t *W25Q64xx = bsp_get_w25Q64();
    PN532_ctx_t* PN532 = bsp_get_pn532();
    Amiibo_ctx_t* Amiibo = bsp_get_amiibo();
    Mifare_ctx_t* Mifare = bsp_get_mifare();
    W25Q64FV_init(W25Q64xx);
    oled_init_hal(oled);
    oled_init(oled);
    //W25Q64FV_Write(W25Q64xx,0x00,Link_Rider_final_bin,540);
    //W25Q64FV_Write(W25Q64xx,0x00,data,sizeof(data));
    //W25Q64FV_Read_Status_Reg1_and_Status_Reg2(W25Q64xx);
    uint8_t *getbuf = W25Q64FV_Read(W25Q64xx,0x200,256);
    //uint8_t *getbuf = W25Q64FV_Read_ManuID_DeviceID(W25Q64xx);
    OLED_ShowHex(0,0,getbuf[25]);
    //OLED_ShowString(0,0,"Hello Noser");
    //OLED_ShowString(0,0,"1");
    //PN532_write_card(PN532,Link_Rider_final_bin,Link_Rider_final_bin_len); 
    //PN532_PWD_AUTH(PN532);
    //PN532_write_card_test(PN532,data);
    //PN532_read_card(PN532,0x02);
    //PN532_read_card(PN532,0x82);
    //PN532_write_lock(PN532,data);
    //Amiibo_read(Amiibo);
    //Mifare_read(Mifare);
    oled_point(oled);
    while (1)
    {
        
    }
    return 0;
}

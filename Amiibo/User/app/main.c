#include "bsp_devices.h"
#include <stdint.h>


int main(void)
{   
    uint8_t data[16] = {0x23,0xa0,3,4,5,6,7,77};
    oled_t *oled = bsp_get_oled();
    W25Q64xx_ctx_t *W25Q64xx = bsp_get_w25Q64();
    PN532_ctx_t* PN532 = bsp_get_pn532();
    W25Q64FV_init(W25Q64xx);
    oled_init_hal(oled);
    oled_init(oled);
    //W25Q64FV_Write(W25Q64xx,0x123,data,sizeof(data));
    //W25Q64FV_Read_Status_Reg1_and_Status_Reg2(W25Q64xx);
    //uint8_t *getbuf = W25Q64FV_Read(W25Q64xx,0x123,sizeof(data));
    //uint8_t *getbuf = W25Q64FV_Read_ManuID_DeviceID(W25Q64xx);
    //OLED_ShowHex(0,0,getbuf[0]);
    //OLED_ShowString(0,0,"Hello Noser");
    //OLED_ShowString(0,0,"1");
    //PN532_write_card(PN532,data); 
    PN532_read_card(PN532);
    oled_point(oled);
    while (1)
    {
        
    }
    return 0;
}

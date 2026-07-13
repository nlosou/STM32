#include "bsp_devices.h"
#include <stdint.h>


int main(void)
{   
    oled_t *oled = bsp_get_oled();
    uint8_t data[] = {0x23,66,3,4,5,6,7,77};
    W25Q64xx_ctx_t *W25Q64xx = bsp_get_w25Q64();
    W25Q64FV_init(W25Q64xx);
    oled_init_hal(oled);
    oled_init(oled);
    //W25Q64FV_Write(W25Q64xx,0x123,data,sizeof(data));
     uint8_t *getbuf = W25Q64FV_Read(W25Q64xx,0x123,sizeof(data));
    OLED_ShowHex(0,0,getbuf[1]);
    oled_point(oled);

    while (1)
    {
        
    }
    return 0;
}

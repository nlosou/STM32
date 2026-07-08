#include "bsp_devices.h"
#include <stdint.h>



int main(void)
{   

    
    oled_t *oled = bsp_get_oled();
    W25Q64xx_ctx_t *W25Q64xx = bsp_get_w25Q64();
    
    W25Q64FV_init(W25Q64xx);

    oled_init_hal(oled);
    oled_init(oled);
    W25Q64FV_Read_ManuID_DeviceID(W25Q64xx);
    OLED_ShowString(1,1,"OK");
    oled_point(oled);
    while (1)
    {
           
    }
    return 0;
}

#include "bsp_devices.h"

int main(void)
{   
    oled_t *oled = bsp_get_oled();
    oled_init_hal(oled);
    oled_init(oled);
    //OLED_ShowString(0,0,"Hello world!");
    //OLED_ShowString(5,1,"#$%#");
    //OLED_ShowString(0,3,"0123456789");
    OLED_ShowHex(0,0  ,0x13);
   // OLED_DrawPoint(0,0,1);
    ///OLED_DrawPoint(0,1,1);
    oled_point(oled);
    //uint8_t data[2] = { 0x40,0xFF};
    while (1)
    {
        
    }
    return 0;
}

#include "bsp_devices.h"
#include "board_config.h"
#include <stdint.h>







int main(void)
{   
    
    uint8_t cmd[4] = {0x90,0x00,0x00,0x00};
    spi_msg_t msg[1] = {
        4,cmd
    };
    oled_t *oled = bsp_get_oled();
    spi_port_t *spi = bsp_get_spi();
    spi->ops->init(spi->ctx);
    oled_init_hal(oled);
    oled_init(oled);
    spi->ops->transmit(spi->ctx,msg,1);
    OLED_ShowString(1,1,"OK");
    oled_point(oled);
    while (1)
    {


           
    }
    return 0;
}

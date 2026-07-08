#ifndef BSP_DEVICES_H 
#define BSP_DEVICES_H
#include "at24c02.h"
#include "oled.h"
#include "gpio_port.h"
#include "W25Q64FV.h"


at24c02_t* bsp_get_eeprom1(void);
oled_t* bsp_get_oled(void);
gpio_port_t* bsp_get_spi_out(void);
W25Q64xx_ctx_t* bsp_get_w25Q64(void);




#endif



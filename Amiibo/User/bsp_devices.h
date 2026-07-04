#ifndef BSP_DEVICES_H 
#define BSP_DEVICES_H
#include "at24c02.h"
#include "oled.h"

at24c02_t* bsp_get_eeprom1(void);
oled_t* bsp_get_oled(void);


#endif



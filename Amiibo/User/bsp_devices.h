#ifndef BSP_DEVICES_H 
#define BSP_DEVICES_H
#include "at24c02.h"
#include "oled.h"
#include "gpio_port.h"
#include "W25Q64FV.h"
#include "middleware/spi_select_opp.h"
#include "PN532.h"
#include "amiibo.h"
#include "Mifare.h"
#include "uart_port.h"


at24c02_t* bsp_get_eeprom1(void);
oled_t* bsp_get_oled(void);
gpio_port_t* bsp_get_spi_out(void);
W25Q64xx_ctx_t* bsp_get_w25Q64(void);
spi_select_port_t* bsp_get_select_spi(void);
PN532_ctx_t* bsp_get_pn532(void);
Amiibo_ctx_t* bsp_get_amiibo(void);
Mifare_ctx_t* bsp_get_mifare(void);
uart_port_t* bsg_get_uart_test(void);

#endif



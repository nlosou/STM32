// board_config.h
#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "stm32f10x_sfr.h"

// ================= EEPROM 1 (AT24C02) 硬件配置 =================
#define EEPROM1_GPIO_PORT           GPIOB
#define EEPROM1_RCC_BIT             RCC_APB2ENR_IOPBEN
#define EEPROM1_GPIO_MODE           OUTPUT_MODE_10MHZ_General_open_drain
#define EEPROM1_SCL_PIN             GPIOx_PIN_5
#define EEPROM1_SDA_PIN             GPIOx_PIN_6

#define EEPROM1_DEV_ADDR_READ       0xA0
#define EEPROM1_DEV_ADDR_WRITE      0xA0




// ================= OLED (ssd1306) 硬件配置 =================
#define OLED_GPIO_PORT           GPIOB
#define OLED_BIT                 RCC_APB2ENR_IOPBEN
#define OLED_GPIO_MODE           OUTPUT_MODE_10MHZ_General_open_drain
#define OLED_SCL_PIN             GPIOx_PIN_5
#define OLED_SDA_PIN             GPIOx_PIN_6

#define OLED_DEV_ADDRESSS        0x78




// ================= W25QXX (软件SPI) 硬件配置 =================
#define W25QXX_GPIO_PORT            GPIOA
#define W25QXX__BIT                 RCC_APB2ENR_IOPAEN
#define W25QXX__GPIO_MODE           OUTPUT_MODE_10MHZ_General_push_pull 
#define W25QXX__GPIO_MODE1          INPUT_WITH_PULLUP_PULLDOWN
#define W25QXX_DI_PIN               GPIOx_PIN_8
#define W25QXX_CLK_PIN              GPIOx_PIN_9
#define W25QXX_DO_PIN               GPIOx_PIN_10
#define W25QXX_CS_PIN               GPIOx_PIN_11




#endif

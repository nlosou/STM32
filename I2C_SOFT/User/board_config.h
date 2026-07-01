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

#endif

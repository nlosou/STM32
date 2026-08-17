#ifndef STM32_GPIO_PORT_H
#define STM32_GPIO_PORT_H

#include <stdint.h>
#include "gpio_port.h"
#include "stm32f10x_sfr.h"

#define STM32_FAST_GET_GPIOA_PIN_LEVEL(PIN) (*((volatile uint32_t*)(GPIOA_BASE + 0x08))&(PIN) ? 1:0)
#define STM32_FAST_SET_GPIOA_PIN_HIGH(PIN) (*((volatile uint32_t*)(GPIOA_BASE + 16)) = PIN)
#define STM32_FAST_SET_GPIOA_PIN_LOW(PIN) (*((volatile uint32_t*)(GPIOA_BASE + 20)) = PIN)


typedef struct{
    GPIOx_TypeDef *gpio;
    uint32_t rcc_enable_bit;
    uint16_t use_pins; //可以选择0到15
    uint8_t mode_select;
}stm32_gpio_ctx_t;

extern const gpio_ops_t stm32_gpio_ops;

#endif

#include <stdint.h>
#include "led.h"
#include "key.h"
#include "./osal/OSAL.h"
#include "stm32_gpio_port.h"
#define KEY_USE_PINS  8


//选择要使用的GPIOx，使能外设时钟，设置使用的引脚，选择输入或输出模式
static stm32_gpio_ctx_t gpioa_ctx = {
    .gpio = GPIOA,
    .rcc_enable_bit = RCC_APB2ENR_IOPAEN,
    .mode_select = OUTPUT_MODE_50MHZ_General_push_pull,
};
static stm32_gpio_ctx_t gpioa_ctx_key = {
    .gpio = GPIOA,
    .rcc_enable_bit = RCC_APB2ENR_IOPAEN,
    .use_pins = KEY_USE_PINS,
    .mode_select = INPUT_WITH_PULLUP_PULLDOWN,
};
static gpio_port_t gpioa_port = {
    .ops = &stm32_gpio_ops,
    .ctx = &gpioa_ctx
};
static gpio_port_t gpioa_port_key = {
    .ops = &stm32_gpio_ops,
    .ctx = &gpioa_ctx_key
};
static led_t leds = {
    .gpio = &gpioa_port,
};

uint32_t  LED_USE_PINS = GPIOA_PIN_7 | GPIOA_PIN_2;

//配置按键使用的引脚，按键的初始状态，按键代表的系统状态
static key_t keys = {
    .gpio = &gpioa_port_key,
    .pins =KEY_USE_PINS,
    .key_state = IDLE,
    .key_represent = Blink_led,
};

Sys_state sys_state = default_;

int main(void)
{   

    gpioa_ctx.use_pins = LED_USE_PINS;
    leds.pins = LED_USE_PINS;

    //Systate state = default_;
    led_init(&leds);
    key_init(&keys);
    while (1)
    {
        /*
        key_machine(&keys,&sys_state);
        switch(sys_state)
        {
            case default_:
                break;
            case Blink_led:
                led_on(&leds);
                //led_off(&leds);
                //sys_state = default_;
                break;
            default:
                break;
        }
        */
        led_on(&leds);
        osal_delay_ms(500);
        led_off(&leds);
    }

    return 0;
}

#include "stm32_gpio_port.h"
#include "stm32f10x_sfr.h"

#define BASE_MASK (0x0F)
#define BASE_ONE (0x01)

static void stm32_gpioa__init(void *ctx)
{
    stm32_gpio_ctx_t *gpio_ctx = (stm32_gpio_ctx_t*)ctx;
        
    //特定port的遮罩 

    if(gpio_ctx == NULL)
    {
        return;
    }

    RCC->APB2ENR|= gpio_ctx->rcc_enable_bit;
    for(uint8_t idx = 0 ; idx < 16 ; idx++)
    {
        if((gpio_ctx->use_pins >> idx) & 0x01)
        {
            if(idx <=7)
            {
                uint32_t mask = BASE_MASK << (idx*4);
                gpio_ctx->gpio->CRL&=~mask;
                gpio_ctx->gpio->CRL|= gpio_ctx->mode_select << (idx*4);

                if(gpio_ctx->mode_select == INPUT_WITH_PULLUP_PULLDOWN)
                {
                    gpio_ctx->gpio->ODR |=(BASE_ONE << idx);
                }
            }
            if(idx>=8 && idx<=15)
            {
                uint32_t mask = BASE_MASK << ((idx - 8))*4;
                gpio_ctx->gpio->CRH&=~mask;
                gpio_ctx->gpio->CRH|= gpio_ctx->mode_select << (idx - 8)*4;
                if(gpio_ctx->mode_select == INPUT_WITH_PULLUP_PULLDOWN)
                {
                    gpio_ctx->gpio->ODR |=(BASE_ONE << idx);
                }
            }
        }
    }
}

//output_mode
static void stm32_gpioa_write(void *ctx,uint16_t use_pins,gpio_level_t level)
{
    stm32_gpio_ctx_t *gpio_ctx = (stm32_gpio_ctx_t*)ctx;

    if(gpio_ctx == NULL)
    {
        return;
    }
    for(uint8_t idx = 0 ; idx < 16 ; idx++)
    {
        if((use_pins >> idx) & 0x01)
        {
            if(level == GPIO_LEVEL_HIGH)
            {
                gpio_ctx->gpio->BSRR = BASE_ONE <<idx;
            }
            else
            {
                gpio_ctx->gpio->BRR = BASE_ONE <<idx;
            }    
        }
    }
}
//input
static uint32_t stm32_gpioa_read(void *ctx,uint16_t use_pins)
{
    stm32_gpio_ctx_t *gpio_ctx = (stm32_gpio_ctx_t*)ctx;
    if(gpio_ctx == NULL)
    {
        return 0;
    }
    return (gpio_ctx->gpio->IDR >> use_pins) & 0x01;
}
static void stm32_gpio_toggle(void *ctx, uint16_t pins)
{
    stm32_gpio_ctx_t *gpio_ctx = (stm32_gpio_ctx_t *)ctx;
    uint32_t odr;

    if (gpio_ctx == NULL) {
        return;
    }

    odr = gpio_ctx->gpio->ODR;

    gpio_ctx->gpio->BSRR = ((odr & pins) << 16) | (~odr & pins);
}

//stm32平台专属的函数表
const gpio_ops_t stm32_gpio_ops = {
    .init = stm32_gpioa__init,
   .write = stm32_gpioa_write,
    .toggle = stm32_gpio_toggle,
    .read = stm32_gpioa_read
};

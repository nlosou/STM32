#include "stm32_timer_port.h"
#include "oled.h"


void stm32_timer_init(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    
    stm32_timer_ctx_t* tim1 = (stm32_timer_ctx_t*)ctx;
    RCC->APB2ENR|= tim1->rcc_enable_bit;
    tim1->tim->TIMx_ARR =tim1->Timx_arr;
    tim1->tim->TIMx_DIER|=tim1->Timx_dier;
    OLED_ShowHex(0,1,tim1->tim->TIMx_ARR);
}

void stm32_timer_start(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    stm32_timer_ctx_t* tim1 = (stm32_timer_ctx_t*)ctx;
    tim1->tim->TIMx_CR1|=0x01;

}


const Timer_ops_t stm32_timer_ops = {
    .init = stm32_timer_init,
    .start_count = stm32_timer_start
};

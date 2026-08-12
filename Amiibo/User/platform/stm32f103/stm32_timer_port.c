#include "stm32_timer_port.h"


void stm32_timer_init(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    
    stm32_timer_ctx_t* tim1 = (stm32_timer_ctx_t*)ctx;
    RCC->APB2ENR|= tim1->rcc_enable_bit;
    //现在将APB2的时钟频率除以16,最终ck_psc会获得9Mhz
    //TODO APB2 分频属于系统时钟树配置，后续移到 RCC/Clock 初始化模块，Timer 驱动只负责读取并使用已经确定的 TIMx 时钟。
    //RCC->CFGR&= ~(0x07 << 11) ;
    //RCC->CFGR|= (0x07 << 11) ;
    tim1->tim->TIMx_ARR =tim1->Timx_arr - 1;
    tim1->tim->TIMx_DIER|=tim1->Timx_dier;
    tim1->tim->TIMx_PSC = tim1->Timx_psc;
}

void stm32_timer_start(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    stm32_timer_ctx_t* tim1 = (stm32_timer_ctx_t*)ctx;
    //TODO 后续 把0x01整理成宏
    tim1->tim->TIMx_CR1|=0x01;

}

void stm32_timer_close(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    stm32_timer_ctx_t* tim1 = (stm32_timer_ctx_t*)ctx;
    //TODO 后续 把0x01整理成宏
    tim1->tim->TIMx_CR1&=~0x01;

}

void stm32_timer_ug(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    stm32_timer_ctx_t* tim1 = (stm32_timer_ctx_t*)ctx;
    //TODO 后续 把0x01整理成宏
    tim1->tim->TIMx_EGR|=0x01;
    CLEAR_UIF();
}


const Timer_ops_t stm32_timer_ops = {
    .init = stm32_timer_init,
    .start_count = stm32_timer_start,
    .close_count = stm32_timer_close,
    .update_ck_cnt = stm32_timer_ug
};

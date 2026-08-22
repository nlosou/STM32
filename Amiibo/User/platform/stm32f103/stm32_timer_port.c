#include "stm32_timer_port.h"


static void stm32_timer_init(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    
    stm32_timer_ctx_t* tim1 = (stm32_timer_ctx_t*)ctx;
    RCC->APB1ENR|= tim1->rcc_enable_bit;
    //现在将APB2的时钟频率除以16,最终ck_psc会获得9Mhz
    //TODO APB2 分频属于系统时钟树配置，后续移到 RCC/Clock 初始化模块，Timer 驱动只负责读取并使用已经确定的 TIMx 时钟。
    //RCC->CFGR&= ~(0x07 << 11) ;
    //RCC->CFGR|= (0x07 << 11) ;
    tim1->tim->TIMx_ARR =tim1->Timx_arr - 1;
    tim1->tim->TIMx_DIER|=tim1->Timx_dier;
    tim1->tim->TIMx_PSC = tim1->Timx_psc;

}

static void stm32_timer_clear_uif(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    stm32_timer_ctx_t* tim1 = (stm32_timer_ctx_t*)ctx;
    tim1->tim->TIMx_SR = 0x00;
}
static void stm32_timer_start(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    stm32_timer_clear_uif(ctx);
    stm32_timer_ctx_t* tim1 = (stm32_timer_ctx_t*)ctx;
    //TODO 后续 把0x01整理成宏
    tim1->tim->TIMx_CR1|=0x01;

}

static void stm32_timer_close(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    stm32_timer_ctx_t* tim1 = (stm32_timer_ctx_t*)ctx;
    //TODO 后续 把0x01整理成宏
    tim1->tim->TIMx_CR1&=~0x01;
    stm32_timer_clear_uif(ctx);
}

static void stm32_timer_ug(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    stm32_timer_ctx_t* tim1 = (stm32_timer_ctx_t*)ctx;
    //TODO 后续 把0x01整理成宏
    tim1->tim->TIMx_EGR|=0x01;
    stm32_timer_clear_uif(ctx);
}

static void stm32_timer_count_clear(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    stm32_timer_ctx_t* tim1 = (stm32_timer_ctx_t*)ctx;
    tim1->tim->TIMx_CNT = 0x00;
}

static void stm32_timer_set_arr(void*ctx,uint32_t arr)
{
    if(ctx == NULL)
    {
        return;
    }
    stm32_timer_ctx_t* tim1 = (stm32_timer_ctx_t*)ctx;
    tim1->tim->TIMx_ARR = arr-1;
}

const Timer_ops_t stm32_timer_ops = {
    .init = stm32_timer_init,
    .start_count = stm32_timer_start,
    .close_count = stm32_timer_close,
    .clear_count = stm32_timer_count_clear,
    .update_ck_cnt = stm32_timer_ug,
    .set_arrtime = stm32_timer_set_arr,
    .clear_uif = stm32_timer_clear_uif

};

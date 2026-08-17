#include "stm32_exti_port.h"



void stm32_exti_init(void*ctx)
{
    if(ctx ==NULL)
    {
        return;
    }
    stm32_exti_ctx_t* exti_ctx = (stm32_exti_ctx_t*)ctx;

    
    //TODO:暂时在这里配置AFIO的始终
   RCC->APB2ENR|=0x01;
   exti_ctx->exti->EXTI_FTSR |=exti_ctx->exti_ftsr_trx; 
   exti_ctx->exti->EXTI_PR = exti_ctx->exti_pr_prx; 
   exti_ctx->exti->EXTI_IMR |=exti_ctx->exti_imr_mrx; 
   //exti_ctx->exti->EXTI_EMR |=exti_ctx->exti_emr_mrx; 
   //exti_ctx->exti->EXTI_RTSR |=exti_ctx->exti_rtsr_trx; 
   //exti_ctx->exti->EXTI_SWIER |=exti_ctx->exti_swier_swierx; 
   exti_ctx->afio->AFIO_EXTICR1 |= exti_ctx->select_interrupt_source;
}
void stm32_exti_clear(void*ctx)
{
    if(ctx ==NULL)
    {
        return;
    }
    stm32_exti_ctx_t* exti_ctx = (stm32_exti_ctx_t*)ctx;
    exti_ctx->exti->EXTI_PR = exti_ctx->exti_pr_prx; 
}

void stm32_exti_close(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    stm32_exti_ctx_t* exti_ctx = (stm32_exti_ctx_t*)ctx;
    exti_ctx->exti->EXTI_IMR &=~(exti_ctx->exti_imr_mrx);
}

void stm32_exti_start(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    stm32_exti_ctx_t* exti_ctx = (stm32_exti_ctx_t*)ctx;
    exti_ctx->exti->EXTI_IMR |=(exti_ctx->exti_imr_mrx);
}

const exti_ops_t stm32_exti_ops = {
    .init = stm32_exti_init,
    .clear = stm32_exti_clear,
    .close = stm32_exti_close,
    .start = stm32_exti_start
};

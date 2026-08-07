#include "stm32_exti_port.h"



void stm32_exti_init(void*ctx)
{
    if(ctx ==NULL)
    {
        return;
    }
    stm32_exti_ctx_t* exti_ctx = (stm32_exti_ctx_t*)ctx;

   exti_ctx->exti->EXTI_IMR |=exti_ctx->exti_imr_mrx; 
   //exti_ctx->exti->EXTI_EMR |=exti_ctx->exti_emr_mrx; 
   //exti_ctx->exti->EXTI_RTSR |=exti_ctx->exti_rtsr_trx; 
   exti_ctx->exti->EXTI_FTSR |=exti_ctx->exti_ftsr_trx; 
   //exti_ctx->exti->EXTI_SWIER |=exti_ctx->exti_swier_swierx; 
   exti_ctx->exti->EXTI_PR |=exti_ctx->exti_pr_prx; 
   //exti_ctx->afio->AFIO_EXTICR1 |= exti_ctx->select_interrupt_source;
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


const exti_ops_t stm32_exti_ops = {
    .init = stm32_exti_init,
    .clear = stm32_exti_clear
};

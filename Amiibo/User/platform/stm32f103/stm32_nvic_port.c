#include "stm32_nvic_port.h"



void stm32_nvic_iser(void* ctx)
{
    if(ctx == NULL)  
    {
        return;
    }
    stm32_nvic_ctx_t* nvic_ctx = (stm32_nvic_ctx_t*)ctx;
    if(nvic_ctx->Interrupt_position <=31)
    {
        nvic_ctx->nvic_iser->NVIC_ISER0 = 1 << nvic_ctx->Interrupt_position;
    }
    else if (nvic_ctx->Interrupt_position >=32 && nvic_ctx->Interrupt_position <= 63)
    {

        nvic_ctx->nvic_iser->NVIC_ISER1 = 1 << (nvic_ctx->Interrupt_position % 32);
    }
    else
    {
        nvic_ctx->nvic_iser->NVIC_ISER2 = 1 << (nvic_ctx->Interrupt_position % 64);
    }
}


void stm32_nvic_icer(void*ctx)
{
    if(ctx == NULL)  
    {
        return;
    }
    stm32_nvic_ctx_t* nvic_ctx = (stm32_nvic_ctx_t*)ctx;
    if(nvic_ctx->Interrupt_position <=31)
    {
        nvic_ctx->nvic_icer->NVIC_ICER0 = 1 << nvic_ctx->Interrupt_position;
    }
    else if (nvic_ctx->Interrupt_position >=32 && nvic_ctx->Interrupt_position <= 63)
    {

        nvic_ctx->nvic_icer->NVIC_ICER1 = 1 << (nvic_ctx->Interrupt_position % 32);
    }
    else
    {
        nvic_ctx->nvic_icer->NVIC_ICER2 = 1 << (nvic_ctx->Interrupt_position % 64);
    }

}
void stm32_nvic_ispr(void*ctx)
{

}
void stm32_nvic_icpr(void*ctx)
{

}
void stm32_nvic_iabr(void*ctx)
{

}
void stm32_nvic_ipr(void*ctx)
{

}


const nvic_ops_t stm32_nvic_ops = {
    .init = stm32_nvic_iser,
};

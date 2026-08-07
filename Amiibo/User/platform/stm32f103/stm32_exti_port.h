#ifndef STM32_EXTI_PORT_H_
#define STM32_EXTI_PORT_H_
#include "stm32f10x_sfr.h"
#include "exti_port.h"


typedef struct {
    EXTI_TypeDef *exti;
    AFIO_TypeDef *afio;
    uint32_t exti_imr_mrx;
    uint32_t exti_emr_mrx;
    uint32_t exti_rtsr_trx;
    uint32_t exti_ftsr_trx;
    uint32_t exti_swier_swierx;
    uint32_t exti_pr_prx;
    uint32_t select_interrupt_source;
}stm32_exti_ctx_t;

extern const exti_ops_t stm32_exti_ops;

#endif



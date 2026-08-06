#ifndef STM32_NVIC_PORT_H
#define STM32_NVIC_PORT_H


#include "stm32f10x_sfr.h"
#include "nvic_port.h"




typedef struct {
    NVIC_ISER_TypeDef* nvic_iser;
    NVIC_ICER_TypeDef* nvic_icer;     
    NVIC_ISPR_TypeDef* nvic_ispr;     
    NVIC_ICPR_TypeDef* nvic_icpr;     
    NVIC_IABR_TypeDef* nvic_iabr;
    NVIC_IPR_TypeDef*  nvic_ipr;
    uint8_t Interrupt_position;
}stm32_nvic_ctx_t;


extern const nvic_ops_t stm32_nvic_ops;

#endif

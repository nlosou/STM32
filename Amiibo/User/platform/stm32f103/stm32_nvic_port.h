#ifndef STM32_NVIC_PORT_H
#define STM32_NVIC_PORT_H


#include "stm32f10x_sfr.h"
#include "nvic_port.h"




typedef struct {
    NVIC_ISER_TypeDef* nvic_iser;
    
}stm32_nvic_ctx_t;






#endif

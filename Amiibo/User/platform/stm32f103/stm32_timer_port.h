#ifndef STM32_TIMER_PORT_H
#define STM32_TIMER_PORT_H
#include "stm32f10x_sfr.h"
#include "timer_port.h"


#define CLEAR_UIF() (*(volatile uint32_t*)(TIM1_TIMER_BASE + 0x10) = 0x00)
#define CLOSE_TIM() (*(volatile uint32_t*)(TIM1_TIMER_BASE) &= ~0x01)
#define OPEN_TIM1() (*(volatile uint32_t*)(TIM1_TIMER_BASE + 0x00)|=0x01)
#define CLOSE_TIM1() (*(volatile uint32_t*)(TIM1_TIMER_BASE + 0x00)&=~0x01)
#define CLEAR_CNT()  (*(volatile uint32_t*)(TIM1_TIMER_BASE + 36) = 0x00)
#define TIMER_SET_ARR(x)   (*(volatile uint32_t*)(TIM1_TIMER_BASE + 44) = x - 1)
#define CLEAR_TIM8_UIF() (*(volatile uint32_t*)(TIM8_TIMER_BASE + 0x10) = 0x00)
#define CLEAR_TIM2_UIF() (*(volatile uint32_t*)(TIM2_TIMER_BASE + 0x10) = 0x00)
#define CLEAR_TIM3_UIF() (*(volatile uint32_t*)(TIM3_TIMER_BASE + 0x10) = 0x00)


typedef struct {
   TIM_TypeDef* tim;     

   uint32_t rcc_enable_bit;
   uint32_t Timx_cnt;
   uint32_t Timx_psc;
   uint32_t Timx_arr;
   uint32_t Timx_rcr;
   uint32_t Timx_cr1;
   uint32_t Timx_dier;
}stm32_timer_ctx_t;


extern const Timer_ops_t stm32_timer_ops;

#endif

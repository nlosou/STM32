#ifndef __SFR_H_
#define __SFR_H_

#include <stdint.h>

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t AHBSTR;
    volatile uint32_t CFGR2;
}RCC_TypeDef;

typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
}GPIOx_TypeDef;

typedef struct {
    volatile uint32_t EXTI_IMR;
    volatile uint32_t EXTI_EMR;
    volatile uint32_t EXTI_RTSR;
    volatile uint32_t EXTI_FTSR;
    volatile uint32_t EXTI_SWIER;
    volatile uint32_t EXTI_PR;
}EXTI_TypeDef;


typedef struct {
    volatile uint32_t NVIC_ISER0;
    volatile uint32_t NVIC_ISER1;
    volatile uint32_t NVIC_ISER2;
}NVIC_ISER_TypeDef;

typedef struct {
    volatile uint32_t NVIC_ICER0;
    volatile uint32_t NVIC_ICER1;
    volatile uint32_t NVIC_ICER2;
}NVIC_ICER_TypeDef;

typedef struct {
    volatile uint32_t NVIC_ISPR0;
    volatile uint32_t NVIC_ISPR1;
    volatile uint32_t NVIC_ISPR2;
}NVIC_ISPR_TypeDef;

typedef struct {
    volatile uint32_t NVIC_ICPR0;
    volatile uint32_t NVIC_ICPR1;
    volatile uint32_t NVIC_ICPR2;
}NVIC_ICPR_TypeDef;

typedef struct {
    volatile uint32_t NVIC_IABR0;
    volatile uint32_t NVIC_IABR1;
    volatile uint32_t NVIC_IABR2;
}NVIC_IABR_TypeDef;

typedef struct {
    volatile uint32_t NVIC_IPR0;
    volatile uint32_t NVIC_IPR1;
    volatile uint32_t NVIC_IPR2;
    volatile uint32_t NVIC_IPR3;
    volatile uint32_t NVIC_IPR4;
    volatile uint32_t NVIC_IPR5;
    volatile uint32_t NVIC_IPR6;
    volatile uint32_t NVIC_IPR7;
    volatile uint32_t NVIC_IPR8;
    volatile uint32_t NVIC_IPR9;
    volatile uint32_t NVIC_IPR10;
    volatile uint32_t NVIC_IPR11;
    volatile uint32_t NVIC_IPR12;
    volatile uint32_t NVIC_IPR13;
    volatile uint32_t NVIC_IPR14;
    volatile uint32_t NVIC_IPR15;
    volatile uint32_t NVIC_IPR16;
    volatile uint32_t NVIC_IPR17;
    volatile uint32_t NVIC_IPR18;
    volatile uint32_t NVIC_IPR19;
    volatile uint32_t NVIC_IPR20;
}NVIC_IPR_TypeDef;


#define RCC_BASE   (0x40021000UL)
#define GPIOA_BASE (0x40010800UL)
#define GPIOB_BASE (0x40010C00UL)
#define GPIOC_BASE (0x40011000UL)
#define EXTI_BASE  (0x40010400UL)
#define NVIC_ISER_BASE    (0xE000E100)
#define NVIC_ICER_BASE    (0xE000E100 | 0x080)
#define NVIC_ISPR_BASE    (0xE000E100 | 0x100)
#define NVIC_ICPR_BASE    (0xE000E100 | 0x180)
#define NVIC_IABR_BASE    (0xE000E100 | 0x200)
#define NVIC_IPR_BASE     (0xE000E100 | 0x300)
#define NVIC_STIR_BASE     (0xE000E100 | 0x300)


#define RCC ((RCC_TypeDef*)RCC_BASE)
#define GPIOA ((GPIOx_TypeDef*)GPIOA_BASE)
#define GPIOB ((GPIOx_TypeDef*)GPIOB_BASE)
#define GPIOC ((GPIOx_TypeDef*)GPIOC_BASE)
#define EXTI  ((EXTI_TypeDef*)EXTI_BASE)
#define NVIC_ISER ((NVIC_ISER_TypeDef*)NVIC_ISER_BASE)
#define NVIC_ICER ((NVIC_ICER_TypeDef*)NVIC_ICER_BASE)
#define NVIC_ISPR ((NVIC_ISPR_TypeDef*)NVIC_ISPR_BASE)
#define NVIC_ICPR ((NVIC_ICPR_TypeDef*)NVIC_ICPR_BASE)
#define NVIC_IABR ((NVIC_IABR_TypeDef*)NVIC_IABR_BASE)
#define NVIC_IPR ((NVIC_IPR_TypeDef*)NVIC_IPR_BASE)
#define NVIC_STIR ((NVIC_STIR_TypeDef*)NVIC_STIR_BASE)



#define RCC_APB2ENR_IOPAEN (1UL << 2)
#define RCC_APB2ENR_IOPBEN (1UL << 3)
#define RCC_APB2ENR_IOPCEN (1UL << 4)


//select mode
#define ANALOG_MODE                (0x00)
#define FLOATING_INPUT             (0x04)
#define INPUT_WITH_PULLUP_PULLDOWN (0x08)


#define OUTPUT_MODE_10MHZ_General_push_pull     (0x01)
#define OUTPUT_MODE_10MHZ_General_open_drain    (0x05)

#define OUTPUT_MODE_2MHZ_General_push_pull     (0x02)
#define OUTPUT_MODE_2MHZ_General_open_drain    (0x06)

#define OUTPUT_MODE_50MHZ_General_push_pull     (0x03)
#define OUTPUT_MODE_50MHZ_General_open_drain    (0x07)


//gpio_pin
#define GPIOx_PIN_0   (1<<0)
#define GPIOx_PIN_1   (1<<1)
#define GPIOx_PIN_2   (1<<2)
#define GPIOx_PIN_3   (1<<3)
#define GPIOx_PIN_4   (1<<4)
#define GPIOx_PIN_5   (1<<5)
#define GPIOx_PIN_6   (1<<6)
#define GPIOx_PIN_7   (1<<7)
#define GPIOx_PIN_8   (1<<8)
#define GPIOx_PIN_9   (1<<9)
#define GPIOx_PIN_10  (1<<10)
#define GPIOx_PIN_11  (1<<11)
#define GPIOx_PIN_12  (1<<12)
#define GPIOx_PIN_13  (1<<13)
#define GPIOx_PIN_14  (1<<14)
#define GPIOx_PIN_15  (1<<15)

//EXTI_IMR
#define EXTI_IMR_MR0   (1<<0)
#define EXTI_IMR_MR1   (1<<1)
#define EXTI_IMR_MR2   (1<<2)
#define EXTI_IMR_MR3   (1<<3)
#define EXTI_IMR_MR4   (1<<4)
#define EXTI_IMR_MR5   (1<<5)
#define EXTI_IMR_MR6   (1<<6)
#define EXTI_IMR_MR7   (1<<7)
#define EXTI_IMR_MR8   (1<<8)
#define EXTI_IMR_MR9   (1<<9)
#define EXTI_IMR_MR10  (1<<10)
#define EXTI_IMR_MR11  (1<<11)
#define EXTI_IMR_MR12  (1<<12)
#define EXTI_IMR_MR13  (1<<13)
#define EXTI_IMR_MR14  (1<<14)
#define EXTI_IMR_MR15  (1<<15)
#define EXTI_IMR_MR16  (1<<16)
#define EXTI_IMR_MR17  (1<<17)
#define EXTI_IMR_MR18  (1<<18)
#define EXTI_IMR_MR19  (1<<19)

//EXTI_EMR
#define EXTI_EMR_MR0    (1<<0)
#define EXTI_EMR_MR1    (1<<1)
#define EXTI_EMR_MR2    (1<<2)
#define EXTI_EMR_MR3    (1<<3)
#define EXTI_EMR_MR4    (1<<4)
#define EXTI_EMR_MR5    (1<<5)
#define EXTI_EMR_MR6    (1<<6)
#define EXTI_EMR_MR7    (1<<7)
#define EXTI_EMR_MR8    (1<<8)
#define EXTI_EMR_MR9    (1<<9)
#define EXTI_EMR_MR10   (1<<10)
#define EXTI_EMR_MR11   (1<<11)
#define EXTI_EMR_MR12   (1<<12)
#define EXTI_EMR_MR13   (1<<13)
#define EXTI_EMR_MR14   (1<<14)
#define EXTI_EMR_MR15   (1<<15)
#define EXTI_EMR_MR16   (1<<16)
#define EXTI_EMR_MR17   (1<<17)
#define EXTI_EMR_MR18   (1<<18)
#define EXTI_EMR_MR19   (1<<19)

//EXTI_RTSR
#define EXTI_RTSR_TR0    (1<<0)
#define EXTI_RTSR_TR1    (1<<1)
#define EXTI_RTSR_TR2    (1<<2)
#define EXTI_RTSR_TR3    (1<<3)
#define EXTI_RTSR_TR4    (1<<4)
#define EXTI_RTSR_TR5    (1<<5)
#define EXTI_RTSR_TR6    (1<<6)
#define EXTI_RTSR_TR7    (1<<7)
#define EXTI_RTSR_TR8    (1<<8)
#define EXTI_RTSR_TR9    (1<<9)
#define EXTI_RTSR_TR10    (1<<10)
#define EXTI_RTSR_TR11    (1<<11)
#define EXTI_RTSR_TR12    (1<<12)
#define EXTI_RTSR_TR13    (1<<13)
#define EXTI_RTSR_TR14    (1<<14)
#define EXTI_RTSR_TR15    (1<<15)
#define EXTI_RTSR_TR16    (1<<16)
#define EXTI_RTSR_TR17    (1<<17)
#define EXTI_RTSR_TR18    (1<<18)
#define EXTI_RTSR_TR19    (1<<19)

//EXTI_FTSR
#define EXTI_FTSR_TR0    (1<<0)
#define EXTI_FTSR_TR1    (1<<1)
#define EXTI_FTSR_TR2    (1<<2)
#define EXTI_FTSR_TR3    (1<<3)
#define EXTI_FTSR_TR4    (1<<4)
#define EXTI_FTSR_TR5    (1<<5)
#define EXTI_FTSR_TR6    (1<<6)
#define EXTI_FTSR_TR7    (1<<7)
#define EXTI_FTSR_TR8    (1<<8)
#define EXTI_FTSR_TR9    (1<<9)
#define EXTI_FTSR_TR10    (1<<10)
#define EXTI_FTSR_TR11    (1<<11)
#define EXTI_FTSR_TR12    (1<<12)
#define EXTI_FTSR_TR13    (1<<13)
#define EXTI_FTSR_TR14    (1<<14)
#define EXTI_FTSR_TR15    (1<<15)
#define EXTI_FTSR_TR16    (1<<16)
#define EXTI_FTSR_TR17    (1<<17)
#define EXTI_FTSR_TR18    (1<<18)
#define EXTI_FTSR_TR19    (1<<19)
//EXTI_SWIER
#define EXTI_SWIER_SWIER0    (1<<0)
#define EXTI_SWIER_SWIER1    (1<<1)
#define EXTI_SWIER_SWIER2    (1<<2)
#define EXTI_SWIER_SWIER3    (1<<3)
#define EXTI_SWIER_SWIER4    (1<<4)
#define EXTI_SWIER_SWIER5    (1<<5)
#define EXTI_SWIER_SWIER6    (1<<6)
#define EXTI_SWIER_SWIER7    (1<<7)
#define EXTI_SWIER_SWIER8    (1<<8)
#define EXTI_SWIER_SWIER9    (1<<9)
#define EXTI_SWIER_SWIER10    (1<<10)
#define EXTI_SWIER_SWIER11    (1<<11)
#define EXTI_SWIER_SWIER12    (1<<12)
#define EXTI_SWIER_SWIER13    (1<<13)
#define EXTI_SWIER_SWIER14    (1<<14)
#define EXTI_SWIER_SWIER15    (1<<15)
#define EXTI_SWIER_SWIER16    (1<<16)
#define EXTI_SWIER_SWIER17    (1<<17)
#define EXTI_SWIER_SWIER18    (1<<18)
#define EXTI_SWIER_SWIER19    (1<<19)
//EXTI_PR
#define EXTI_PR_PR0    (1<<0)
#define EXTI_PR_PR1    (1<<1)
#define EXTI_PR_PR2    (1<<2)
#define EXTI_PR_PR3    (1<<3)
#define EXTI_PR_PR4    (1<<4)
#define EXTI_PR_PR5    (1<<5)
#define EXTI_PR_PR6    (1<<6)
#define EXTI_PR_PR7    (1<<7)
#define EXTI_PR_PR8    (1<<8)
#define EXTI_PR_PR9    (1<<9)
#define EXTI_PR_PR10    (1<<10)
#define EXTI_PR_PR11    (1<<11)
#define EXTI_PR_PR12    (1<<12)
#define EXTI_PR_PR13    (1<<13)
#define EXTI_PR_PR14    (1<<14)
#define EXTI_PR_PR15    (1<<15)
#define EXTI_PR_PR16    (1<<16)
#define EXTI_PR_PR17    (1<<17)
#define EXTI_PR_PR18    (1<<18)
#define EXTI_PR_PR19    (1<<19)

#endif 

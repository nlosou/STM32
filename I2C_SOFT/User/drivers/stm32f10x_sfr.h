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



#define RCC_BASE   (0x40021000UL)
#define GPIOA_BASE (0x40010800UL)
#define GPIOB_BASE (0x40010C00UL)
#define GPIOC_BASE (0x40011000UL)

#define RCC ((RCC_TypeDef*)RCC_BASE)
#define GPIOA ((GPIOx_TypeDef*)GPIOA_BASE)
#define GPIOB ((GPIOx_TypeDef*)GPIOB_BASE)
#define GPIOC ((GPIOx_TypeDef*)GPIOC_BASE)

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

#endif 

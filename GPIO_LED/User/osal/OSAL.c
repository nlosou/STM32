// osal_baremetal.c
#include "OSAL.h"

void osal_delay_ms(uint32_t ms)
{
    volatile uint32_t i;
    volatile uint32_t j;

    for (i = 0; i < ms; i++) {
        for (j = 0; j < 8000; j++) {
            __asm volatile ("nop");
        }
    }
}

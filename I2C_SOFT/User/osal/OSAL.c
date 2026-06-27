// osal_baremetal.c
#include "OSAL.h"

void osal_delay_ms(uint32_t ms)
{
    while(ms--);
}

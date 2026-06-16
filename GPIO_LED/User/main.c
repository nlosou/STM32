#include "sfr.h"
#include <stdint.h>

int main(void)
{
    //使能
    RCC_APB2ENR|=0x01 << 2;
    RCC_APB2ENR|=0x04 << 3;

    return 0;
}

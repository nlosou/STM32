#include <stdint.h>
#include "OLED.h"
#define KEY_USE_PINS  8

int main(void)
{   

    OLED_Init();
    OLED_ShowString(1,1,"Hello world");
    while (1)
    {
        
    }

    return 0;
}

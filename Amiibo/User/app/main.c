#include "bsp_devices.h"
#include "test_data.h"
#include <stdint.h>
#include "stm32f10x_it.h"




int main(void)
{   
    oled_t* oled = bsp_get_oled();
    oled_init_hal(oled);
    oled_init(oled);
    exti_port_t *exti = bsp_get_exti();
    nvic_port_t *nvic = bsp_get_nvic();
    gpio_port_t *gpio = bsp_get_gpio();
    Timer_port_t *timer1 = bsp_get_tim();

    gpio_port_init(gpio);
    //exti_init(exti);
    Timer_init(timer1);
    nvic_init(nvic);
    Timer_start(timer1);

    while(1)
    {
        OLED_ShowHex(0,0,flag);
        oled_point(oled);
    }
    return 0;
}


#include "bsp_devices.h"
#include "test_data.h"
#include <stdint.h>
#include "stm32f10x_it.h"

int main(void)
{   
    
    uint16_t data = 0xAF;
    uart_msg_t msg = {
        .mode = Half_duplex,
        .parity_bits = parity_bits_off,
        .tranfer_buf =&data,
    };
    oled_t* oled = bsp_get_oled();
    oled_init_hal(oled);
    oled_init(oled);
    exti_port_t *exti = bsp_get_exti();
    nvic_port_t *nvic = bsp_get_nvic();
    gpio_port_t *gpio = bsp_get_gpio();
    uart_port_t *uart = bsp_get_uart_test();
    Timer_port_t *timer1 = bsp_get_tim();

   // uart_init(uart);
    gpio_port_init(gpio);
   //exti_init(exti);
    Timer_init(timer1);
    nvic_init(nvic);
    Timer_update_ck_cnt(timer1);
    Timer_start(timer1);
    //uart_transmit(uart,&msg,1);
    //Timer_close(timer1);
    while(1)
    {
        //Timer_start(timer1);
        if(flag)
        {
            gpio_port_write(gpio,1,GPIO_LEVEL_HIGH);
         // flag = 0;
        }
        else
        {
            gpio_port_write(gpio,1,GPIO_LEVEL_LOW);
        }
        //OLED_ShowHex(0,0,flag);
        //oled_point(oled);
    }
    return 0;
}


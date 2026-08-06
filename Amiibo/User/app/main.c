#include "bsp_devices.h"
#include "test_data.h"
#include <stdint.h>




int main(void)
{   
    /*
    uart_port_t *uart = bsg_get_uart_test();
    uart_init(uart);    
    uint16_t data = 0xAA;
    uart_msg_t msg[] = {
        &data,
    };
    uart_transmit(uart,msg,1);
    */
    oled_t* oled = bsp_get_oled();
    oled_init_hal(oled);
    oled_init(oled);
    exti_port_t *exti = bsp_get_exti();
    nvic_port_t *nvic = bsp_get_nvic();
    gpio_port_t *gpio = bsp_get_gpio();
    exti_init(exti);
    nvic_init(nvic);
    gpio_port_init(gpio);

   //gpio_port_write(gpio,1,GPIO_LEVEL_HIGH);
    /*
    gpio_port_read(gpio,0);
    if(gpio_port_read(gpio,0))
    {
    }
    */
    while(1)
    {
         gpio_port_read(gpio,1);
         oled_point(oled);
    }
    return 0;
}


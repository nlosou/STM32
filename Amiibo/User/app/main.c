#include "bsp_devices.h"
#include "test_data.h"
#include <stdint.h>
#include "stm32f10x_it.h"

int main(void)
{   
    
    uint16_t data = 0x41;
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

    uart_init(uart);
    //exti_init(exti);
    nvic_init(nvic);
    //oled_point(oled);
    while(1)
    {
        uart_transmit(uart,&msg,1);
    }
    return 0;
}


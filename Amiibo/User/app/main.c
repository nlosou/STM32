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
    exti_port_t *exti = bsp_get_exti();
    exti_init(exti);
    while(1)
    {
        
    }
    return 0;
}

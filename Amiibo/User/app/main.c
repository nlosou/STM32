#include "bsp_devices.h"
#include "test_data.h"
#include <stdint.h>
#include "stm32f10x_it.h"

int main(void)
{   
    uint16_t buf[1] ={0x00};
    oled_t* oled = bsp_get_oled();
    oled_init_hal(oled);
    oled_init(oled);
    uart_port_t *uart = bsp_get_uart_test();

    uart_init(uart);
    uint16_t tmep = 0x00;
    uart_msg_t msg = {
        .mode = Half_duplex,
        .parity_bits = parity_bits_off,
        .tranfer_buf = tmep,
        .recieve_buf = buf,
        .tranfer_buf_len = 0 ,
    };

    //CLOSE_EXTIx(1<<2);
    //CLEAR_EXTI_PR(0x01 << 2);   

    while(1)
    {
        
        uart_transmit(uart,&msg,1);
        tmep = msg.recieve_buf[0];

        OLED_ShowHex(0,0,tmep);
        tmep = 0xFF;
        OLED_ShowString(0,1,"uart_data_come");
        OLED_ShowHex(6,0,uart_transfer_idx);

        /*
        if(uart_come)
        {
            OLED_ShowString(0,0,"uart_data_come");
            uart_come = 0;
        }
        else
        {
            OLED_ShowString(0,0,"              ");
        }
        */
        oled_point(oled);
    }
    return 0;
}


#include <stdint.h>
#include "stm32_gpio_port.h"
#include "./osal/OSAL.h"

stm32_gpio_ctx_t sw_i2c_gpio_ctx = {
    .gpio = GPIOB,
    .rcc_enable_bit = RCC_APB2ENR_IOPBEN,
    .mode_select =OUTPUT_MODE_2MHZ_General_open_drain,
    .use_pins = GPIOx_PIN_5 | GPIOx_PIN_6
};
gpio_port_t  sw_i2c_port = {
    .ctx = &sw_i2c_gpio_ctx,
    .ops = &stm32_gpio_ops,
};

void sda(uint8_t level)
{
    sw_i2c_port.ops->write(sw_i2c_port.ctx,GPIOx_PIN_6,level);
}
void scl(uint8_t level)
{
    sw_i2c_port.ops->write(sw_i2c_port.ctx,GPIOx_PIN_5,level);
}
void start(void)
{
    sda(1);
    scl(1);
    osal_delay_ms(50);
    sda(0);
    osal_delay_ms(50);
    scl(0);
    osal_delay_ms(50);
}
void stop(void)
{

    sda(0);
    scl(0);
    osal_delay_ms(50);
    scl(1);
    osal_delay_ms(50);
    sda(1);
    osal_delay_ms(50);
}
void sent_one(void)
{
    sda(1);
    osal_delay_ms(50);
    scl(1);
    osal_delay_ms(50);
    scl(0);
    osal_delay_ms(50);
    sda(0);

}
void sent_zero(void)
{
    sda(0);
    osal_delay_ms(50);
    scl(1);
    osal_delay_ms(50);
    scl(0);
}
uint8_t receive_one_or_zero(void)
{
    uint8_t bit = 0;
    sda(1);
    scl(1);
    if((sw_i2c_gpio_ctx.gpio->IDR>> 6) & 0x01)
    {
        bit = 1;
    }
    scl(0);
    return bit;
}
uint8_t i2c_sent_ack(void)
{
    uint8_t bit = 1;
    sda(1);
    scl(1);
    if((sw_i2c_gpio_ctx.gpio->IDR>>6) == 1)
    {
        bit = 0;
    }
    scl(0);
    return bit;
}
void i2c_receive_ack(void)
{
    sda(0);
    scl(1);
    scl(0);
}
uint8_t i2c_send_Byte(uint8_t data)
{
    uint8_t success =1;
    for(uint8_t i = 0 ; i < 8 ; i++)
    {
        if((data>>(7-i)) & 0x01)
        {
            sent_one();
        }
        else
        {
            sent_zero();
        }
    }   
    if(i2c_sent_ack() == 1)
    {
        success = 0;
    }
    return success;
}
uint8_t i2c_receive_byte(void)
{
    uint8_t data = 0x00; 
    for(uint8_t i = 0 ; i < 8 ; i++)
    {
        if(receive_one_or_zero() == 1)
        {
            data|=0x01 << (7 - i);
        }
    }
    //i2c_receive_ack();
    return data;
}

uint8_t at24c02_read(uint8_t address)
{
    uint8_t data = 0;
    start();
    i2c_send_Byte(0xA0);
    i2c_send_Byte(address);
    start();
    i2c_send_Byte(0xA1);
    data = i2c_receive_byte();
    stop();
    return data;
}
void at24c02_write(uint8_t data,uint8_t address)
{
    start();
    i2c_send_Byte(0xA0);
    i2c_send_Byte(address);
    i2c_send_Byte(data);
    stop();

}
int main(void)
{   
    sw_i2c_port.ops->init(sw_i2c_port.ctx);

    //at24c02_write(0xFF,0);
//    osal_delay_ms(1);
    at24c02_read(1);

    while (1)
    {
        
    }
    return 0;
}

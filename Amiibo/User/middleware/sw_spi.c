#include "sw_spi.h"
#include "./osal/OSAL.h"
#include "oled.h"

void sw_spi_init(void *ctx)
{
    if(ctx==NULL)
    {
        return;
    }
    sw_spi_ctx_t*  sw_spi = (sw_spi_ctx_t*)ctx; 
    gpio_port_init(sw_spi->gpio_input);
    gpio_port_init(sw_spi->gpio_output);
}

static void sw_spi_sent_byte(void*ctx,uint8_t data)
{
   sw_spi_ctx_t*  sw_spi = (sw_spi_ctx_t*)ctx; 
   for(uint8_t idx = 0 ; idx < 8 ;idx++)
   {
       gpio_port_write(sw_spi->gpio_output,sw_spi->MOSI,(data >>(7 -idx) & 0x01));
       //osal_delay_ms(5);
       gpio_port_write(sw_spi->gpio_output,sw_spi->CLK,GPIO_LEVEL_LOW);
       gpio_port_write(sw_spi->gpio_output,sw_spi->CLK,GPIO_LEVEL_HIGH);
       gpio_port_write(sw_spi->gpio_output,sw_spi->CLK,GPIO_LEVEL_LOW);
   }
}
static uint8_t sw_spi_recieve_byte(void*ctx,uint8_t data)
{
    if(ctx==NULL)
    {
        return 0;
    }

   sw_spi_ctx_t*  sw_spi = (sw_spi_ctx_t*)ctx; 
   uint8_t temp_data = 0x00; 
   for(uint8_t idx = 0 ; idx < 8 ;idx++)
   {
       gpio_port_write(sw_spi->gpio_output,sw_spi->CLK,GPIO_LEVEL_LOW);
       gpio_port_write(sw_spi->gpio_output,sw_spi->CLK,GPIO_LEVEL_HIGH);
       temp_data |= gpio_port_read(sw_spi->gpio_input,sw_spi->MISO) << (7 - idx); 
   }
   return temp_data;
}


uint32_t sw_spi_transmit(void*ctx ,spi_msg_t *msg,uint16_t num)
{
    if(ctx==NULL)
    {
        return 0;
    }
    sw_spi_ctx_t*  sw_spi = (sw_spi_ctx_t*)ctx; 
    gpio_port_write(sw_spi->gpio_output,sw_spi->CS,GPIO_LEVEL_HIGH);
    gpio_port_write(sw_spi->gpio_output,sw_spi->CS,GPIO_LEVEL_LOW);
    for(uint8_t idx = 0 ; idx < num ; idx ++)
    {
        for(uint8_t cmd_count = 0 ; cmd_count < msg->len ; cmd_count++) 
        {
            sw_spi_sent_byte(ctx,(msg + idx)->buf[cmd_count]);
        }
    }
    gpio_port_write(sw_spi->gpio_output,sw_spi->CS,GPIO_LEVEL_HIGH);
    return num;
}


const spi_ops_t sw_spi_ops = {
    .init = sw_spi_init,
    .transmit = sw_spi_transmit
};

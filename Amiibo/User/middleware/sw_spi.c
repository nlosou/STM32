#include "sw_spi.h"

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

static uint8_t sw_spi_sent_byte(void*ctx,uint8_t data)
{
   //OLED_ShowHex(0,1,1);
   sw_spi_ctx_t*  sw_spi = (sw_spi_ctx_t*)ctx; 
   gpio_port_t *port = sw_spi->gpio_output; 
   gpio_port_t *port_intput = sw_spi->gpio_input; 
   uint16_t clk_pin = sw_spi->CLK;
   uint16_t mosi_pin = sw_spi->MOSI;
   uint16_t miso_pin = sw_spi->MISO;
   uint8_t temp_level[8] = {0};
   uint8_t temp_data = 0x00; 


   for(uint8_t idx = 0 ; idx < 8 ;idx++)
   {

        temp_level[idx] =(data >>(7 -idx) & 0x01);
   }
   for(uint8_t idx = 0 ; idx < 8 ;idx++)
   {
       gpio_port_write(port,mosi_pin,temp_level[idx]);
       //gpio_port_write(port,clk_pin,GPIO_LEVEL_LOW);
       gpio_port_write(port,clk_pin,GPIO_LEVEL_HIGH);
       temp_data |= gpio_port_read(port_intput,miso_pin) << (7 - idx); 
       gpio_port_write(port,clk_pin,GPIO_LEVEL_LOW);
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
   gpio_port_t *port_output = sw_spi->gpio_output; 
   uint16_t clk_pin = sw_spi->CLK;
   for(uint16_t idx = 0 ; idx < num ; idx ++)
    {
        for(uint8_t cmd_count = 0 ; cmd_count < msg[idx].len + msg[idx].get_buf_len ; cmd_count++) 
        {
            if(cmd_count < msg[idx].len)
            {
                sw_spi_sent_byte(ctx,(msg + idx)->buf[cmd_count]);
            }
            else
            {
               msg[idx].getbuf[cmd_count - msg[idx].len] = sw_spi_sent_byte(ctx,0x00);
            }
        }
    }
    return num;
}

const spi_ops_t sw_spi_ops = {
    .init = sw_spi_init,
    .transmit = sw_spi_transmit
};

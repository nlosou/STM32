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

//发送一个字节
static uint8_t sw_spi_sent_byte(void*ctx,uint8_t data,uint8_t bit_order)
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

   if(bit_order == MSB)
   {
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
   }
   else
   {
       for(uint8_t idx = 0 ; idx < 8 ;idx++)
       {

            temp_level[idx] =(data >>(idx) & 0x01);
       }
       for(uint8_t idx = 0 ; idx < 8 ;idx++)
       {
           gpio_port_write(port,mosi_pin,temp_level[idx]);
           //gpio_port_write(port,clk_pin,GPIO_LEVEL_LOW);
           gpio_port_write(port,clk_pin,GPIO_LEVEL_HIGH);
           temp_data |= gpio_port_read(port_intput,miso_pin) << (idx); 
           gpio_port_write(port,clk_pin,GPIO_LEVEL_LOW);
       }
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

    for(uint32_t cmd_count = 0 ; cmd_count < msg->len + msg->get_buf_len ; cmd_count++) 
    {
        if(cmd_count < msg->len)
        {
            sw_spi_sent_byte(ctx,(msg)->buf[cmd_count],msg->bit_oder);
        }
        else
        {
            //让主机产生clk给从机器
           msg->getbuf[cmd_count - msg->len] = sw_spi_sent_byte(ctx,0x00,msg->bit_oder);
        }
    }
    return num;
}

const spi_ops_t sw_spi_ops = {
    .init = sw_spi_init,
    .transmit = sw_spi_transmit
};

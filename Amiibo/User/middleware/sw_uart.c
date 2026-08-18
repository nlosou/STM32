#include "sw_uart.h"



static void sw_uart_init(void* ctx)
{
   if(ctx == NULL) 
   {
       return;
   }
   
   sw_uart_ctx_t* sw_uart = (sw_uart_ctx_t*)(ctx);
   gpio_port_write(sw_uart->TX,sw_uart->TX_PIN,GPIO_LEVEL_HIGH);
   gpio_port_init(sw_uart->RX);
   gpio_port_init(sw_uart->TX);
   Timer_init(sw_uart->timer);
   Timer_update_ck_cnt(sw_uart->timer);
   nvic_init(sw_uart->nvic_exti);
   nvic_init(sw_uart->nvic_timer);
   exti_init(sw_uart->exti);
}


static void sw_uart_start_bit(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
   sw_uart_ctx_t* sw_uart = (sw_uart_ctx_t*)(ctx);
   gpio_port_t* port = sw_uart->TX;
   uint16_t TX_PIN = sw_uart->TX_PIN;

   gpio_port_write(port,TX_PIN,GPIO_LEVEL_HIGH);
}

static void sw_uart_parity_bit(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
   sw_uart_ctx_t* sw_uart = (sw_uart_ctx_t*)(ctx);
   gpio_port_t* port = sw_uart->TX;
   uint16_t TX_PIN = sw_uart->TX_PIN;
   gpio_port_write(port,TX_PIN,GPIO_LEVEL_LOW);
}
static void sw_uart_stop_bit(void*ctx)
{
    if(ctx == NULL)
    {
        return;
    }
   sw_uart_ctx_t* sw_uart = (sw_uart_ctx_t*)(ctx);
   gpio_port_t* port = sw_uart->TX;
   uint16_t TX_PIN = sw_uart->TX_PIN;
   //gpio_port_write(port,TX_PIN,GPIO_LEVEL_LOW);
   gpio_port_write(port,TX_PIN,GPIO_LEVEL_HIGH);
}
uint8_t tmep = 0;
static void sw_uart_send_data(void*ctx ,uint16_t transfer_data)
{
    if(ctx == NULL)
    {
        return;
    }
    sw_uart_ctx_t* sw_uart = (sw_uart_ctx_t*)(ctx);
    gpio_port_t* port = sw_uart->TX;
    uint16_t TX_PIN = sw_uart->TX_PIN;
    uint8_t tmep_bit[10] = {0};                      //默认填入开始位
    tmep_bit[9] = 1;                                //填入停止位
                                                    //
    for(uint8_t idx = 0 ; idx < 8 ; idx++)
    {
        tmep_bit[idx + 1] = (transfer_data >>idx) & 0x01 ;
    }
    Timer_start(sw_uart->timer);
    uint8_t idx = 0;
    while(idx < 10)
    {
        if(flag)
        {
            gpio_port_write(port,TX_PIN,tmep_bit[idx++]);
            flag = 0;
        }
    }
    Timer_close(sw_uart->timer);
}

static void sw_uart_recieve_data(void*ctx,uint16_t* receive_data)
{
    if(ctx == NULL)
    {
        return;
    }

    if(fetch_complete)
    {
        *receive_data = uart_receive_data;
        uart_receive_data = 0;
        bit_idx = 0;
        fetch_complete = 0;
        tmep = 1;
        
    }
}

static uint8_t sw_uart_transmit(void*ctx,uart_msg_t* msg,uint16_t msg_num)
{
    if(ctx == NULL)
    {
        return 0;
    }

    sw_uart_recieve_data(ctx,msg->recieve_buf);
    if(tmep)
    {
        sw_uart_send_data(ctx,*(msg->recieve_buf));
        tmep =0;
    }
    return 1;
}

const uart_ops_t uart_ops = {
    .init = sw_uart_init,
    .transmit = sw_uart_transmit
};

#include "sw_uart.h"



volatile Uart_rx_sate sw_uart_recieve_state = Idel;
volatile uint8_t uart_receive_data = 0x00;
volatile uint8_t bit_idx = 0;
volatile uint32_t flag = 0;
volatile uint8_t fetch_complete = 0;
volatile uint8_t  uart_transfer_idx = 0;
volatile uint8_t get_pin_level =0;
volatile uint8_t Uart_tx_busy = 0;
volatile uint8_t Uart_tx_idx = 0;

uint8_t TX_tmep_bit[10] = {0};                      //默认填入开始位

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
   Timer_init(sw_uart->time_tx);
   Timer_init(sw_uart->time_rx);
   Timer_update_ck_cnt(sw_uart->time_tx);
   Timer_update_ck_cnt(sw_uart->time_rx);
   nvic_init(sw_uart->nvic_exti);
   nvic_init(sw_uart->nvic_timer_tx);
   nvic_init(sw_uart->nvic_timer_rx);
   exti_init(sw_uart->exti);
}

static void sw_uart_send_data(void*ctx ,uint16_t transfer_data)
{
    if(ctx == NULL)
    {
        return;
    }
    sw_uart_ctx_t* sw_uart = (sw_uart_ctx_t*)(ctx);
    gpio_port_t* port = sw_uart->TX;
    uint16_t TX_PIN = sw_uart->TX_PIN;
        
    //预处理
    TX_tmep_bit[9] = 1;                                //填入停止位
    for(uint8_t idx = 0 ; idx < 8 ; idx++)
    {
        TX_tmep_bit[idx + 1] = (transfer_data >>idx) & 0x01 ;
    }
    Uart_tx_busy = 1;
    Uart_tx_idx = 0;
    Timer_start(sw_uart->time_tx);
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
        
    }
}

static uint8_t sw_uart_transmit(void*ctx,uart_msg_t* msg,uint16_t msg_num)
{
    if(ctx == NULL)
    {
        return 0;
    }
    sw_uart_send_data(ctx,*msg->recieve_buf);
    sw_uart_recieve_data(ctx,msg->recieve_buf);
    //TODO 暂时这样写,应该使用状态机组织TX和RX
    return 1;
}

const uart_ops_t uart_ops = {
    .init = sw_uart_init,
    .transmit = sw_uart_transmit
};

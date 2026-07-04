#include "sw_I2C.h"
#define SDA(x) gpio_port_write(i2c_sda.port,i2c_sda.use_pins,x)
#define SCL(x) gpio_port_write(i2c_scl.port,i2c_scl.use_pins,x)
#define BASE_MASK (0x0F)
#define BASE_ONE (0x01)

//这里可以直接调用抽象的gpio函数吗?
void sw_i2c_init(void* ctx)
{
    sw_i2c_ctx_t* sw_i2c_ctx = (sw_i2c_ctx_t*)ctx;
    if(sw_i2c_ctx == NULL)
    {
        return;
    }
    gpio_port_init(sw_i2c_ctx->gpio);
}



static void sw_i2c_scl(void*ctx,gpio_level_t level)
{
    
    sw_i2c_ctx_t* sw_i2c_ctx = (sw_i2c_ctx_t*)ctx;
    if(sw_i2c_ctx == NULL)
    {
        return;
    }

    gpio_port_write(sw_i2c_ctx->gpio,sw_i2c_ctx->scl,level);

}
static void sw_i2c_sda(void*ctx,gpio_level_t level)
{
    sw_i2c_ctx_t* sw_i2c_ctx = (sw_i2c_ctx_t*)ctx;
    if(sw_i2c_ctx == NULL)
    {
        return;
    }
    gpio_port_write(sw_i2c_ctx->gpio,sw_i2c_ctx->sda,level);
}

static void sw_i2c_start(void*ctx)
{

   sw_i2c_ctx_t* sw_i2c_ctx = (sw_i2c_ctx_t*)ctx;

   sw_i2c_sda(ctx, 1);
   sw_i2c_scl(ctx, 1);
   sw_i2c_ctx->i2c_delay(5);
   sw_i2c_sda(ctx, 0);
   sw_i2c_ctx->i2c_delay(5);
   sw_i2c_scl(ctx, 0);
}

static void sw_i2c_stop(void*ctx)
{
    
   sw_i2c_ctx_t* sw_i2c_ctx = (sw_i2c_ctx_t*)ctx;

   sw_i2c_sda(ctx, 0);
   sw_i2c_scl(ctx, 0);

   sw_i2c_ctx->i2c_delay(5);

   sw_i2c_scl(ctx, 1);

   sw_i2c_ctx->i2c_delay(5);

   sw_i2c_sda(ctx, 1);
}
static void sw_i2c_sent_bit1(void*ctx)
{
   sw_i2c_ctx_t* sw_i2c_ctx = (sw_i2c_ctx_t*)ctx;
   sw_i2c_sda(ctx, 1);

   sw_i2c_ctx->i2c_delay(10);

   sw_i2c_scl(ctx, 1);
   sw_i2c_ctx->i2c_delay(5);
   sw_i2c_scl(ctx, 0);
   sw_i2c_ctx->i2c_delay(5);
   sw_i2c_sda(ctx, 0);
}

static void sw_i2c_sent_bit0(void*ctx)
{
   sw_i2c_ctx_t* sw_i2c_ctx = (sw_i2c_ctx_t*)ctx;
   sw_i2c_sda(ctx, 0);
   sw_i2c_scl(ctx, 1);
   sw_i2c_ctx->i2c_delay(5);
   sw_i2c_scl(ctx, 0);

}
static uint8_t sw_i2c_receive_bit0_or_bit1(void*ctx)
{

    uint8_t bit = 0;
    sw_i2c_sda(ctx,1);
    sw_i2c_scl(ctx,1);
    sw_i2c_ctx_t* sw_i2c_ctx = (sw_i2c_ctx_t*)ctx;
    if(gpio_port_read(sw_i2c_ctx->gpio,sw_i2c_ctx->sda))
    {
        bit = 1;        
    }
    sw_i2c_scl(ctx,0);
    return bit;
}
static uint8_t sw_i2c_sent_ack(void*ctx)
{
    uint8_t bit = 1;
    sw_i2c_sda(ctx,1);
    sw_i2c_scl(ctx,1);
    sw_i2c_ctx_t* sw_i2c_ctx = (sw_i2c_ctx_t*)ctx;
    if(gpio_port_read(sw_i2c_ctx->gpio,sw_i2c_ctx->sda))
    {
        bit = 0;        
    }
    sw_i2c_scl(ctx,0);
    return bit;
}
static  void sw_i2c_receive_NOACK(void*ctx)
{
    sw_i2c_sda(ctx,1);
    sw_i2c_scl(ctx,1);
    sw_i2c_scl(ctx,0);
}

static void sw_i2c_sent_byte(void*ctx,uint8_t data)
{
    sw_i2c_ctx_t* sw_i2c_ctx = (sw_i2c_ctx_t*)ctx;
    uint8_t success = 1;
    for(uint8_t i = 0 ;  i < 8 ; i++)
    {
        if((data>>(7-i))&0x01)
        {
            sw_i2c_sent_bit1(ctx);
        }
        else
        {
            sw_i2c_sent_bit0(ctx);
        }
    }
}

static uint8_t sw_i2c_receive_byte(void*ctx)
{
    uint8_t data = 0x00;
    for(uint8_t i = 0 ; i < 8 ; i++)
    {
        if(sw_i2c_receive_bit0_or_bit1(ctx)==1)
        {
            data|=0x01 << (7-i);
        }
    }
    return data;
}


uint16_t sw_i2c_transfer(void*ctx,i2c_msg_t* msgs,uint16_t num)
{
    for(uint16_t i = 0 ; i < num; i++)
    {
        i2c_msg_t *msg = &msgs[i];

        sw_i2c_start(ctx);

        uint8_t addr_byte = msg->addr |((msg->flags & I2C_M_RD) ? 1 : 0);
        sw_i2c_sent_byte(ctx,addr_byte);
        sw_i2c_sent_ack(ctx);
        for(uint16_t j = 0 ; j < msg->len;j++)
        {
            if(msg->flags & I2C_M_RD)
            {
                uint8_t ack = (j == msg->len - 1) ? 0 : 1;
                msg->buf[j] = sw_i2c_receive_byte(ctx);
                sw_i2c_receive_NOACK(ctx);
            }
            else
            {
                sw_i2c_sent_byte(ctx,msg->buf[j]);
                sw_i2c_sent_ack(ctx);
            }
        }
    }
    sw_i2c_stop(ctx);
    return num;
}

const i2c_ops_t sw_i2c_ops = {
    .init = sw_i2c_init,
    .transfer = sw_i2c_transfer
};

#include "sw_I2C.h"
#define SDA(x) gpio_port_write(i2c_sda.port,i2c_sda.use_pins,x)
#define SCL(x) gpio_port_write(i2c_scl.port,i2c_scl.use_pins,x)
#define BASE_MASK (0x0F)
#define BASE_ONE (0x01)


typedef struct {
    gpio_port_t* SCL_PIN;
    gpio_port_t* SDA_PIN;
}sw_i2c_ctx;



static void sw_i2c_init(void *ctx)
{

    sw_i2c_ctx *sw_i2c = (sw_i2c_ctx*)ctx;
    //特定port的遮罩 

    if(sw_i2c== NULL)
    {
        return;
    }

}
static void sw_i2c_SDA(void *ctx,gpio_level_t level)
{
    sw_i2c_ctx *sw_i2c = (sw_i2c_ctx*)ctx;

    if(sw_i2c == NULL)
    {
        return;
    } 
    gpio_port_t *sda = sw_i2c->SDA_PIN;
    //sda->ops->write(sda->ops,)
    
}
static void sw_i2c_SCL(void *ctx,gpio_level_t level)
{
   sw_i2c_ctx *sw_i2c = (sw_i2c_ctx*)ctx;

    if(sw_i2c == NULL)
    {
        return;
    }
}


void sw_i2c_start(void* ctx)
{
    sw_i2c_SDA(ctx,1);
    sw_i2c_SCL(ctx,1);
    sw_i2c_SDA(ctx,0);
    sw_i2c_SCL(ctx,0);
}


void sw_i2c_stop(void* ctx)
{
    sw_i2c_SDA(ctx,0);
    sw_i2c_SCL(ctx,0);
    sw_i2c_SCL(ctx,1);
    sw_i2c_SDA(ctx,1);
}

void sw_i2c_sent_one(void* ctx)
{
    sw_i2c_SDA(ctx,1);
    sw_i2c_SCL(ctx,1);
    sw_i2c_SCL(ctx,0);
    sw_i2c_SDA(ctx,0);
}
void sw_i2c_sent_zero(void* ctx)
{
    sw_i2c_SDA(ctx,0);
    sw_i2c_SCL(ctx,1);
    sw_i2c_SCL(ctx,0);
    sw_i2c_SDA(ctx,0);
}

uint8_t sw_i2c_receive_one_or_zero(void*ctx)
{
   sw_i2c_ctx *sw_i2c = (sw_i2c_ctx*)ctx;
//   return sw_i2c->SDA_PIN & sw_i2c->gpio->ODR;
    return 0;
}



#include "at24c02.h"

void at24c02_init(at24c02_t *at24)
{
    if(at24 == NULL)
    {
        return;
    }
    i2c_init(at24->i2c);
}
uint16_t at24c02_read(at24c02_t *at24,uint8_t reg_addr,uint8_t *data)
{
    if(at24 == NULL)
    {
        return 0;
    }
    i2c_msg_t msgs[2];
    uint8_t reg = reg_addr;
    msgs[0].addr = 0xA0;
    msgs[0].flags = 0;
    msgs[0].len = 1;
    msgs[0].buf = &reg;

    
    msgs[1].addr = 0xA0;
    msgs[1].flags = I2C_M_RD;
    msgs[1].len = 1;
    msgs[1].buf = data;

    return at24->i2c->ops->transfer(at24->i2c->ctx,msgs,2);
}
void at24c02_write(at24c02_t *at24,uint8_t data,uint8_t address)
{
    if(at24 == NULL)
    {
        return;
    }
    
}

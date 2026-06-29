#include "at24c02.h"

void at24c02_init(at24c02_t *at24)
{
    if(at24 == NULL)
    {
        return;
    }
    i2c_init(at24->i2c);
}
uint8_t at24c02_read(at24c02_t *at24,uint8_t data_address)
{
    if(at24 == NULL)
    {
        return 0;
    }
    uint8_t data = 0;
    i2c_start(at24->i2c);
    i2c_write(at24->i2c,at24->dev_address_write);
    i2c_write(at24->i2c,data_address);
    i2c_start(at24->i2c);
    i2c_write(at24->i2c,at24->dev_address_read);
    data = i2c_read(at24->i2c);
    i2c_stop(at24->i2c);
    return data;
}
void at24c02_write(at24c02_t *at24,uint8_t data,uint8_t address)
{
    if(at24 == NULL)
    {
        return;
    }
    i2c_start(at24->i2c);
    i2c_write(at24->i2c,at24->dev_address_write);
    i2c_write(at24->i2c,address);
    i2c_write(at24->i2c,data);
    i2c_stop(at24->i2c);

}

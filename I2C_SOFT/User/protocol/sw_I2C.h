#ifndef SW_I2C_H__
#define SW_I2C_H__
#include "i2c_port.h"
#include "gpio_port.h"


typedef struct{
    gpio_port_t *gpio;
    uint16_t scl;
    uint16_t sda;
    void (*i2c_delay)(uint32_t ms);
}sw_i2c_ctx_t;

extern const i2c_ops_t sw_i2c_ops ;

#endif

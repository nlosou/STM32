#ifndef AT24C02_H_
#define AT24C02_H_



#include "./protocol/i2c_port.h"

typedef struct {
    i2c_port_t* i2c;
    uint16_t scl;
    uint16_t sda;
    uint8_t data_address;
    uint8_t dev_address_read;
    uint8_t dev_address_write;
    
}at24c02_t;
void at24c02_init(at24c02_t *at24);


void at24c02_write(at24c02_t *at24,uint8_t data,uint8_t address);
uint16_t at24c02_read(at24c02_t *at24,uint8_t reg_addr,uint8_t* data);


#endif

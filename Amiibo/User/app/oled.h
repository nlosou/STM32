#ifndef OLED_H_
#define OLED_H_
#include "i2c_port.h"


typedef struct {
    i2c_port_t* i2c_port; 
    uint16_t sda;
    uint16_t scl;
    uint8_t dev_address;
}oled_t;


void oled_init_hal(oled_t* oled);
uint16_t oled_init(oled_t* oled);
//uint16_t oled_test(oled_t* oled);
//uint16_t oled_transfer(oled_t* oled,uint8_t *data);
uint16_t oled_point(oled_t* oled);
//void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t color);
void OLED_ShowChar(uint8_t row,uint8_t colum,char letter);
void OLED_ShowString(uint8_t row,uint8_t colum,char* string);
void OLED_ShowHex(uint8_t row ,uint8_t colum,uint16_t num);
void OLED_ShowBin(uint8_t row ,uint8_t colum,uint16_t num);

#endif

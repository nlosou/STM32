#ifndef PN532_H_
#define PN532_H_
#include "spi_port.h"
#include "middleware/spi_select_opp.h"



typedef struct {
    spi_port_t *port;
    spi_select_port_t *select;
    uint16_t CS;
    uint8_t bit_order;
}PN532_ctx_t;
uint8_t PN532_write_card(PN532_ctx_t* PN532,uint8_t* need_write_data);
uint8_t PN532_PWD_AUTH(PN532_ctx_t* PN532);
uint8_t PN532_write_card_test(PN532_ctx_t* PN532,uint8_t* need_write_data);

uint8_t PN532_write_lock(PN532_ctx_t* PN532,uint8_t* need_write_data);
uint8_t PN532_read_card(PN532_ctx_t* PN532,uint8_t page_address);




#endif

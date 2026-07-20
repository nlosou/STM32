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
uint8_t PN532_getgirmwareversion(PN532_ctx_t* PN532);
uint8_t PN532_GetGeneralStatus(PN532_ctx_t* PN532);
uint8_t PN532_InListPassiveTarget(PN532_ctx_t* PN532);
uint8_t PN532_RFConfiguration(PN532_ctx_t* PN532);



#endif

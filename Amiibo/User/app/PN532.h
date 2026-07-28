#ifndef PN532_H_
#define PN532_H_
#include "spi_port.h"
#include "middleware/spi_select_opp.h"
#include "nfc_hal.h"

//=================command==================
#define GetFirmwareVersion 0x02
#define GetGeneralStatus   0x04
#define SAMConfiguration   0x14
#define TgGetTargetStatus  0x8A
#define InCommunicateThru  0x42


#define RFConfiguration     0x32
#define InListPassiveTarget 0x4A
#define InDataEXchange      0x40

typedef struct {
    spi_port_t *port;
    spi_select_port_t *select;
    uint16_t CS;
    uint8_t bit_order;
}PN532_ctx_t;


extern const nfc_ops_t nfc_ops;

#endif

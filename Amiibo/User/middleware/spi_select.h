#ifndef SPI_SELECT_H
#define SPI_SELECT_H
#include "gpio_port.h"
#include "spi_select_opp.h"

typedef struct {
    gpio_port_t *cs;
}spi_select_ctx_t;

extern const spi_select_ops_t spi_select_ops;

#endif

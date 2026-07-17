#ifndef SW_SPI_H_
#define SW_SPI_H_
#include "spi_port.h"
#include "gpio_port.h"

typedef struct {
    gpio_port_t *gpio_output;
    gpio_port_t *gpio_input;
    uint16_t MOSI;
    uint16_t MISO;
    uint16_t CLK;
}sw_spi_ctx_t;

extern const spi_ops_t sw_spi_ops;

#endif

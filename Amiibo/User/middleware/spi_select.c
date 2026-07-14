#include "spi_select.h"



void spi_select_real(void*ctx,uint16_t cs_pin,uint8_t level)
{
    if(ctx==NULL)
    {
        return;
    }
    spi_select_ctx_t* spi_select_ctx = (spi_select_ctx_t*)ctx;
    gpio_port_write(spi_select_ctx->cs,cs_pin,level);
}

const spi_select_ops_t spi_select_ops = {
    .select_device = spi_select_real
};

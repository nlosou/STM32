#include "bsp_devices.h"
#include "board_config.h"
#include <stdint.h>







int main(void)
{   
    
    gpio_port_t* spi_out = bsp_get_spi_out();
    gpio_port_t* spi_input = bsp_get_spi_input();
    oled_t *oled = bsp_get_oled();
    spi_out->ops->init(spi_out->ctx);
    spi_input->ops->init(spi_input->ctx);
    oled_init_hal(oled);
    oled_init(oled);
    uint8_t ManufacturerID = 0x00;
    uint8_t DevieceId = 0x00;
    uint8_t data[16];

    //片选
    spi_out->ops->write(spi_out->ctx,W25QXX_CS_PIN , 1);

    uint8_t cmd = 0x90;
    //片选
    spi_out->ops->write(spi_out->ctx,W25QXX_CS_PIN , 0);

    for(uint8_t  idx = 0 ; idx < 8 ; idx++)
    {
        spi_out->ops->write(spi_out->ctx,W25QXX_DI_PIN,(cmd >> (7 - idx))&0x01);
        spi_out->ops->write(spi_out->ctx,W25QXX_CLK_PIN,0);
        spi_out->ops->write(spi_out->ctx,W25QXX_CLK_PIN,1);
        spi_out->ops->write(spi_out->ctx,W25QXX_CLK_PIN,0);
    }

    for(uint8_t  idx = 0 ; idx < 24 ; idx++)
    {
        spi_out->ops->write(spi_out->ctx,W25QXX_DI_PIN,0);
        spi_out->ops->write(spi_out->ctx,W25QXX_CLK_PIN,0);
        spi_out->ops->write(spi_out->ctx,W25QXX_CLK_PIN,1);
        spi_out->ops->write(spi_out->ctx,W25QXX_CLK_PIN,0);
    }
    for(uint8_t  idx = 0 ; idx < 16 ; idx++)
    {
        spi_out->ops->write(spi_out->ctx,W25QXX_CLK_PIN,0);
        spi_out->ops->write(spi_out->ctx,W25QXX_CLK_PIN,1);
        data[idx] = spi_input->ops->read(spi_input->ctx,W25QXX_DO_PIN);
    }
    for(uint8_t  idx = 0 ; idx < 16 ; idx++)
    {
        OLED_ShowChar(idx,0,data[idx] + '0');
    }
    
    oled_point(oled);
    while (1)
    {


           
    }
    return 0;
}

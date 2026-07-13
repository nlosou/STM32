#include "board_config.h"
#include "stm32_gpio_port.h"
#include "./middleware/sw_I2C.h"
#include "./middleware/sw_spi.h"
#include "at24c02.h"
#include "oled.h"
#include "osal/OSAL.h"
#include "W25Q64FV.h"



//================ gpio相关 =========================================
static stm32_gpio_ctx_t i2c_gpio = {
    .gpio = OLED_GPIO_PORT,
    .rcc_enable_bit = OLED_BIT,
    .mode_select = OLED_GPIO_MODE,
    .use_pins = OLED_SCL_PIN | OLED_SDA_PIN 
};


static stm32_gpio_ctx_t SPI_gpio_out = {
    .gpio = spi_GPIO_PORT,
    .rcc_enable_bit = spi_BIT,
    .mode_select = spi_GPIO_MODE,
    .use_pins = spi_bus_CLK_PIN | W25QXX_CS_PIN | spi_bus_DI_PIN
};
static stm32_gpio_ctx_t SPI_gpio_input = {
    .gpio = spi_GPIO_PORT,
    .rcc_enable_bit = spi_BIT,
    .mode_select = spi_GPIO_MODE1,
    .use_pins = spi_bus_DO_PIN
};

static gpio_port_t gpio_port_ctx = {
    .ctx = &i2c_gpio,
    .ops = &stm32_gpio_ops
};
static gpio_port_t spi_gpio_port_ctx_out = {
    .ctx = &SPI_gpio_out,
    .ops = &stm32_gpio_ops
};
static gpio_port_t spi_gpio_port_ctx_input = {
    .ctx = &SPI_gpio_input,
    .ops = &stm32_gpio_ops
};



//================ 软件i2c相关 =========================================
static sw_i2c_ctx_t sw_i2c_ctx = {
    .gpio = &gpio_port_ctx,
    .scl = OLED_SCL_PIN,
    .sda = OLED_SDA_PIN,
    .i2c_delay = osal_delay_ms, 
};

static i2c_port_t i2c_port = {
    .ctx = &sw_i2c_ctx,
    .ops = &sw_i2c_ops,
};


//=============== 软件SPI相关 =========================================
static sw_spi_ctx_t sw_spi_ctx = {
    .gpio_input = &spi_gpio_port_ctx_input,
    .gpio_output = &spi_gpio_port_ctx_out,
    .CLK = spi_bus_CLK_PIN,
    .CS = W25QXX_CS_PIN,
    .MISO = spi_bus_DO_PIN,
    .MOSI = spi_bus_DI_PIN
};

static spi_port_t spi_port = {
    .ctx = &sw_spi_ctx,
    .ops = &sw_spi_ops
};

//================ 外设相关相关 =========================================
static oled_t oled_inst = {
    .i2c_port = &i2c_port,
    .dev_address = OLED_DEV_ADDRESSS,
    .scl = OLED_SDA_PIN,
    .sda = OLED_SDA_PIN
};


static W25Q64xx_ctx_t W25Qxx = {
    .port = &spi_port,
    .CS = W25QXX_CS_PIN,
    .bit_order =MSB
};
// 只有最外层的设备对象可以被外界感知
oled_t* bsp_get_oled(void)
{
    return &oled_inst;
}


W25Q64xx_ctx_t* bsp_get_w25Q64(void)
{
    return &W25Qxx;
}

/*
// 
at24c02_t* bsp_get_eeprom1(void)
{
    return &at24c02_inst;
}
*/

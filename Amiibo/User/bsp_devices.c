// bsp_devices.c
#include "board_config.h"
#include "stm32_gpio_port.h"
#include "./middleware/sw_I2C.h"
#include "at24c02.h"
#include "oled.h"
#include "osal/OSAL.h"



// 所有的静态结构体，全锁死在这个文件里，用 static 修饰，不暴露给外界
//================ gpio相关 =========================================
static stm32_gpio_ctx_t i2c_gpio = {
    .gpio = OLED_GPIO_PORT,
    .rcc_enable_bit = OLED_BIT,
    .mode_select = OLED_GPIO_MODE,
    .use_pins = OLED_SCL_PIN | OLED_SDA_PIN 
};

static stm32_gpio_ctx_t SPI_gpio_out = {
    .gpio = W25QXX_GPIO_PORT,
    .rcc_enable_bit = W25QXX__BIT,
    .mode_select = W25QXX__GPIO_MODE,
    .use_pins = W25QXX_CLK_PIN | W25QXX_CS_PIN | W25QXX_DI_PIN
};
static stm32_gpio_ctx_t SPI_gpio_input = {
    .gpio = W25QXX_GPIO_PORT,
    .rcc_enable_bit = W25QXX__BIT,
    .mode_select = W25QXX__GPIO_MODE1,
    .use_pins = W25QXX_DO_PIN
};



static gpio_port_t gpio_port_ctx = {
    .ctx = &i2c_gpio,
    .ops = &stm32_gpio_ops
};
static gpio_port_t spi_gpio_port_ctx = {
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
//================ 外设相关相关 =========================================
// 只有最外层的设备对象可以被外界感知
static oled_t oled_inst = {
    .i2c_port = &i2c_port,
    .dev_address = OLED_DEV_ADDRESSS,
    .scl = OLED_SDA_PIN,
    .sda = OLED_SDA_PIN
};


oled_t* bsp_get_oled(void)
{
    return &oled_inst;
}
gpio_port_t* bsp_get_spi_out(void)
{
    return &spi_gpio_port_ctx;
}
gpio_port_t* bsp_get_spi_input(void)
{
    return &spi_gpio_port_ctx_input;
}
/*
// 工厂函数：对外只吐出最终的设备句柄指针
at24c02_t* bsp_get_eeprom1(void)
{
    return &at24c02_inst;
}
*/

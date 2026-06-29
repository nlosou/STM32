// bsp_devices.c
#include "board_config.h"
#include "stm32_gpio_port.h"
#include "protocol/sw_I2C.h"
#include "at24c02.h"
#include "osal/OSAL.h"

// 所有的静态结构体，全锁死在这个文件里，用 static 修饰，不暴露给外界
static stm32_gpio_ctx_t i2c_gpio = {
    .gpio = EEPROM1_GPIO_PORT,
    .rcc_enable_bit = EEPROM1_RCC_BIT,
    .mode_select = EEPROM1_GPIO_MODE,
    .use_pins = EEPROM1_SCL_PIN | EEPROM1_SDA_PIN
};

static gpio_port_t gpio_port_ctx = {
    .ctx = &i2c_gpio,
    .ops = &stm32_gpio_ops
};

static sw_i2c_ctx_t sw_i2c_ctx = {
    .gpio = &gpio_port_ctx,
    .scl = EEPROM1_SCL_PIN,
    .sda = EEPROM1_SDA_PIN,
    .i2c_delay = osal_delay_ms, 
};

static i2c_port_t i2c_port = {
    .ctx = &sw_i2c_ctx,
    .ops = &sw_i2c_ops,
};

// 只有最外层的设备对象可以被外界感知
static at24c02_t at24c02_inst = {
    .i2c = &i2c_port,
    .dev_address_read = EEPROM1_DEV_ADDR_READ,
    .dev_address_write = EEPROM1_DEV_ADDR_WRITE,
    .scl = EEPROM1_SCL_PIN,
    .sda = EEPROM1_SDA_PIN
};

// 工厂函数：对外只吐出最终的设备句柄指针
at24c02_t* bsp_get_eeprom1(void)
{
    return &at24c02_inst;
}

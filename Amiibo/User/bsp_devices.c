#include "bsp_devices.h"
#include "board_config.h"
#include "stm32_gpio_port.h"
#include "./middleware/sw_I2C.h"
#include "./middleware/sw_spi.h"
#include "./middleware/spi_select.h"
#include "./middleware/sw_uart.h"
//#include "at24c02.h"
#include "oled.h"
#include "osal/OSAL.h"
#include "W25Q64FV.h"
#include "PN532.h"
#include "stm32_exti_port.h"
#include "stm32_nvic_port.h"


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
    .use_pins = spi_bus_CLK_PIN | W25QXX_CS_PIN | spi_bus_DI_PIN | PN532_CS_PIN
};
static stm32_gpio_ctx_t SPI_gpio_input = {
    .gpio = spi_GPIO_PORT,
    .rcc_enable_bit = spi_BIT,
    .mode_select = spi_GPIO_MODE1,
    .use_pins = spi_bus_DO_PIN
};

static stm32_gpio_ctx_t UART_RX_gpio= {
    .gpio = UART_RX_GPIO_PORT,
    .rcc_enable_bit = RCC_APB2ENR_IOPAEN,
    .mode_select = OUTPUT_MODE_10MHZ_General_push_pull,
    .use_pins =  UART_RX_PIN
};

static stm32_gpio_ctx_t UART_TX_gpio= {
    .gpio = UART_TX_GPIO_PORT,
    .rcc_enable_bit = RCC_APB2ENR_IOPAEN,
    .mode_select = OUTPUT_MODE_10MHZ_General_push_pull,
    .use_pins =  UART_TX_PIN
};

static stm32_gpio_ctx_t Inteerupt_gpio= {
    .gpio = GPIOA,
    .rcc_enable_bit = RCC_APB2ENR_IOPAEN,
    .mode_select =INPUT_WITH_PULLUP_PULLDOWN,
    .use_pins = GPIOx_PIN_0 | GPIOx_PIN_1
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

static gpio_port_t uart_rx_gpio_port_ctx = {
    .ctx = &UART_RX_gpio,
    .ops = &stm32_gpio_ops,
};

static gpio_port_t uart_tx_gpio_port_ctx = {
    .ctx = &UART_TX_gpio,
    .ops = &stm32_gpio_ops,
};

static gpio_port_t Interrupt_gpio_ctx = {
    .ctx = &Inteerupt_gpio,
    .ops = &stm32_gpio_ops
};

//================ EXIT相关 =========================================

static stm32_exti_ctx_t exti_test_ctx = {
    .exti = EXTI,
    .afio = AFIO,
    .exti_imr_mrx = EXTI_IMR_MR0,
    .exti_ftsr_trx = EXTI_FTSR_TR0,
    .exti_pr_prx = EXTI_PR_PR0,
    .select_interrupt_source = 0x00,
};

static exti_port_t exti_port = {
    .ctx = &exti_test_ctx,
    .ops = &stm32_exti_ops
};

//================ NVIC相关 =========================================

static stm32_nvic_ctx_t nvic_test_ctx = {
    .Interrupt_position = 6,
    .nvic_iser = NVIC_ISER,
    .nvic_icer = NVIC_ICER,
    .nvic_ispr = NVIC_ISPR,
    .nvic_icpr = NVIC_ICPR,
    .nvic_iabr = NVIC_IABR
};

static nvic_port_t nvic_port = {
    .ctx = &nvic_test_ctx,
    .ops = &stm32_nvic_ops
};


//================ 软件uart相关 =========================================

static sw_uart_ctx_t sw_uart_ctx = {
    .RX = &uart_rx_gpio_port_ctx,   
    .TX = &uart_tx_gpio_port_ctx,   
    .RX_PIN = UART_RX_PIN,
    .TX_PIN = UART_TX_PIN,
};
static uart_port_t uart_port = {
    .ctx = &sw_uart_ctx,
    .ops = &uart_ops
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
    .MISO = spi_bus_DO_PIN,
    .MOSI = spi_bus_DI_PIN
};

static spi_port_t spi_port = {
    .ctx = &sw_spi_ctx,
    .ops = &sw_spi_ops
};

static spi_select_ctx_t spi_select_ctx = {
    .cs = &spi_gpio_port_ctx_out,
};

static spi_select_port_t spi_select_port = {
    .ops = &spi_select_ops,
    .ctx = &spi_select_ctx
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
    .select = &spi_select_port,
    .CS = W25QXX_CS_PIN,
    .bit_order =MSB
};

static PN532_ctx_t PN532 = {
    .port = &spi_port,
    .select = &spi_select_port,
    .CS = PN532_CS_PIN,
    .bit_order = LSB

};

static nfc_port_ctx_t  nfc_port = {
    .ctx = &PN532,
    .ops =&nfc_ops,
};

static NTAG21x_t NTAG215  = {
    .ctx =&nfc_port ,
    .CC_Address = 0x03,
    .User_memory_Address_Start = 0x04,
    .User_memory_Address_End = 0x81,
    .Dynamic_lock_bytes_Address = 0x82,
    .Configuration_pages_Start = 0x83,
    .Configuration_pages_End = 0x86,
    .UID_Start = 0x00,
    .UID_End = 0x02,
    .Page_per_bytes = 4,
};
static Mifare_ctx_t Mifare = {
    .nfc = &nfc_port
};

static Amiibo_ctx_t Amiibo ={
    .card_info = &NTAG215
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

spi_select_port_t* bsp_get_select_spi(void)
{
    return &spi_select_port;
}
PN532_ctx_t* bsp_get_pn532(void)
{
    return &PN532;
}

Amiibo_ctx_t* bsp_get_amiibo(void)
{
    return &Amiibo;
}

Mifare_ctx_t* bsp_get_mifare(void)
{
    return &Mifare;
}

uart_port_t* bsg_get_uart_test(void)
{
    return &uart_port;
}

exti_port_t* bsp_get_exti(void)
{
    return &exti_port;
}

nvic_port_t* bsp_get_nvic(void)
{
    return &nvic_port;
}

gpio_port_t* bsp_get_gpio(void)
{
    return &Interrupt_gpio_ctx;
}

/*
// 
at24c02_t* bsp_get_eeprom1(void)
{
    return &at24c02_inst;
}
*/

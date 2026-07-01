#include "bsp_devices.h"

int main(void)
{   
    at24c02_t *eeprom = bsp_get_eeprom1();
    at24c02_init(eeprom);
    uint8_t data[2] = {0};
    at24c02_read(eeprom,0,data);
    while (1)
    {
        
    }
    return 0;
}

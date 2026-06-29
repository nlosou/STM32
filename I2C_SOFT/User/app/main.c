#include "bsp_devices.h"

int main(void)
{   
    at24c02_t *eeprom = bsp_get_eeprom1();
    at24c02_init(eeprom);
    at24c02_read(eeprom,0);
    while (1)
    {
        
    }
    return 0;
}

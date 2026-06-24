#include "key.h"
#include "./osal/OSAL.h"


void key_init(key_t *key)
{
   if(key == NULL) 
   {
       return;
   }
   gpio_port_init(key->gpio);
}

static uint32_t key(key_t *key)
{
    uint32_t bit = 0;

    bit = gpio_port_read(key->gpio,key->pins);

    return bit;
}
void key_machine(key_t *key_pins,Sys_state *sys_state)
{

    switch(key_pins->key_state)
    {
        case IDLE:
            if(!key(key_pins))
            {
                osal_delay_ms(20);
                key_pins->key_state= FILTER_DOWN;
            }
            break;
        case FILTER_DOWN:
            if(!key(key_pins))
            {
                key_pins->key_state= PRESSED;
               *sys_state = key_pins->key_represent;
            }
            else
            {
                key_pins->key_state= IDLE;
            }
            break;
        case PRESSED:
            if(!key(key_pins))
            {
            }
            else
            {
                osal_delay_ms(20);
                key_pins->key_state = FILTER_UP;
            }
            break;
        case FILTER_UP:
            if(key(key_pins))
            {
                key_pins->key_state= IDLE;
            }
            else
            {
                key_pins->key_state= PRESSED;
            }
            break;
    }
}

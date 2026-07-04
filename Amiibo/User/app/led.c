#include "led.h"

void led_init(led_t *led)
{
   if(led == NULL)
   {
       return;
   }
   gpio_port_init(led->gpio);
   led_off(led);
}

void led_on(led_t *led)
{
    if (led == NULL) {
        return;
    }

    gpio_port_write(led->gpio, led->pins, GPIO_LEVEL_HIGH);
}

void led_off(led_t *led)
{
    if (led == NULL) {
        return;
    }

    gpio_port_write(led->gpio, led->pins, GPIO_LEVEL_LOW);
}

void led_toggle(led_t *led)
{
    if (led == NULL) {
        return;
    }

    gpio_port_toggle(led->gpio, led->pins);
}

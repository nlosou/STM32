#ifndef LED_H
#define LED_H
#include <stdint.h>
#include "gpio_port.h"

typedef struct {
    gpio_port_t *gpio;
    uint16_t pins;
}led_t;


void led_init(led_t *led);
void led_on(led_t *led);
void led_off(led_t *led);
void led_toggle(led_t *led);

#endif


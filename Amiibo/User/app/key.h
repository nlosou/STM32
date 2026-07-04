#ifndef KEY_H_
#define KEY_H_
#include <stdint.h>
#include "gpio_port.h"
typedef enum {
    IDLE,
    FILTER_DOWN,
    PRESSED,
    FILTER_UP
}Key_state;

typedef enum {
    default_,
    Blink_led
}Sys_state;

typedef struct {
    gpio_port_t *gpio;
    uint16_t pins;
    Key_state key_state;    
    Sys_state key_represent;
}key_t;

void key_machine(key_t *key_pins,Sys_state *sys_state);

void key_init(key_t *key);

#endif

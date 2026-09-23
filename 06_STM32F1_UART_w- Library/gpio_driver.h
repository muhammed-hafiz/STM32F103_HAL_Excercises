#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H 

#include <stdint.h>
#include "stm32f10x.h"

void gpio_set_mode(struct gpio *gpio, uint16_t pin, uint8_t mode, uint8_t speed);


#endif 
#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include "gpio_driver.h"
#include "stm32f10x.h"
#include "systick_driver.h"

#define adc1 1
#define adc2 2 

char adc_init(char adc, struct gpio *port, short pin);
char adc_check(char adc,  struct gpio *port, short pin);
int adc_rx(char adc, struct gpio *port, short pin);
#endif
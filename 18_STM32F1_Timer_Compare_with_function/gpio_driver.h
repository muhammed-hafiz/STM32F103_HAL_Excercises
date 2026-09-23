#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H 

#include <stdint.h>
#include "stm32f10x.h"


// GPIO Output Modes
enum {GPIO_OUTPUT_MODE_PUSHPULL, GPIO_OUTPUT_MODE_OPENDRAIN, GPIO_AF_MODE_PUSHPULL,
GPIO_AF_MODE_OPENDRAIN};


// GPIO Input Modes
enum {GPIO_INPUT_MODE_ANALOG, GPIO_INPUT_MODE_INPUTFLOATING,   
GPIO_INPUT_MODE_PULL_DOWN_OR_UP};


// GPIO Speeds
enum {INPUT_SPEED, OUTPUT_10MHZ_SPEED, OUTPUT_2MHZ_SPEED, OUTPUT_50MHZ_SPEED};



void gpio_set_mode(struct gpio *gpio, uint16_t pin, uint8_t mode, uint8_t speed);


#endif 
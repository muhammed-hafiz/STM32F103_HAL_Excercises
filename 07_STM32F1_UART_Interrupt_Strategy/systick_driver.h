#ifndef SYSTICK_DRIVER_H
#define SYSTICK_DRIVER_H

#include <stdint.h>
#include "stm32f10x.h"


//void delay(volatile uint32_t counter);
void systick_init(void);
void delayms(unsigned long t);
void delaymilli(void);


#endif
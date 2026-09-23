#ifndef SYSTICK_DRIVER_H
#define SYSTICK_DRIVER_H

#include <stdint.h>
#include "stm32f10x.h"


//void delay(volatile uint32_t counter);
void systick_init(void);
void delayms(unsigned long t);
void delaymilli(void);
void systick_int_start(void);
void systick_int(unsigned short uart_1_mgr[], unsigned short uart_2_mgr[], unsigned short uart_3_mgr[]);


#endif
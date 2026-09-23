#include "systick_driver.h"

/*
inline void delay(volatile uint32_t counter){
	while(counter--) asm("nop");
} */

void delaymilli(void)
{
    SYSTICK->LOAD = 72000;
    SYSTICK->VAL = 0;
    while ((SYSTICK->CTRL & 0x00010000) == 0);
}

void delayms(unsigned long t)
{
    for (;t>0;t--){
        delaymilli();
    }
}

void systick_init(void)
{
    SYSTICK->CTRL = 0;
    SYSTICK->LOAD = 0X00FFFFFF;
    SYSTICK->VAL = 0;
    SYSTICK->CTRL |= 5;
}

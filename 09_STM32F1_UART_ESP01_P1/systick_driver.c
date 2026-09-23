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

void systick_int_start(void)
{
    __disable_irq();
    SYSTICK->CTRL = 0;
    SYSTICK->LOAD = 72000; // every 1 ms
    SYSTICK->VAL = 0;
    SYSTICK->CTRL |= 7;  
    __enable_irq();
}

void systick_int(unsigned short uart_1_mgr[], unsigned short uart_2_mgr[], unsigned short uart_3_mgr[])
{
    if (uart_1_mgr[0] != 0)
    {
        if (uart_1_mgr[6] == 0)
        {
            uart_1_mgr[0] = 0;
            uart_1_mgr[1] = 1;
            systick_init();
        } else
        {
            uart_1_mgr[6]--;
        }
    }

     if (uart_2_mgr[0] != 0)
    {
        if (uart_2_mgr[6] == 0)
        {
            uart_2_mgr[0] = 0;
            uart_2_mgr[1] = 1;
            systick_init();
        } else
        {
            uart_2_mgr[6]--;
        }
    } 

     if (uart_3_mgr[0] != 0)
    {
        if (uart_3_mgr[6] == 0)
        {
            uart_3_mgr[0] = 0;
            uart_3_mgr[1] = 1;
            systick_init();
        } else
        {
            uart_3_mgr[6]--;
        }
    }
}
#include "stm32f10x.h"


void clock_init(void)
{
    RCC->RCC_CR |= (1 << 16);              // Enable HSE
    while (!(RCC->RCC_CR & (1 << 17)));    // Wait for HSE ready

    FLASH->ACR |= (2 << 0);               // 2 wait states for 72 MHz

    // Configure PLL: 8MHz * 9 = 72 MHz
    RCC->RCC_CFGR &= ~(0xF << 18);
    RCC->RCC_CFGR |=  (7 << 18);          // PLL mul = 9
    RCC->RCC_CFGR &= ~(1 << 17);          // HSE not divided (PLLXTPRE = 0)
    RCC->RCC_CFGR |=  (1 << 16);          // **PLLSRC = HSE** (select HSE as PLL source)

    // Prescalers
    RCC->RCC_CFGR &= ~(0xF << 4);         // AHB = SYSCLK (no divide)
    RCC->RCC_CFGR &= ~(0x7 << 8); 
    RCC->RCC_CFGR |=  (0x4 << 8);         // APB1 = SYSCLK/2
    RCC->RCC_CFGR &= ~(0x7 << 11);        // APB2 = SYSCLK (no divide)

    RCC->RCC_CR   |=  (1 << 24);          // Enable PLL
    while (!(RCC->RCC_CR & (1 << 25)));   // Wait PLL ready

    RCC->RCC_CFGR &= ~(0x3 << 0);
    RCC->RCC_CFGR |=  (0x2 << 0);         // Switch SYSCLK to PLL
    while (((RCC->RCC_CFGR >> 2) & 0x3) != 0x2); // Wait switch
}



void __disable_irq(void)
{
	__asm volatile ("CPSID i" ::: "memory");

}


void __enable_irq(void)
{
	__asm volatile ("CPSIE i" ::: "memory");

}
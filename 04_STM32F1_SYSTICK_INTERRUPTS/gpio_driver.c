#include "gpio_driver.h"

inline void gpio_set_mode(struct gpio *gpio, uint16_t pin, uint8_t mode, uint8_t speed)
{
	
	if (pin <= 7){
		// first, clearing the bits
		gpio->CRL &= ~(15U << (pin * 4));

		// configuring the bits
		gpio->CRL |= (speed << (pin * 4));
		gpio->CRL |= (mode << ((pin * 4) + 2));
	} else if (pin > 7){
		// first, clearing the bits
		gpio->CRH &= ~(15U << ((pin%8) * 4));

		// configuring the bits
		gpio->CRH |= (speed << ((pin%8) * 4));
		gpio->CRH |= (mode << (((pin%8) * 4) + 2));
	}

}

/*
inline void delay(volatile uint32_t counter){
	while(counter--) asm("nop");
} */

void delaymilli(void)
{
    SYSTICK->LOAD = 8000;
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

void __disable_irq(void)
{
	__asm volatile ("CPSID i" ::: "memory");

}


void __enable_irq(void)
{
	__asm volatile ("CPSIE i" ::: "memory");

}
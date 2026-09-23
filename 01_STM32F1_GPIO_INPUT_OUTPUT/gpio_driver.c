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

inline void delay(volatile uint32_t counter){
	while(counter--) asm("nop");

}


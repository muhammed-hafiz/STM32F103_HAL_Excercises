#include "gpio_driver.h"


int main(void)
{	
	// enable port b and port c clocks
	RCC-> RCC_APB2ENR |= (3U << 3);	
	
	// set pins mode
	gpio_set_mode(GPIOC, 14, GPIO_OUTPUT_MODE_PUSHPULL, OUTPUT_2MHZ_SPEED);
	gpio_set_mode(GPIOB, 11, GPIO_INPUT_MODE_PULL_DOWN_OR_UP, INPUT_SPEED);
	gpio_set_mode(GPIOB, 5, GPIO_OUTPUT_MODE_PUSHPULL, OUTPUT_2MHZ_SPEED);

	for (;;)
	{
		if (!(GPIOB->IDR & (1U << 11))){
			delay(100000);
			GPIOC->ODR ^= (1U << 14);
			GPIOB->ODR |= (1U << 5);
			delay(100000);
		} else {
			GPIOC->ODR &= ~(1U << 14);
			GPIOB->BSRR |= (1U << 21);
		}
	}
	return 0;
}


// startup code
__attribute__((naked, noreturn)) void _reset(void)
{
	extern long _sbss, _ebss, _sdata, _edata, _sidata;
	for (long *dst = &_sbss; dst < &_ebss; dst++) *dst = 0;
	for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;) *dst++ = *src++;

	// calling main()
	main();

	for (;;)(void) 0; //infinite loop
}


// stack
extern void _estack(void); // Define link.ld
// stack inilization
// reset handler
// 16 standard and 91 stm32-specific handlers
__attribute__((section(".vectors"))) void (*const vector_table[16+91] )(void) = {
	 _estack, _reset
};
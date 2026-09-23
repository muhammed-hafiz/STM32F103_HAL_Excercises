#include <stdint.h>
#include "gpio_driver.h"


int main(void) {
    systick_init();
    // 1. Enable Clocks
    RCC->RCC_APB2ENR |= (1<<4) | (1<<3) | (1<<0);  // IOPC, IOPB, AFIO
    
    // 2. Configure PC13 (LED) as Push-Pull Output
	gpio_set_mode(GPIOC, 13, GPIO_OUTPUT_MODE_PUSHPULL, OUTPUT_10MHZ_SPEED);


    // 3. Configure PB11 as Input with Pull-Up
	gpio_set_mode(GPIOB, 11, GPIO_INPUT_MODE_PULL_DOWN_OR_UP, INPUT_SPEED);

    
    // 4. Configure EXTI11
    AFIO->EXTICR3 |= (1 << 12);       // PB11 for EXTI11
    EXTI->IMR  |= (1 << 11);         // Enable EXTI11
    EXTI->FTSR |= (1 << 11);         // Falling edge trigger
    
    // 5. Enable NVIC Interrupt
    NVIC_ISER->ISER1 |= (1 << (40 - 32));  // Enable IRQ40
    

    
    while(1) {
    delayms(1000);
    GPIOC->ODR |= (1 << 13);
    delayms(1000);
    GPIOC->ODR ^= (1 << 13);
	}
}


void EXTI15_10_Handler(void) {
    if (EXTI->PR & (1 << 11)) {
        GPIOC->ODR ^= (1 << 13);
        EXTI->PR = (1 << 11);  // Clear by writing 1
    }
}

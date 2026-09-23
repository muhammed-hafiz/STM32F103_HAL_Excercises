#include <stdint.h>
#include "gpio_driver.h"

// note: systick timer is a 3 byte register

char chat = 'c';

int main(void) {
    
    systick_init();

    // Enable the Alternate function for the pins
    RCC->RCC_APB2ENR |= (1 << 0);
    RCC->RCC_APB2ENR |= (1 << 2);

    // Enable UART2 peripheral
    RCC->RCC_APB1ENR |= 0x20000;

    // Enable the related pins, on datasheet, pin mapping section
        // for the AF only the tx has to be as AF, but the rx should be input
        // we gonna use USART2 (PA2 -> TX, PA3 -> RX)
    gpio_set_mode(GPIOA, 2, GPIO_AF_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);
    gpio_set_mode(GPIOA, 3, GPIO_INPUT_MODE_PULL_DOWN_OR_UP, INPUT_SPEED);


    // Setup Baudrate as 9600 bps
    USART2->BRR = 0x341;

    // | UE:UART enable | TE: Transmit enable | RE: Revieve enable

    // Enable UART Transmit 
    USART2->CR1 |= 8;

    // Enable UART Recieve 
    USART2->CR1 |= 4;
    
    // Enable UART
    USART2->CR1 |= 0x2000;

    while(1) {
        // Wait until a character is received
        while (!(USART2->SR & (1 << 5)));
        chat = USART2->DR;  // Read the received character immediately
        
        // Wait until ready to transmit
        while (!(USART2->SR & (1 << 7)));
        USART2->DR = chat;  // Send back the received character
    }

}


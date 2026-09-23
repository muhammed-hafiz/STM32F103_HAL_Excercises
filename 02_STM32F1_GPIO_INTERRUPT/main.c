#include <stdint.h>

// Register Definitions
#define RCC_APB2ENR   (*(volatile uint32_t*)0x40021018)
#define GPIOC_CRH     (*(volatile uint32_t*)0x40011004)
#define GPIOC_ODR     (*(volatile uint32_t*)0x4001100C)
#define GPIOB_CRH     (*(volatile uint32_t*)0x40010C04)
#define AFIO_EXTICR3  (*(volatile uint32_t*)0x40010010)
#define EXTI_IMR      (*(volatile uint32_t*)0x40010400)
#define EXTI_FTSR     (*(volatile uint32_t*)0x4001040C)
#define EXTI_PR       (*(volatile uint32_t*)0x40010414)
#define NVIC_ISER1    (*(volatile uint32_t*)0xE000E104)

void EXTI15_10_Handler(void) {
    if (EXTI_PR & (1 << 11)) {
        GPIOC_ODR ^= (1 << 13);
        EXTI_PR = (1 << 11);  // Clear by writing 1
    }
}

int main(void) {
    // 1. Enable Clocks
    RCC_APB2ENR |= (1<<4) | (1<<3) | (1<<0);  // IOPC, IOPB, AFIO
    
    // 2. Configure PC13 (LED) as Push-Pull Output
    GPIOC_CRH &= ~(0b1111 << 20);    // Clear bits
    GPIOC_CRH |=  (0b0001 << 20);    // Output mode, 10MHz
    
    // 3. Configure PB11 as Input with Pull-Up
    GPIOB_CRH &= ~(0b1111 << 12);    // Clear bits
    GPIOB_CRH |=  (0b1000 << 12);    // Input with pull-up/pull-down
    
    // 4. Configure EXTI11
    AFIO_EXTICR3 |= (1 << 12);       // PB11 for EXTI11
    EXTI_IMR  |= (1 << 11);         // Enable EXTI11
    EXTI_FTSR |= (1 << 11);         // Falling edge trigger
    
    // 5. Enable NVIC Interrupt
    NVIC_ISER1 |= (1 << (40 - 32));  // Enable IRQ40
    
    // Initial state: LED ON
    GPIOC_ODR |= (1 << 13);
    
    while(1);
}
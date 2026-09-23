    #include "timer_driver.h"
    #include "gpio_driver.h"

    int main(void) {

        // Enable clock for timer 1 and for gpio pin PA9
        RCC->RCC_APB2ENR |= (1 << 11 ) | (1 << 2);

            gpio_set_mode(GPIOA, 8, GPIO_AF_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);

        // Configuring Timer 1
        TIM1->PSC = 72 - 1;
        TIM1->CNT = 0;
        TIM1->ARR = 60000;

        // Configuring Capture/Compare as toggling only for channel 1
        TIM1->CCMR1 |= (3 << 4);

        // Enabling the Capture/Compare function for channel 1
        TIM1->CCER |= 1;

        // Set the break and dead time main output enable bit
        TIM1->BDTR |= 0x8000;

        // Setting the Capture/Compare value
        TIM1->CCR1 |= 30000;

        // Let CNT start counting from register CR1
        TIM1->CR1 |= 1;

        while(1) {
        
        }
    }
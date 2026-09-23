#include "timer_driver.h"
#include "gpio_driver.h"


/*
void TIM1_UP_IRQHandler(){}
void TIM2_IRQHandler(){}
void TIM3_IRQHandler(){}
void TIM4_IRQHandler(){}

*/



int main(void) {

    //timer_irq_millis_start(T,500);


    RCC->RCC_APB2ENR |= (1 << 4);
    gpio_set_mode(GPIOC, 13, GPIO_OUTPUT_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);
    //gpio_set_mode(GPIOC, 9, GPIO_OUTPUT_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);

    while(1) {
        //TDelay_Milli(1000);
        for (int i=0; i<1000; i++){
        TDelay_Micros(T1, 1000);}   

        GPIOC->ODR ^= (1 << 13);
    }
}

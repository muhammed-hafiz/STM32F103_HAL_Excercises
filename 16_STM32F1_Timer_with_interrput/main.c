    #include "timer_driver.h"
    #include "gpio_driver.h"

    /*
    void TIM2_IRQHandler()
    {

    }

    void TIM3_IRQHandler()
    {

    }

    void TIM4_IRQHandler()
    {

    }
    */
    volatile static int counter = 0;

    int main(void) {

        RCC->RCC_APB2ENR |= (1 << 4 );
        gpio_set_mode(GPIOC, 13, GPIO_OUTPUT_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);
        timer_irq_millis_start(T2, 200);

        //timer_irq_stop(T2);
        //TDelay_Millis(T1, 15000);

        while(1) {
        GPIOC->ODR ^= (1 << 13);
        TDelay_Millis(T1, 10000);
        if (counter >= 10)
        {
            timer_irq_stop(T2);
            } 
        }
        
    }


void TIM2_IRQHandler()
    {
        timer_irq_Rflag(T2);
        GPIOC->ODR ^= (1 << 13); 
        counter++;
    
    }



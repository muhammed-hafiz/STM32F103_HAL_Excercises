#include "adc_driver.h"

/*
PA0 -> ADC12_IN0
PA1 -> ADC12_IN1
PA2 -> ADC12_IN2
PA3 -> ADC12_IN3
PA4 -> ADC12_IN4
PA5 -> ADC12_IN5
PA6 -> ADC12_IN6
PA7 -> ADC12_IN7
PB0 -> ADC12_IN8
PB1 -> ADC12_IN9


PC0 -> ADC12_IN10
PC1 -> ADC12_IN11
PC2 -> ADC12_IN12
PC3 -> ADC12_IN13
PC4 -> ADC12_IN14
PC5 -> ADC12_IN15


ADC12_IN16 input channel which is used to convert the sensor output voltage into digital value.

*/

// Initializing the ADC for the STM32F1
char adc_init(char adc, struct gpio *port, short pin)
{
    char channel;
    char result = 0;
    if (port == GPIOA)
    {
        if (pin < 8){
            result = 1;
            channel = pin;
        }
    } else if (port == GPIOB){
        if (pin < 2) {
            result = 1;
            channel = 8 + pin;
        }
    } else if (port == GPIOC){
        if (pin < 6){
            result = 1;
            channel = 10 + pin;
        }
    }

    if (result){
        gpio_set_mode(port, pin, GPIO_INPUT_MODE_ANALOG, INPUT_SPEED);
        if (adc == adc1){
            // Enabling AFIO and ADC1 from APB2 
            RCC->RCC_APB2ENR |= (1 << 0) | (1 << 9);

            // Setting up the ADC_CR1 register 
            ADC1->CR2 = 0;

            // Which channel I would like to scan
            ADC1->SQR3 = channel;

            // Turning peripheral on 
            ADC1->CR2 |= 1;

            delayms(100);

            ADC1->CR2 |= 1;
            // setting the peripheral to have continuous conversion
            ADC1->CR2 |= 2;

        } else if (adc == adc2){
            // Enabling AFIO and ADC1 from APB2 
            RCC->RCC_APB2ENR |= (1 << 0) | (1 << 10);

            // Setting up the ADC_CR1 register 
            ADC2->CR2 = 0;

            // Which channel I would like to scan
            ADC2->SQR3 = channel;

            // Turning peripheral on 
            ADC2->CR2 |= 1;

            delayms(100);

            ADC2->CR2 |= 1;
            // setting the peripheral to have continuous conversion
            ADC2->CR2 |= 2;
        }
    }
    return result;
}

// Reading the flag that says the data is ready, the bit is EOC in ADC->SR 
char adc_check(char adc,  struct gpio *port, short pin)
{
    char check = 0;
    if (adc == adc1){
        if (ADC1->SR & 2){

            check = 1;
        }


    } else if (adc == adc2){
        if (ADC2->SR & 2){
            check = 1;
        }
    }

    return check;

}

// Reading the ADC value
int adc_rx(char adc, struct gpio *port, short pin)
{
    int result = 0;
    int data = 0;
    if (adc == adc1){
        data = ADC1->DR;

    } else if (adc == adc2){
        data = ADC2->DR;
    }

    result = (data*1000)/0xFFF;

    return result;
}
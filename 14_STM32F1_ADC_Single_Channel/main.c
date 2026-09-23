#include "adc_driver.h"
#include "usart_driver.h"
#include "help_func.h"
char num[10];
int analog_rx = 0;

int main(void) {
    // Initialize UART2
    USART_init(1, 115200);

    UART_SEND(1, "i");
    // Initialize the ADC
    adc_init(adc1, GPIOA, 0);
    
    while(1) {
        UART_SEND(1, "Loop Started.");
        if (adc_check(adc1,  GPIOA, 0)){
            //analog_rx = adc_rx(adc1, GPIOA, 0);
            //int2char(analog_rx, num);
            UART_SEND(1, "Got Result.");
            UART_TX(1, '\n');

        }
        UART_SEND(1, "Didn't get Result.");
    }
}

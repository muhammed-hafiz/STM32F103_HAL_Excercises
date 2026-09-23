#include <stdint.h>
#include "stm32f10x.h"
#include "gpio_driver.h"
#include "systick_driver.h"
#include "usart_driver.h"


char chat;

int main(void) {
    
    systick_init();
    USART_init(1, 115200);

    while(1) {

        chat = UART_RX(1);
        UART_TX(1, chat);

    }
}


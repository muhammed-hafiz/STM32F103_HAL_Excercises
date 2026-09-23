#include <stdint.h>
#include "stm32f10x.h"
#include "gpio_driver.h"
#include "systick_driver.h"
#include "usart_driver.h"   

char USART_1_msg[250];
unsigned short USART_1_cnt = 0;
unsigned short USART_1_sig = 0;
unsigned short USART_1_bdg = 0;

char USART_2_msg[250];
unsigned short USART_2_cnt = 0;
unsigned short USART_2_sig = 0;
unsigned short USART_2_bdg = 0;

char USART_3_msg[250];
unsigned short USART_3_cnt = 0;
unsigned short USART_3_sig = 0;
unsigned short USART_3_bdg = 0;

char msg2[] = "This is UART 2";
char msg3[] = " This is UART 3";

int main(void) {
    
    systick_init(); 
    USART_init(2, 9600);
    USART_init(3, 9600);

    // the registers need a little bit of time to be ready to send data
    delayms(100);

    UART_SEND(2, msg2);
    UART_SEND(3, msg3);
    while(1) {

        if (USART_2_sig == 1){
            UART_SEND(3, USART_2_msg);
            USART_2_sig = 0;
            str_empty(USART_2_msg);
        }
        if (USART_3_sig == 1){
            UART_SEND(2, USART_3_msg);
            USART_3_sig = 0;
            str_empty(USART_3_msg);
        }

    }
}


void USART2_IRQHandler()
{
    UART_ISR(2, 0, &USART_2_sig, &USART_2_cnt, USART_2_msg);
}

void USART3_IRQHandler()
{
    UART_ISR(3, 0, &USART_3_sig, &USART_3_cnt, USART_3_msg);
}
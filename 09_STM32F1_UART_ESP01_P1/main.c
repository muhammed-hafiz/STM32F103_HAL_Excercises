#include <stdint.h>
#include "stm32f10x.h"
#include "gpio_driver.h"
#include "systick_driver.h"
#include "usart_driver.h"   

/*
1- Introduction to esp8266 
2- Creating Setup library/menu
3- Creating wifi communication library
*/

/* 
UART MANAGER
0- count
1- signal
2- bridge
3- terminator 1 / interrupt 0
4- terminator char
5- time constant
6- time counter
*/

unsigned short uart_1_mgr[7] = {0,0,0,0,0,0,0};
unsigned short uart_2_mgr[7] = {0,0,0,0,0,200,0};
unsigned short uart_3_mgr[7] = {0,0,0,0,0,200,0};

char USART_1_msg[300];
unsigned short USART_1_cnt = 0;
unsigned short USART_1_sig = 0;
unsigned short USART_1_bdg = 0;

char USART_2_msg[300];
unsigned short USART_2_cnt = 0;
unsigned short USART_2_sig = 0;
unsigned short USART_2_bdg = 0;

char USART_3_msg[300];
unsigned short USART_3_cnt = 0;
unsigned short USART_3_sig = 0;
unsigned short USART_3_bdg = 0;

char msg[30] = "Welcome to the WeeW";




int main(void) {
    
    systick_init(); 
    USART_init(2, 115200);
    USART_init(3, 115200);

    // the registers need a little bit of time to be ready to send data
    delayms(100);

    UART_SEND(2, msg);

    while(1) {
        if (uart_2_mgr[1]){
            UART_SEND(3, USART_2_msg);
            uart_2_mgr[1] = 0;
            str_empty(USART_2_msg);
        }
        if (uart_3_mgr[1]){
            UART_SEND(2, USART_3_msg);
            uart_3_mgr[1] = 0;
            str_empty(USART_3_msg);
        }
    }
}


void USART2_IRQHandler()
{
    UART_ISR(2, uart_2_mgr, USART_2_msg);
}

void USART3_IRQHandler()
{
    UART_ISR(3, uart_3_mgr, USART_3_msg);
}

void SysTick_Handler()
{
    systick_int(uart_1_mgr, uart_2_mgr, uart_3_mgr);
}
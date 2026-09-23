#ifndef USART_DRIVER_H
#define USART_DRIVER_H

#include "stm32f10x.h"
#include "gpio_driver.h"
#include "systick_driver.h"


unsigned long CALC_USART_BR(unsigned short usart, unsigned long BR);
void USART_init(unsigned short usart, unsigned long BR);
char UART_RX(unsigned short uart);
void UART_TX(unsigned short uart, char c);

void UART_SEND(unsigned short uart, char str[]);

void UART_ISR(unsigned short uart, unsigned short uart_mgr[], char str[]);

void str_empty(char str[]);

void UART_msg_wait(unsigned short uart, char str[], unsigned short str_mgr[]);

#endif
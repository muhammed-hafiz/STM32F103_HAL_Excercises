#include "usart_driver.h"


unsigned long SystemCoreClock = 72000000UL;

/* 32-bit only, no libgcc helpers needed -------------------------- */
static uint16_t build_brr(uint32_t pclk_hz, uint32_t baud)
{
    uint32_t baud_x16 = baud << 4;               /* 16 × baud          */
    uint32_t mantissa = pclk_hz / baud_x16;      /* integer part       */
    uint32_t rem      = pclk_hz - mantissa * baud_x16;

    /* fractional part, rounded:  nearest = (rem * 16 + half) / denom */
    uint32_t fraction = (rem * 16U + baud_x16 / 2U) / baud_x16;

    if (fraction == 16U) {                       /* carry overflow     */
        mantissa++;
        fraction = 0U;
    }
    return (mantissa << 4) | (fraction & 0xF);
}

uint32_t CALC_USART_BR(uint16_t usart, uint32_t baud)
{
    /* pick the correct peripheral clock */
    uint32_t pclk = (usart == 1)
                  ? SystemCoreClock        /* APB2: 72 MHz */
                  : SystemCoreClock / 2U;  /* APB1: 36 MHz */

    return build_brr(pclk, baud);
}


void USART_init(unsigned short usart, unsigned long BR)
{
    unsigned long brr = CALC_USART_BR(usart, BR);
    //unsigned long brr = 0x1D4C;
    RCC->RCC_APB2ENR |= (1 << 0);
     if (usart == 1) {
      
        RCC->RCC_APB2ENR |= (1 << 2);    // GPIOA clock
        RCC->RCC_APB2ENR |= (1 << 14);   // USART1 clock

        AFIO->MAPR &= ~(1 << 2);         // Disable USART1 remap (PA9/PA10)

        gpio_set_mode(GPIOA, 9, GPIO_AF_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);   // TX = PA9
        gpio_set_mode(GPIOA, 10, GPIO_INPUT_MODE_PULL_DOWN_OR_UP, INPUT_SPEED);
        GPIOA->ODR |= (1 << 10);   // select pull-up
        // RX = PA10

        USART1->BRR = brr;
        USART1->CR1 |= (1 << 13) | (1 << 3) | (1 << 2);  // UE | TE | RE
        (void)USART1->SR;    /* dummy read */
        (void)USART1->DR;    /* clears RXNE  */
    }

    else if (usart == 2) {
        RCC->RCC_APB2ENR |= (1 << 2);     // GPIOA clock
        RCC->RCC_APB1ENR |= (1 << 17);    // USART2 clock

        gpio_set_mode(GPIOA, 2, GPIO_AF_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);
        gpio_set_mode(GPIOA, 3, GPIO_INPUT_MODE_INPUTFLOATING, INPUT_SPEED);

        USART2->BRR = brr;
        USART2->CR1 |= (1 << 13) | (1 << 3) | (1 << 2);
    }
    else if (usart == 3) {
        RCC->RCC_APB2ENR |= (1 << 3);     // GPIOB clock
        RCC->RCC_APB1ENR |= (1 << 18);    // USART3 clock

        gpio_set_mode(GPIOB, 10, GPIO_AF_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);
        gpio_set_mode(GPIOB, 11, GPIO_INPUT_MODE_INPUTFLOATING, INPUT_SPEED);

        USART3->BRR = brr;
        USART3->CR1 |= (1 << 13) | (1 << 3) | (1 << 2);
    }
}


char UART_RX(unsigned short uart)
{
    char c = '\0';
    if (uart == 1){
        while(!(USART1->SR & (1 << 5)));
        c = USART1->DR;

    } else if (uart == 2){
        while(!(USART2->SR & (1 << 5)));
        c = USART2->DR;
    } else if (uart == 3){
        while(!(USART3->SR & (1 << 5)));
        c = USART3->DR;
    }

    return c;
}

void UART_TX(unsigned short uart, char c)
{
 
    if (uart == 1){
        while(!(USART1->SR & (1 << 7)));
        USART1->DR = c;

    } else if (uart == 2){
        while(!(USART2->SR & (1 << 7)));
        USART2->DR = c;
    } else if (uart == 3){
        while(!(USART3->SR & (1 << 7)));
        USART3->DR = c;
    }
}


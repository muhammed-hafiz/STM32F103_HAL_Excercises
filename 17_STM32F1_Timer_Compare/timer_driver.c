#include "timer_driver.h"

struct timer * get_timer(char timer)
{
    struct timer *tim = 0;
    switch(timer)
    {
        case 1: tim = TIM1;break;
        case 2: tim = TIM2;break;
        case 3: tim = TIM3;break;
        case 4: tim = TIM4;break;
    }
    return tim;
}

struct timer *start_timer_micros(char timer, int microS)
{
    int prescaler = 72 - 1;
    struct timer *tim = 0;

    if (timer == 1){
        RCC->RCC_APB2ENR |= 0x0800;
    }
    else {
        RCC->RCC_APB1ENR |= 1 << (timer-2);
    }

    tim = get_timer(timer);

    // Setup the counter to 0
    tim->CNT = 0;

    // Setup the prescaler to 72 -> 1 div equal to 1 Micro Sec
    tim->PSC = prescaler;

    // Initilaize the auto reload register value
    tim->ARR = (microS - 3);

    // Enable the counter
    tim->CR1 |= 0x1;    

    return tim;
}

struct timer *start_timer_millis(char timer, int milliS)
{
    int prescaler = 32000 - 1;
    struct timer *tim;

    if (timer == 1){
        RCC->RCC_APB2ENR |= 0x0800;
    }
    else {
        RCC->RCC_APB1ENR |= 1 << (timer-2);
    }

    tim = get_timer(timer);

    // Setup the counter to 0
    tim->CNT = 0;

    // Setup the prescaler to 72 -> 1 div equal to 1 Micro Sec
    tim->PSC = prescaler;

    // Initilaize the auto reload register value
    tim->ARR = milliS*2;

    // Enable the counter
    tim->CR1 |= 0x1;    

    return tim;
}

int get_time_micros(char timer)
{
    struct timer *tim = get_timer(timer);
    return tim->CNT;
}


// assuming the counter is in millis
int get_time_millis(char timer)
{
    struct timer *tim = get_timer(timer);
    return tim->CNT;
}

void TDelay_Micros(char timer, int microS)
{
    struct timer *tim = start_timer_micros(timer, microS);

    // Enable the counter
    tim->CR1 |= 0x9;

    while(tim->CR1 & 1);
}

void TDelay_Millis(char timer, int milliS)
{
    struct timer *tim = start_timer_millis(timer, milliS);

    // Enable the counter
    tim->CR1 |= 0x9;

    while(tim->CR1 & 1);
}

void TDelay_Micro(int microS)
{
    TDelay_Micros(T4, microS);
}

void TDelay_Milli(int milliS)
{
    TDelay_Millis(T4, milliS);
}

void timer_irq_micro_start(char timer, int microS)
{
    struct timer *tim = start_timer_micros(timer, microS);
    tim->DIER |= 1;
    
    __disable_irq();

    switch(timer)
    {
    case 1: NVIC_ISER->ISER0 |= (1 << 25) ;break;
    case 2: NVIC_ISER->ISER0 |= (1 << 28) ;break;
    case 3: NVIC_ISER->ISER0 |= (1 << 29) ;break;
    case 4: NVIC_ISER->ISER0 |= (1 << 30) ;break;
    }

    __enable_irq();
}

void timer_irq_millis_start(char timer, int milliS)
{
    struct timer *tim = start_timer_millis(timer, milliS);
    tim->DIER |= 1;
    
    __disable_irq();

    switch(timer)
    {
    case 1: NVIC_ISER->ISER0 |= (1 << 25) ;break;
    case 2: NVIC_ISER->ISER0 |= (1 << 28) ;break;
    case 3: NVIC_ISER->ISER0 |= (1 << 29) ;break;
    case 4: NVIC_ISER->ISER0 |= (1 << 30) ;break;
    }

    __enable_irq();
}

void timer_irq_Rflag(char timer)
{
    struct timer *tim = get_timer(timer);
    tim->SR &= 0xFFFE;
}

void timer_irq_stop(char timer)
{
    struct timer *tim = get_timer(timer);
    tim->DIER &= 0xFFFE;

    __disable_irq();

    switch(timer)
    {
    case 1: NVIC_ICER->ICER0 |= (1 << 25) ;break;
    case 2: NVIC_ICER->ICER0 |= (1 << 28) ;break;
    case 3: NVIC_ICER->ICER0 |= (1 << 29) ;break;
    case 4: NVIC_ICER->ICER0 |= (1 << 30) ;break;
    }

    __enable_irq();
}

void timer_stop(char timer)
{
    struct timer *tim = get_timer(timer);
    tim->CR1 = 0;

    if (timer == 1){
        RCC->RCC_APB2ENR &= ~(0x0800);
    }
    else {
        RCC->RCC_APB1ENR &= ~(1 << (timer-2));
    }


    timer_irq_stop(timer);
}
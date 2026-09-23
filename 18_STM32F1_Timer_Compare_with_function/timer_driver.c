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


/*

PA8  - TIM1 - CHANNEL 1
PA9  - TIM1 - CHANNEL 2
PA10 - TIM1 - CHANNEL 3
PA11 - TIM1 - CHANNEL 4

PA0  - TIM2 - CHANNEL 1
PA1  - TIM2 - CHANNEL 2
PA2  - TIM2 - CHANNEL 3
PA3  - TIM2 - CHANNEL 4

PA6  - TIM3 - CHANNEL 1 
PA7  - TIM3 - CHANNEL 2
PB0  - TIM3 - CHANNEL 3
PB1  - TIM3 - CHANNEL 4

PB6  - TIM4 - CHANNEL 1
PB7  - TIM4 - CHANNEL 2
PB8  - TIM4 - CHANNEL 3
PB9  - TIM4 - CHANNEL 4
    

*/

int extract_timer_pin(char timer, char channel)
{   
    if (timer == 1){
        switch(channel){
        case 1: return 8; break;
        case 2: return 9; break;
        case 3: return 10; break;
        case 4: return 11; break;
        }
    }

    else if (timer == 2){
        switch(channel){
        case 1: return 0; break;
        case 2: return 1; break;
        case 3: return 2; break;
        case 4: return 3; break;
        }
    }

    else if (timer == 3){
        switch(channel){
        case 1: return 6; break;
        case 2: return 7; break;
        case 3: return 0; break;
        case 4: return 1; break;
        }
    }

    else if (timer == 4){
        switch(channel){
        case 1: return 6; break;
        case 2: return 7; break;
        case 3: return 8; break;
        case 4: return 9; break;
        }
    }
    return 0;

}

struct gpio *extract_timer_port(char timer, char channel)
{

    if (timer == 1 || timer == 2){
        return GPIOA;
    }


    else if (timer == 3){
        switch(channel){
        case 1: return GPIOA; break;
        case 2: return GPIOA; break;
        case 3: return GPIOB; break;
        case 4: return GPIOB; break;
        }
    }

    else if (timer == 4){
        return GPIOB;
    }
    return 0;

}

void timer_compare_micro(char timer, char channel, int arr, int compare)
{
    struct gpio *port = extract_timer_port(timer, channel);
    int pin = extract_timer_pin(timer, channel);
    struct timer *tim = get_timer(timer);

    // enabling the clock for selected timer 
    if (timer == 1){
        RCC->RCC_APB2ENR |= (1 << 11);

    } else {
        RCC->RCC_APB1ENR |= (1 << (timer - 2));        
    }

    // setting the pin
    gpio_set_mode(port, pin, GPIO_AF_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);

    // Configuring Timer 
    tim->PSC = 72 - 1;
    tim->CNT = 0;
    tim->ARR = arr-1;


    // Configuring Capture/Compare as toggling only for channel 
    switch (timer){
        case 1: tim->CCMR1 |= 0x30; break;
        case 2: tim->CCMR1 |= 0x3000; break;
        case 3: tim->CCMR2 |= 0x30; break;
        case 4: tim->CCMR2 |= 0x3000; break;
    }

   


    // Enabling the Capture/Compare function for channel 1
    tim->CCER |= 1;

    // Set the break and dead time main output enable bit
    tim->BDTR |= 0x8000;

    // Setting the Capture/Compare value
    tim->CCR1 |= compare;

    // Let CNT start counting from register CR1
    tim->CR1 |= 1;    


}

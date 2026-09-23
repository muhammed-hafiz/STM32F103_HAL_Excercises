#include <stdint.h>


// Enabling GPIO Peripheral
struct rcc {
	volatile uint32_t RCC_CR, RCC_CFGR, RCC_CIR, RCC_APB2RSTR, RCC_APB1RSTR, RCC_AHBENR, 
	RCC_APB2ENR, RCC_APB1ENR, RCC_BDCR, RCC_CSR;
};


// structure for GPIO peripheral
struct gpio
{
	volatile uint32_t CRL, CRH, IDR, ODR, BSRR, BRR, LCKR;
};

#define GPIOA ((struct gpio *) (0x40010800 + 0x00))
#define GPIOB ((struct gpio *) (0x40010800 + 0x400))
#define GPIOC ((struct gpio *) (0x40010800 + 0x800))
#define RCC ((struct rcc*) (0x40021000))


enum {GPIO_OUTPUT_MODE_PUSHPULL, GPIO_OUTPUT_MODE_OPENDRAIN, GPIO_AF_MODE_PUSHPULL,
GPIO_AF_MODE_OPENDRAIN};

enum {GPIO_INPUT_MODE_ANALOG, GPIO_INPUT_MODE_INPUTFLOATING,   
GPIO_INPUT_MODE_PULL_DOWN_OR_UP};

enum {INPUT_SPEED, OUTPUT_10MHZ_SPEED, OUTPUT_2MHZ_SPEED, OUTPUT_50MHZ_SPEED};

void gpio_set_mode(struct gpio *gpio, uint16_t pin, uint8_t mode, uint8_t speed);
void delay(volatile uint32_t counter);


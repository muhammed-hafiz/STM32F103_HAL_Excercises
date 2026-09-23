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


// structure for EXTI
struct exti 
{
	volatile uint32_t IMR, EMR,RTSR, FTSR, SWIER, PR;
};

// structure for AFIO
struct afio 
{
	volatile uint32_t EVCR, MAPR, EXTICR1, EXTICR2, EXTICR3, EXTICR4, MAPR2;
};

// structure for nvic_iser
struct nvic_iser 
{
	volatile uint32_t ISER0, ISER1, ISER2;
};

// structure for nvic_icer
struct nvic_icer 
{
	volatile uint32_t ICER0, ICER1, ICER2;
};

// structure for nvic_ispr
struct nvic_ispr 
{
	volatile uint32_t ISPR0, ISPR1, ISPR2;
};

// structure for nvic_icpr
struct nvic_icpr 
{
	volatile uint32_t ICPR0, ICPR1, ICPR2;
};

// structure for nvic_iabr
struct nvic_iabr 
{
	volatile uint32_t IABR0, IABR1, IABR2;
};

// note: the ipr0 ~ ipr20 have not been implemented yet

// structure for systick
struct systick
{
    volatile uint32_t CTRL, LOAD, VAL, CALIB;
};


#define GPIOA ((struct gpio *) (0x40010800 + 0x00))
#define GPIOB ((struct gpio *) (0x40010800 + 0x400))
#define GPIOC ((struct gpio *) (0x40010800 + 0x800))
#define RCC   ((struct rcc *) (0x40021000))
#define EXTI  ((struct exti *) 0x40010400)
#define AFIO  ((struct afio *) 0x40010000)

#define NVIC_ISER ((struct nvic_iser *) (0xE000E100 + 0x00))
#define NVIC_ICER ((struct nvic_icer *) (0xE000E100 + 0x80))
#define NVIC_ISPR ((struct nvic_ispr *) (0xE000E100 + 0x100))
#define NVIC_ICPR ((struct nvic_icpr *) (0xE000E100 + 0x180))
#define NVIC_IABR ((struct nvic_iabr *) (0xE000E100 + 0x200))
#define NVIC_STIR ((volatile uint8_t *) (0xE000E100 + 0xE00))

#define SYSTICK ((struct systick *)0xE000E010)



enum {GPIO_OUTPUT_MODE_PUSHPULL, GPIO_OUTPUT_MODE_OPENDRAIN, GPIO_AF_MODE_PUSHPULL,
GPIO_AF_MODE_OPENDRAIN};

enum {GPIO_INPUT_MODE_ANALOG, GPIO_INPUT_MODE_INPUTFLOATING,   
GPIO_INPUT_MODE_PULL_DOWN_OR_UP};

enum {INPUT_SPEED, OUTPUT_10MHZ_SPEED, OUTPUT_2MHZ_SPEED, OUTPUT_50MHZ_SPEED};

void gpio_set_mode(struct gpio *gpio, uint16_t pin, uint8_t mode, uint8_t speed);
//void delay(volatile uint32_t counter);
void systick_init(void);
void delayms(unsigned long t);
void delaymilli(void);
void __disable_irq(void);
void __enable_irq(void);


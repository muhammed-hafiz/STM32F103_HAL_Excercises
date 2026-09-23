#ifndef STM32F10X_H
#define STM32F10X_H


#include <stdint.h>


// structure for clock control regiser
struct rcc {
	volatile uint32_t RCC_CR, RCC_CFGR, RCC_CIR, RCC_APB2RSTR, RCC_APB1RSTR, RCC_AHBENR, 
	RCC_APB2ENR, RCC_APB1ENR, RCC_BDCR, RCC_CSR, RCC_AHBRSTR, RCC_CFGR2;
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

// struct for USART
struct usart 
{
	volatile uint32_t SR, DR, BRR, CR1, CR2, CR3, GTPR;	
};


// struct for SPI
struct spi 
{
	volatile uint32_t CR1, CR2, SR, DR, CRCPR, RXCRCR, STXCRCR, I2SCFGR, I2SPR;	
};


// struct for I2C
struct i2c 
{
	volatile uint32_t CR1, CR2, OAR1, OAR2, DR, SR1, SR2, CCR, TRISE;	
};

// struct for flash memory interface registers
struct flash
{
	volatile uint32_t ACR, KEYR, OPTKEYR, SR, CR, AR, RESERVED, OBR, WRPR;
};

// struct for ADC
struct adc
{
	volatile uint32_t SR, CR1, CR2, SMPR1, SMPR2, JOFRx, HTR, LTR, SQR1, SQR2, SQR3, JSQR, JDRx, DR;
};

// struct for Timer
struct timer 
{
	volatile uint32_t CR1, CR2, SMCR, DIER, SR, EGR, CCMR1, CCMR2, CCER, CNT, PSC, ARR, RCR, CCR1, CCR2, CCR3, CCR4, BDTR, DCR, DMAR;
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

#define SYSTICK ((struct systick *) 0xE000E010)

#define USART1 ((struct usart *) 0x40013800)
#define USART2 ((struct usart *) 0x40004400)
#define USART3 ((struct usart *) 0x40004800)

#define SPI1 ((struct spi *) 0x40013000)
#define SPI2 ((struct spi *) 0x40003800)
#define SPI3 ((struct spi *) 0x40003C00)

#define I2C1 ((struct i2c *) 0x40005400)
#define I2C2 ((struct i2c *) 0x40005800)

#define ADC1 ((struct adc *) 0x40012400)
#define ADC2 ((struct adc *) 0x40012800)

#define TIM1 ((struct timer *) 0x40012C00)
#define TIM2 ((struct timer *) 0x40000000)
#define TIM3 ((struct timer *) 0x40000400)
#define TIM4 ((struct timer *) 0x40000800)

#define FLASH ((struct flash *) 0x40022000)


void clock_init(void);
void __disable_irq(void);
void __enable_irq(void);

#endif 
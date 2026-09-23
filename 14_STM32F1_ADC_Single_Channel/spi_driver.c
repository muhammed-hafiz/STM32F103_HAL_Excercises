#include "spi_driver.h"


void spi_init(unsigned short spi)
{
    /*
    SPI 1
    PA4 --> SS
    PA5 --> SCLK
    PA6 --> MISO
    PA7 --> MOSI

    note that you can use 8bit or 16bit frame format, for default 16 bit
    i will use spi-2 to be 16 bit
	*/
	if (spi == 1){
    // Activat SPI-1 & AFIO & port A
    RCC->RCC_APB2ENR |= (1 << 12) | (1 << 0) | (1 << 2);

    // Set the pins 
    gpio_set_mode(GPIOA, 4, GPIO_OUTPUT_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);
    gpio_set_mode(GPIOA, 5, GPIO_AF_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);
    gpio_set_mode(GPIOA, 6, GPIO_INPUT_MODE_PULL_DOWN_OR_UP, INPUT_SPEED);
    gpio_set_mode(GPIOA, 7, GPIO_AF_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);

    // from control reg we need to set the baudrate and configure the mcu also as master
    SPI1->CR1 |= (1 << 2) | (7 << 3);

    // ss enable output
    SPI1->CR2 |= (1 << 2);

    // after finishing we set the spi enable bit 6
    SPI1->CR1 |= (1 << 6);

    // drive chip select high
    GPIOA->ODR |= (1 << 4);
    
	} else if (spi == 2){
    /*SPI 2
    PB12 --> SS
    PB13 --> SCLK
    PB14 --> MISO
    PB15 --> MOSI
    */
	// Activat SPI-2
    RCC->RCC_APB1ENR |= (1 << 14);

 	// Enable port B & AFIO
    RCC->RCC_APB2ENR |= (1 << 0) | (1 << 3);

     
    // Set the pins 
    gpio_set_mode(GPIOB, 12, GPIO_OUTPUT_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);
    gpio_set_mode(GPIOB, 13, GPIO_AF_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);
    gpio_set_mode(GPIOB, 14, GPIO_INPUT_MODE_PULL_DOWN_OR_UP, INPUT_SPEED);
    gpio_set_mode(GPIOB, 15, GPIO_AF_MODE_PUSHPULL, OUTPUT_50MHZ_SPEED);


    // from control reg we need to set the baudrate and configure the mcu also as master
    SPI2->CR1 |= (1 << 2);

    SPI2->CR1 &= ~(7 << 3);

    SPI2->CR1 |= (7 << 3);


    // ss enable output
    SPI2->CR2 |= (1 << 2);

    // configure frame as 16 bits
    SPI2->CR1 |= (1 << 11);

    // after finishing we set the spi enable bit 6
    SPI2->CR1 |= (1 << 6);

    // drive chip select high
    GPIOB->ODR |= (1 << 12);
	}
}

void spi_tx(unsigned short spi, char tx_char)
{
    if (spi == 1){
    GPIOA->ODR &= ~(1 << 4);
    while(!(SPI1->SR & (1 << 1))); 
    SPI1->DR = tx_char;
    while(!(SPI1->SR & (1 << 7)));  
    GPIOA->ODR |= (1 << 4);    

    } else if (spi == 2) {

    GPIOB->ODR &= ~(1 << 12);
    while(!(SPI2->SR & (1 << 1)));  
    SPI2->DR = tx_char;
    while(!(SPI2->SR & (1 << 7)));  
    GPIOB->ODR |= (1 << 12);
    }
}

void spi_msg(unsigned short spi, char str[])
{
    int i = 0;
    if (spi == 1){
        GPIOA->ODR &= ~(1 << 4);
        while (str[i] != '\0'){
            SPI1->DR = str[i];
            while(SPI1->SR & (1 << 7));
            i++;
        }
        GPIOA->ODR |= (1 << 4);

    } else if (spi == 2){

        GPIOB->ODR &= ~(1 << 12);

        while (str[i] != '\0'){
            SPI2->DR = str[i];
            while(SPI2->SR & (1 << 7));
            i++;
        }
        GPIOB->ODR |= (1 << 12);
    }
}

uint16_t spi_rx(unsigned short spi)
{
    uint16_t data = 0;
    
    if (spi == 1){

    GPIOA->ODR &= ~(1 << 4);

    // Wait for TX buffer empty
    while(!(SPI1->SR & (1 << 1)));

    // Send dummy data to trigger clock
    SPI1->DR = 0x00;

    // Wait for RX buffer full
    while (!(SPI2->SR & (1 << 0)));

    // read the 8-bit result
    data = SPI1->DR;

    // CS HIGH: end communication
    GPIOA->ODR |= (1 << 4);    

    } else if (spi == 2) {
        // CS LOW: start communication
        GPIOB->ODR &= ~(1 << 12);

        // Wait for TX buffer empty
        while (!(SPI2->SR & (1 << 1)));

        // Send dummy data to trigger clock
        SPI2->DR = 0x0000;

        // Wait for RX buffer full
        while (!(SPI2->SR & (1 << 0)));

        // Read the 16-bit result
        data = SPI2->DR;

        // CS HIGH: end communication
        GPIOB->ODR |= (1 << 12);
    }

    return data;
}
#include "i2c_driver.h"


// find the peripheral 

// activate the pins

// setup and activate the I2C


void i2c_init(char i2c, unsigned short speed_mode)
{
    RCC->RCC_APB2ENR |= (1 << 0);

    if (i2c == 1) {
        // ENABLE clock for i2c-1 
        RCC->RCC_APB1ENR |= (1 << 21); 
        // enable pins
        gpio_set_mode(GPIOB, 6, GPIO_AF_MODE_OPENDRAIN, OUTPUT_50MHZ_SPEED);
        gpio_set_mode(GPIOB, 7, GPIO_AF_MODE_OPENDRAIN, OUTPUT_50MHZ_SPEED);

        // SETUP THE I2C peripheral itself
        // 1st we need to reset the peripheral
        I2C1->CR1 |= (1 << 15);
        I2C1->CR1 &= ~(1 << 15);

        //inform peripheral about frequency of the APB (i.e. 8MHz)
        I2C1->CR2 |= (1 << 3);

        I2C1->CCR = speed_mode; // standard or fast
        I2C1->TRISE = 0x9; // if the freq is set to 8Mhz

        // enable the peripheral (PE bit)
        I2C1->CR1 |= (1 << 0);

    } else if (i2c == 2) {
        // ENABLE clock for i2c-2
        RCC->RCC_APB1ENR |= (1 << 22); 
        // enable pins
        gpio_set_mode(GPIOB, 10, GPIO_AF_MODE_OPENDRAIN, OUTPUT_50MHZ_SPEED);
        gpio_set_mode(GPIOB, 11, GPIO_AF_MODE_OPENDRAIN, OUTPUT_50MHZ_SPEED);

        // SETUP THE I2C peripheral itself
        // 1st we need to reset the peripheral
        I2C2->CR1 |= (1 << 15);
        I2C2->CR1 &= ~(1 << 15);

        //inform peripheral about frequency of the APB (i.e. 8MHz)
        I2C2->CR2 |= (1 << 3);

        I2C2->CCR = speed_mode; // standard or fast
        I2C2->TRISE = 0x9; // if the freq is set to 8Mhz

        // enable the peripheral (PE bit)
        I2C2->CR1 |= (1 << 0);

    }


}

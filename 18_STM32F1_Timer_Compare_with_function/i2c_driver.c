#include "i2c_driver.h"


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
        I2C1->CR2 = 8;

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
        I2C2->CR2 = 8;

        I2C2->CCR = speed_mode; // standard or fast
        I2C2->TRISE = 0x9; // if the freq is set to 8Mhz

        // enable the peripheral (PE bit)
        I2C2->CR1 |= (1 << 0);

    }
}

// Start step
void i2c_start(char i2c)
{
    if (i2c == 1){
        I2C1->CR1 |= (1 << 8); // SETING THE start bit
        while (!(I2C1->SR1 & 1)); // wait till this bit equals to zera

    } else if (i2c == 2){
        I2C2->CR1 |= (1 << 8); // SETING THE start bit
        while (!(I2C2->SR1 & 1)); // wait till this bit equals to zera
    }
}
// Sending the address + R/W bit
void i2c_add(char i2c, char address, char RW)
{

        if (i2c == 1){
            I2C1->DR = (address << 1) | RW;
            while((I2C1->SR1 & 2) == 0); // waiting for the ACK
            while(I2C1->SR1 & 2){
                (void)I2C1->SR1;
                (void)I2C1->SR2;
                if ((I2C1->SR1 & 2) == 0){
                    break; 
                }
        }
    } else if (i2c == 2){
        I2C2->DR = (address << 1) | RW; 
        while((I2C2->SR1 & 2) == 0); // waiting for the ACK
        while(I2C2->SR1 & 2){
            (void)I2C2->SR1;
            (void)I2C2->SR2;
            if ((I2C2->SR1 & 2) == 0){
                break; 
            }
        }
    }
} 
// Sending Data
void i2c_data(char i2c, char data)
{   
    if (i2c == 1){
        while ((I2C1->SR1 & (1 << 7 )) == 0);// bit 7 of SR1, wait til becames 1 (data reg is empty and ready)
        I2C1->DR = data;
        while ((I2C1->SR1 & (1 << 7 )) == 0);
    }   else if (i2c == 2) {
        while ((I2C2->SR1 & (1 << 7 )) == 0);// bit 7 of SR1, wait til becames 1 (data reg is empty and ready)
        I2C2->DR = data;
        while ((I2C2->SR1 & (1 << 7 )) == 0);
}

}
// Stop step
void i2c_stop(char i2c)
{   

    if (i2c == 1){

        // noted from Weew to read sr1 and sr2 before sendig the stop bit
        (void)I2C1->SR1;
        (void)I2C1->SR2;
        I2C1->CR1 |= (1 << 9); // SETING THE stop bit

    } else if (i2c == 2){
        (void)I2C2->SR1;
        (void)I2C2->SR2;
        I2C2->CR1 |= (1 << 9); // SETING THE stop bit
    }
}


void i2c_write(char i2c, char address, char data[])
{   int i = 0;
    i2c_start(i2c);
    i2c_add(i2c, address, 0);
    while (data[i]){
        i2c_data(i2c, data[i]);
        i++;
    }
    i2c_stop(i2c);
    
}

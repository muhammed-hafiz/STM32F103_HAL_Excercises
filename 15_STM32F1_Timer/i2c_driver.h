#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "stm32f10x.h"
#include "gpio_driver.h"

#define i2c_FM 0x2d // 400 KHz SCL
#define i2c_SM 0xB4 // 100 KHz SCL


void i2c_init(char i2c, unsigned short speed_mode);
void i2c_write(char i2c, char address, char data[]);


#endif
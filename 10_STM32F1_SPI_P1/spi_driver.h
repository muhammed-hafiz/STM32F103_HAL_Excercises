#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include "gpio_driver.h"
#include "stm32f10x.h"


void spi_init(unsigned short spi);
void spi_tx(unsigned short spi, char tx_char);
void spi_msg(unsigned short spi, char str[]);

#endif
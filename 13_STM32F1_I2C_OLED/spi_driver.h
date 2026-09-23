#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include "gpio_driver.h"
#include "stm32f10x.h"
#include <stdint.h>


void spi_init(unsigned short spi);
void spi_tx(unsigned short spi, char tx_char);
void spi_msg(unsigned short spi, char str[]);
uint16_t spi_rx(unsigned short spi);

#endif
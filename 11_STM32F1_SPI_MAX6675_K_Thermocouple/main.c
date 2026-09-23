#include "stm32f10x.h"
#include "systick_driver.h"
#include "spi_driver.h"
#include "usart_driver.h"
  
float max6675_read_temp(void);

void float_to_string(float value, char *buffer);

int main(void) {

    systick_init();
    spi_init(2);
    USART_init(2, 9600);
    UART_SEND(2, "This is UART 2.");
    delayms(20);
    float temp = 0.0;

    char temp_str[20];

    while(1) {


    temp = max6675_read_temp();
    if (temp >= 0) {
        // Valid temperature
        float_to_string(temp, temp_str);

        UART_SEND(2, temp_str);
        UART_SEND(2, "\n");
    } else {
        // Thermocouple not connected
        UART_SEND(2,"Thermocouple open or not connected.\n");
    }

    delayms(500);  // Read every 500ms

    }
}

float max6675_read_temp(void)
{
    uint16_t raw = spi_rx(2);  // Always use SPI2

    // Check for open thermocouple (bit D2 == 1)
    if (raw & 0x0004) {
        return -1.0f;  // Indicate error
    }

    // Extract bits D14..D3 (12 bits of temperature data)
    uint16_t temp_data = (raw >> 3) & 0x0FFF;

    // Multiply by 0.25 to convert to °C
    return temp_data * 0.25f;
}

void float_to_string(float value, char *buffer)
{
    if (value < 0) {
        *buffer++ = '-';
        value = -value;
    }

    int int_part = (int)value;
    int frac_part = (int)((value - int_part) * 100);  // 2 decimal places

    // Convert integer part
    char temp[10];
    int i = 0;
    if (int_part == 0) {
        temp[i++] = '0';
    } else {
        while (int_part > 0) {
            temp[i++] = '0' + (int_part % 10); // convert any integer digit to ASCII by adding (48) which is '0'
            int_part /= 10;
        }
    }

    // Reverse and copy integer digits to buffer
    while (i > 0) {
        *buffer++ = temp[--i];
    }

    *buffer++ = '.';

    // Convert fractional part (2 digits)
    buffer[0] = '0' + (frac_part / 10);
    buffer[1] = '0' + (frac_part % 10);
    buffer[2] = '\0';
}

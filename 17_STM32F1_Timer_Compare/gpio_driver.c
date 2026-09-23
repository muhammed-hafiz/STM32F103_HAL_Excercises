#include "gpio_driver.h"


inline void gpio_set_mode(struct gpio *gpio, uint16_t pin, uint8_t  mode, uint8_t  speed)
{
    /* Build the 4-bit configuration nibble: MODE[1:0] | CNF[1:0]<<2 */
    uint32_t cfg_nibble = (speed & 0x3) | ((mode & 0x3) << 2);

    /* Which 32-bit control register and bit-shift for this pin? */
    uint32_t shift = (pin & 0x7) * 4;                /* 0,4,8, … ,28 */
    volatile uint32_t *cr = (pin < 8) ? &gpio->CRL   /* pins 0-7  */
                                      : &gpio->CRH;  /* pins 8-15 */

    /* Atomically update the 4-bit field */
    uint32_t mask = 0xF << shift;                    /* clear nibble */
    *cr = (*cr & ~mask) | (cfg_nibble << shift); // here the (*cr & ~mask) is to keep other nibbles untouched
}

#include "stm32f10x.h"
#include "systick_driver.h"
#include "spi_driver.h"
  

int main(void) {

    systick_init();
    spi_init(1);
    delayms(20);

    while(1) {
        delayms(20);
        spi_msg(1, "HIman");
    }
}



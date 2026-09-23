#include "stm32f10x.h"
#include "systick_driver.h"
#include "i2c_driver.h"

 
int main(void) {

    systick_init();
    i2c_init(2, i2c_FM);

    while(1) {



    }
}

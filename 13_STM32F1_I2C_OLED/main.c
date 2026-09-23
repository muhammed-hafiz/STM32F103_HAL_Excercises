#include "stm32f10x.h"
#include "systick_driver.h"
#include "i2c_driver.h"
#include "oled_driver.h" 

 
int main(void) {

    systick_init();
	delayms(100);
    oled_init_64(2);

    //delayms(2000);
    oled_blank(2);
	oled_msg(2, 4, 20, "GCC Tool Chain!");
	
	
    while(1) {

		

    }
}

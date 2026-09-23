#include "timer_driver.h"
#include "gpio_driver.h"

int main(void) {

    // timer_compare_micro(char timer, char channel, int arr, int compare);
    // PA8 is TIM1 CH1

    timer_compare_micro(1, 2, 60000, 1000);


    while(1) {
    
    }
}
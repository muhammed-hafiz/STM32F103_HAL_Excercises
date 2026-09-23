#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

#include "stm32f10x.h"

enum timers {T, T1, T2, T3, T4};


void TDelay_Micros(char timer, int microS);
void TDelay_Millis(char timer, int milliS);
void TDelay_Micro(int microS);
void TDelay_Milli(int milliS);


int get_time_micros(char timer);
int get_time_millis(char timer);




#endif
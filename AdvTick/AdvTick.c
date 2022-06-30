/*
 * AdvTick.c    atmega16    F_CPU = 8000000 Hz
 * 
 * Created on: 04.11.2021
 *     Author: £ukasz L
*/
#include <avr/io.h> 

#include "AdvTick.h" 

volatile CNT_TYPE timersCnt[TIMERS_AMOUNT] = {0};
                                    
void Tick(){                                
    for(uint8_t i=0;i<TIMERS_AMOUNT;i++)
        if(timersCnt[i])timersCnt[i]--;
}                                                         
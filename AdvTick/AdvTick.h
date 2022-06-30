/*
 * AdvTick.h    atmega32/16    F_CPU = 20000000 Hz
 * 
 * Created on: 04.11.2021
 *     Author: £ukasz L 
 *  Medium complex mechanism, with parallels blocks tak allows use delay(sleep) and restoring context
 *  I not give any warranty of that
*/
                      
#ifndef ADVTICK_H_
#define ADVTICK_H_     

#include <util/delay.h>  

// depending of your needs and resources this limits how long sleep you can set uint8_t 255 uint16_t 65 535 etc.
#define CNT_TYPE uint16_t 
// here define how much parallel block do you need 
#define TIMERS_AMOUNT 4     

#define  TIMER_0 0
#define  TIMER_1 1 
#define  TIMER_2 2                     
#define  TIMER_3 3  
           
                 
extern volatile CNT_TYPE timersCnt[]; 
void Tick();                
       
             
 /*      
    schuld be invoked periodically to power the software-counters 
 */                                
#define TICK  _delay_ms(1); Tick()//     
                              
// reguired to work tick
#define TICK_CTRL() volatile void * backPtr[TIMERS_AMOUNT] = {0};volatile uint8_t selTimer = 0;                                       
                                                       
#define SET_TIMER(timer_num,how_long) timersCnt[timer_num] = how_long // set timer counter    
#define WAIT(timer_num,how_long) SET_TIMER(timer_num,how_long) // waits selected amount time  
                                            
#define CAT_(a, b) a ## b                                    
#define CAT(a, b) CAT_(a, b)   
#define VARNAME(Var) CAT(Var, __LINE__)  

// wroking in lock block interrupt block (even in loop if you use END_LOOP)
#define SLEEP(tisks) SET_TIMER(selTimer,tisks); backPtr[selTimer] = &&VARNAME(cnt); break; VARNAME(cnt): 
                                                                                            
// this block use to procedures which need to wait until selected time time will run out
#define SELECT_TIMER(timer_num) selTimer = timer_num;
#define RESTORE_CONTEX(timer_num) if((!timersCnt[timer_num]) && backPtr[timer_num]){volatile void * cp = backPtr[timer_num]; backPtr[timer_num] = 0; goto *cp; }; 

//this block needed variables that should bed keep while lock is used( TICK_CTRL macro)
#define LOCK(timer_num) SELECT_TIMER(timer_num);  RESTORE_CONTEX(timer_num); switch(timersCnt[timer_num]) case 0:  
                                                                            
                                                                                                       
                                                                                                                              
#define RETURN_IF_LOCKED(timer_num) if(timersCnt[timer_num])return 

// IF YOU USING SLEEP IN LOOP USE THIS AFTER LOOP BRACKETS ! 
#define END_LOOP() if(timersCnt[selTimer])break; 

     
#endif  /* ADVTICK_H_ */                                                                                            
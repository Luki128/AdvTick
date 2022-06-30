# AdvTick
Lib in C for AVR
 *  Medium complex mechanism, with parallels blocks tak allows use delay(sleep) and restoring context
 *  I not give any warranty of that

example 1:
```c
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>                                          
#include "AdvTick/AdvTick.h"  
                                                       
int main( void ) {      
     DDRD |= (1<<PD1)|(1<<PD2);
     TICK_CTRL();                                        
     while(1){                                                                                             
          LOCK( TIMER_1 ){              
              SLEEP(300); 
              PORTD ^= (1<<PD1);//blik ~ 300ms          
          }                                  
           
          LOCK( TIMER_2 ){                                         
              SLEEP(1000);        
              PORTD ^= (1<<PD2);//blik ~ 1000ms     
          }    
          TICK;//one tick 1ms
     }                                                    
}                                                                                                         
```

Example loop
```c
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>                                          
#include "AdvTick/AdvTick.h"  
                                                       
int main( void ) {      
     DDRD |= (1<<PD1)|(1<<PD2);
     TICK_CTRL(); 
     int i=0;// no local vars inside !
     while(1){                                                                                             
          LOCK( TIMER_1 ){              
              for(i=0;i<3;i++){
                SLEEP(300); 
                PORTD ^= (1<<PD1);//blik ~ 300ms  
              }
              END_LOOP(); 
              for(i=0;i<3;i++){
                SLEEP(600); 
                PORTD ^= (1<<PD1);//blik ~ 300ms  
              }
              END_LOOP(); 
          }                                  
           
          LOCK( TIMER_2 ){                                         
              SLEEP(1000);        
              PORTD ^= (1<<PD2);//blik ~ 1000ms     
          }    
          TICK;//one tick 1ms
     }                                                    
}                                                                                                         
```

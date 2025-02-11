// turn ON LED with SW1 and OFF with SW2
#include "TM4C123.h"                    // Device header

// SW1 - PF4
// SW2 - PF0
// Green LED - PF3


uint8_t button1_state, button2_state;
int main()
{
    // configure GPIO
    // turn on clock for GPIO port F
    SYSCTL->RCGCGPIO = SYSCTL->RCGCGPIO | (1<<5); 
    
    // SW2 PF0 is a special purpose pin (WAKE up for MCU)
    // to use as general purpose, need to unlock and configure lock and commit registers
    GPIOF->LOCK = 0x4C4F434B;  // from data sheet
    GPIOF->CR = GPIOF->CR | (1<<0);  // PF0 Unlock
    
    // PF3 is output for green LED
    GPIOF->DIR = GPIOF->DIR | (1<<3); 
    
    // PF4 is input for SW1 PF4
    GPIOF->DIR = GPIOF->DIR & (~(1<<4));
    
    // PF0 is input for SW2 PF0
    GPIOF->DIR = GPIOF->DIR & (~(1<<0));
    
    // enable internal pull-up register for SW1 PF4, SW2 PF0
    GPIOF->PUR = GPIOF->PUR | (1<<4) | (1<<0);
    
    // digitalize all pins: pin 3, 4, 0
    GPIOF->DEN = GPIOF->DEN | (1<<3) | (1<<4) | (1<<0);
    
    while(1)
    {   
        // pull up logic: button released = 1; pressed = 0;
        // data register: turn ON pin if configured as output; read if input
        button1_state = (GPIOF->DATA & (1<<4))>>4;
        if(button1_state == 0)  // button pressed
        {
            GPIOF->DATA = GPIOF->DATA | (1<<3);  // LED ON
        }
        
        // check SW2 state; also pull up logic
        button2_state = (GPIOF->DATA & (1<<0))>>0;
        if(button2_state == 0)
        {
            GPIOF->DATA = GPIOF->DATA & (~(1<<3));  // LED OFF
        }
        
    }
  
}

#include "TM4C123.h"                    // Device header

// SW1 - PF4
// SW2 - PF0
// Green LED - PF3


uint8_t buttonState;
int main()
{
    // configure GPIO
    // turn on clock for GPIO port F
    SYSCTL->RCGCGPIO = SYSCTL->RCGCGPIO | (1<<5); 
    
    // PF3 is output for green LED
    GPIOF->DIR = GPIOF->DIR | (1<<3); 
    
    // PF4 is input for SW1
    GPIOF->DIR = GPIOF->DIR & (~(1<<4));
    
    // enable internal pull-up register for SW1 PF4
    GPIOF->PUR = GPIOF->PUR | (1<<4);
    
    // digitalize all pins: pin 3, 4
    GPIOF->DEN = GPIOF->DEN | (1<<3) | (1<<4);
    
    while(1)
    {   
        // pull up logic: button released = 1; pressed = 0;
        // data register: turn ON pin if configured as output; read if input
        buttonState = (GPIOF->DATA & (1<<4))>>4;
        if(buttonState == 0)  // button pressed
        {
            GPIOF->DATA = GPIOF->DATA | (1<<3);  // LED ON
        }
        else
        {
            GPIOF->DATA = GPIOF->DATA & (~(1<<3));  // LED OFF
        }
    }
    
}

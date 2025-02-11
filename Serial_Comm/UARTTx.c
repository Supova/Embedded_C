// send 'a' when SW1 pressed and 'b' when SW2 pressed
#include "TM4C123.h"                    // Device header

// SW1 - PF4
// SW2 - PF0
// Green LED - PF3


uint8_t button1_state, button2_state;

void delay(long time)
{
    while(time--);
}

int main()
{
    // Configure GPIO for LED and switches
    SYSCTL->RCGCGPIO |= (1<<5);  // turn on clock for GPIO port F
    GPIOF->LOCK = 0x4C4F434B;
    GPIOF->CR |= (1<<0);        // PF0 Unlock
    GPIOF->DIR |= (1<<3);                       // PF3 is output for green LED
    GPIOF->DIR &= (~(1<<4)) & (~(1<<0));       // PF4 is input for SW1 PF4, SW2 PF0
    GPIOF->PUR |= (1<<4) | (1<<0);              // enable internal pull-up register for SW1 PF4, SW2 PF0
    GPIOF->DEN |= (1<<3) | (1<<4) | (1<<0);    // digitalize pins: 3, 4, 0
    
    // UART0 -> PA0 (Rx), PA1 (Tx)
    
    /*** SYSCTL Configuration ***/
    SYSCTL->RCGCUART |= (1<<0);   // (UART0) Enable Clock of UART Port used
    SYSCTL->RCGCGPIO |= (1<<0);  // (Port A) Enable Clock of GPIO Port used
        
    /*** GPIO Configuration ***/
    GPIOA->AFSEL |= (1<<0) | (1<<1);   // (PA0, PA1) Set Alternate Functions for UART pins high
    GPIOA->PCTL |= (1<<0) | (1<<4);   // Set the mode in PCTL (Port control)
    GPIOA->DEN |= (1<<0) | (1<<1);   // Digitalize GPIO Pins of UART line
        
    /*** UART Configuration ***/
    UART0->CTL &= (~(1<<0)) & (~(1<<8)) & (~(1<<9));
    UART0->IBRD = 104;                          // Set baud rate (9600) in IBRD & FBRD register
    UART0->FBRD = 11;   
    UART0->LCRH |= (0x3<<5);                   // Set Word length (8 bits) for UART communication in LCRH (line control)
    UART0->CC = 0x5;                          // (PIOSC) Select Clock source in CC register
    UART0->CTL |= (1<<0) | (1<<8) | (1<<9);  // Turn on UART EN & TXEN bits from CTL
    
    while(1)
    {   
        // Pull up logic: button released = 1; pressed = 0;
        button1_state = (GPIOF->DATA & (1<<4))>>4;
        if(button1_state == 0)  // button pressed
        {
            while((UART0->FR & (1<<5)) != 0);  // check FIFO; if 0 (empty), write data to DR
            UART0->DR = 'a';  // data register
            delay(6000000);   // debouncing
        }
        
        button2_state = (GPIOF->DATA & (1<<0))>>0;
        if(button2_state == 0)
        {
            while((UART0->FR & (1<<5)) != 0);
            UART0->DR = 'b';
            delay(6000000);
        }
        
    }
  
}

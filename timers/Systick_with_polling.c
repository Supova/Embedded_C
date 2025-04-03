#include "TM4C123.h" // Device header
#include <stdint.h>
#include <stdbool.h>

#define SYSTEM_CLOCK 16000000 // 16 MHz
#define PORT_F (1U << 5)
#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
#define LED_YELLOW (LED_RED | LED_GREEN)

void SysTick_Init();
void SysTick_delay_1s();
void SysTick_delay_seconds(uint32_t seconds);

int main()
{
    SYSCTL->RCGCGPIO |= PORT_F;
    GPIOF->DIR |= LED_RED | LED_BLUE | LED_GREEN;
    GPIOF->DEN |= LED_RED | LED_BLUE | LED_GREEN;

    SysTick_Init();

    while (1)
    {
        GPIOF->DATA = LED_RED;
        SysTick_delay_seconds(15);
        GPIOF->DATA &= ~LED_RED;

        GPIOF->DATA |= LED_GREEN;
        SysTick_delay_seconds(15);
        GPIOF->DATA &= ~LED_GREEN;
    }
}

void SysTick_Init()
{
    SysTick->LOAD = SYSTEM_CLOCK - 1; // Load for 1 second (16M ticks)
    SysTick->VAL = 0;                 // Clear current value
    SysTick->CTRL = (1 << 0) |        // Enable SysTick
                    (1 << 2);         // Use system clock (16MHz)
}

void SysTick_delay_1s()
{
    while ((SysTick->CTRL & (1 << 16)) == 0); // Wait for COUNTFLAG
}

void SysTick_delay_seconds(uint32_t seconds)
{
    while (seconds--)
    {
        SysTick_delay_1s(); // Wait for 1 second each iteration
    }
}

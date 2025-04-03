# Learning from Mistakes



<table>
<tr>
<th>Code</th>
<th>Notes</th>
</tr>
<tr>
<td>
  
```c
void SysTick_delay_1s()
{
    SysTick->LOAD = SYSTEM_CLOCK - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = (1 << 0) | // enable systick
                    (1 << 2);  // use system clock: 16MHz
    SysTick->CTRL &= ~(1<<1);  // disable interrupt
}
```
  
</td>
<td>

Every time this function is called, it reinitializes the timer, which is unnecessary and inefficient. 
Resetting the countdown each time disrupts the natural flow of the timer.
Instead, you should configure it once in an Init() and then just poll it in a delay function.

</td>
</tr>
<tr>
<td>

```c
void SysTick_delay_s(uint32_t seconds)
{
    while(seconds--)
    {
        SysTick_delay_1s();
        while((SysTick->CTRL & (1<<16)) == 0);
    }
}
```

</td>
<td>

Just check the COUNT flag to see when 1 second has passed. 
When the function SysTick_delay_seconds() returns, it means all seconds have passed.

```c
void SysTick_delay_1s()
{
    while ((SysTick->CTRL & (1 << 16)) == 0); // Wait until COUNTFLAG is set
}

void SysTick_delay_seconds(uint32_t seconds)
{
    while (seconds--)
    {
        SysTick_delay_1s();  // Wait for 1 second
    }
}
```

</td>
</tr>

</table>
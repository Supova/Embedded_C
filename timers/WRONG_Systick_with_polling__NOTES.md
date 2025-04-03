# Learning from Mistakes

SOME TEXT

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
Instead, you should configure it once and then just poll it in a delay function.
    
Disabling the interrupt after enabling timer

</td>
</tr>
</table>

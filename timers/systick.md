

## Steps to initialize SysTick Timer:
### 1. SysTick->LOAD must be set before enabling

This ensures that the timer starts counting from the correct value.

Load = (system frequency * delay_time) - 1;

* We need to substract 1 as 0 is included in the count.

Maximum delay = ((Max reload) + 1)/(clock freq);
* For a 24-bit timer, the max reload value is 0xFFFFFF
* With a system clock freq of 16MHz, the max delay is about 1.0486 seconds

### 2. SysTick->VAL should be cleared

Writing 0 to VAL resets the current counter to prevent unexpected behavior.

 ### 3. Enable SysTick in the control and status register

This ensures that the timer starts counting only after everything is properly configured.
* bit 0: timer enable
* bit 1: interrupt
* bit 2: clock source

Without the interrupt enabled, we need to manually check if the COUNT flag (bit 16) has been set after each cycle of the SysTick timer

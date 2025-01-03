#include <stdio.h>
#include <stdint.h>

/*
clear bits in 4,5,6 positions (0-indexed)
0_ _ _ 0000  = 0x70 = 112

Take complement ~ then &
0111 0000
1000 1111  <- could use as mask too (0x8F)
*/
int main()
{
    uint32_t num = 123;
    printf("New num is %d", (num & (~0x70)));
    // printf("New num is %d", (num & (~(7<<4))));

    return 0;
}

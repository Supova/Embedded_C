/*
Takes a signed 8-bit integer as input and prints its binary representation:

Algorithm:
 - Read the binary from left to right
    - Right-shift the number by bit position, decreasing, to read from left-right
        - desired bit will be at LSB
    - And& right-shifted num with 1 to get single bit
    - Do a for-loop from bit position 7 to 0, so index > -1, index--
*/
#include <stdio.h>
#include <stdint.h>

int main()
{
    int8_t num;
    printf("Enter a 8bit integer to see its binary representation: ");
    scanf("%d", &num);

    for (int index = 7; index > -1; index--)
    {
        int bit = (num >> index) & 1;
        printf("%d", bit);
    }

    return 0;
}

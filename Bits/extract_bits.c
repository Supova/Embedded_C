#include <stdio.h>
#include <stdint.h>

/*Extract bit positions from 9-14 and store in a variable.
0[000 000]0 0000 0000

Right shift until desired bits reach LSB.
0000 0000 00[00 0000]

And(&) mask of number of desired bits (11 1111) to extract the original bits.
    0000 0000 00[00 0000]
 &               11 1111
--------------------------
                [00 0000]
*/
int main()
{
    uint16_t var = 0xB410;
    uint8_t bits = (uint8_t)((var >> 9) & 0x003F);

    printf("%x", bits);


    return 0;
}

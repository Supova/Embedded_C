#include <stdio.h>
#include <stdint.h>

/* set bits at 4th and 7th position of given num and print result
bit positions start LSB index 0
0000 0000 _00_ 0000
*/
int main()
{
    uint16_t num = 23;

    // mask: 1 << 4   (0001 0000)
    // mask2: 1 << 7  (1000 0000)
    // set bit using | (or)
    uint16_t num2 = num | (1 << 4);
    num2 = num2 | (1 << 7);
    // or could use mask 0x90 : 1001 0000
    // uint16_t num2 = num | 0x90;
    printf("%d\n", num2);
}

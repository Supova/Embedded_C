#include <stdio.h>

long long int g_data = 0xFFFEABCD11111234;

int main()
{
    short *pAddr = (short*)&g_data;  
    printf("Value of pAddr: %p\n", pAddr);
    printf("Value at address %p is: %x\n", pAddr, *pAddr);

    pAddr = pAddr + 1; // address will increment by 2 since ptr is short type
    printf("Value of pAddr: %p\n", pAddr);
    printf("Value at address %p is: %x\n", pAddr, *pAddr);

    return 0;
}

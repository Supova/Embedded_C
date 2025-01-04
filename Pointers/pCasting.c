#include <stdio.h>

long long int g_data = 0xFFFEABCD11111234;

int main()
{
    char *pAddr = (char*)&g_data;  // explicit
    // char *pAddr = &g_data;     // implicit
    printf("Value at address %p is: %x\n", pAddr, *pAddr);

    short *pAddr2 = (short*)&g_data;
    printf("Value at address %p is: %x\n", pAddr2, *pAddr2);
    
    int *pAddr3 = (int*)&g_data;
    printf("Value at address %p is: %x\n", pAddr3, *pAddr3);
    
    long long int *pAddr4 = (long long int*)&g_data;
    printf("Value at address %p is: %llx\n", pAddr4, *pAddr4);

    return 0;
}

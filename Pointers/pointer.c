#include <stdio.h>

int main()
{
    char num = 100;
    printf("The address of variable num: %p\n", &num);

    char* p_num = &num;  // address of operator

    char data = *p_num;  // de-referencing operator
    printf("One byte of data from the pointer: %d\n", data);

    *p_num = 65;
    printf("Original variable: %d\n", num);

    return 0;
}

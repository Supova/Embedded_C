#include <stdio.h>

/*
testing of bits: &
setting of bits: | 
clearing of bits: ~ and &
toggling of bits: ^
*/
int main()
{
    int num1, num2;

    printf("Enter 2 numbers seperated by space: ");
    scanf("%d %d", &num1, &num2);

    int AND = num1 & num2;
    int OR = num1 | num2;
    int XOR = num1 ^ num2;
    int NOT1 = ~num1;
    int NOT2 = ~num2;

    printf("%d %d %d %d %d", AND, OR, XOR, NOT1, NOT2);

    return 0;
}

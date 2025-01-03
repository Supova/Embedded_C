#include <stdio.h>

int main()
{
    // write a program to find out if user entered int is even or odd
    int num;
    printf("Enter a num: ");
    scanf("%d", &num);

    // check if LSB is 1
    if (num & 1)
        printf("Odd");
    else
        printf("Even");

    return 0;
}

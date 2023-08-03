#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int int1 = get_int("What is the value of integer 1? ");
    int int2 = get_int("What is the value of integer 2? ");
    if (int1 > int2)
    {
        printf("int1 (value of %s) is greater than int2 (value of %s)", int1, int2);
    }
    else if (int1 < int2)
    {
        printf("int1 (value of %s) is less than int2 (value of %s)", int1, int2);
    }
    else
    {
        printf("int1 (value of %s) is equal to int2 (value of %s)", int1, int2);
    }
}
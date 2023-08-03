#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int numMeows = 0;
    while (numMeows < 1)
    {
        numMeows = get_int("How many meows would you like? (enter a positive integer) ");
        if (numMeows < 1)
        {
            printf("You entered %d")
        }
    }
}
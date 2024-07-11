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
            printf("\nYou entered %d.\nThis is an invalid input. You must enter a positive integer value.\n", numMeows);
        }
    }
    printf("\n");
    for (int i = 0; i < numMeows; i++)
    {
        printf("Meow\n");
    }
}
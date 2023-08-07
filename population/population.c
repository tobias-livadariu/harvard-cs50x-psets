#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    // initializing the variable that will hold the user's starting llama population size
    int popStartSize;
    // using a do-while loop to prompt the user for the starting population size and reprompting them if their input was an integer less than 9
    do
    {
        popStartSize = get_int("Start size: ");
    }
    while (popStartSize < 9);

    // TODO: Prompt for end size
    // initializing the variable that will hold the user's ending llama population size
    int popEndSize;
    // using a do-while loop to prompt the user for the ending population size and reprompting them if their input was an integer less than the inputted starting population size
    do
    {
        popEndSize = get_int("End size: ");
    }
    while (popEndSize < popStartSize);

    // TODO: Calculate number of years until we reach threshold
    // initializing the variable that will hold the number of elapsed years, and assigning it a value of 0
    int numYears = 0;
    // this while loop increases popStartSize by the number of llamas that were born (popStartSize / 3) and decreasing it by the number of llamas that died (popStartSize / 4) to simulate the years going by
    while (popEndSize > popStartSize)
    {
        popStartSize = popStartSize + (popStartSize / 3) - (popStartSize / 4);
        numYears += 1;
    }

    // TODO: Print number of years
    printf("Years: %i\n", numYears);
}

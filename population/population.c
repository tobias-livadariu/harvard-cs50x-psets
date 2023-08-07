#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int popStartSize = get_int("Start size: ");

    // TODO: Prompt for end size
    int popEndSize = get_int("End size: ");

    // TODO: Calculate number of years until we reach threshold
    int numYears = 0;
    while (popEndSize >= popStartSize);
    {
        popStartSize = popStartSize + (popStartSize / 3) - (popStartSize / 4)
        numYears += 1
    }

    // TODO: Print number of years
    printf("Years: %i\n", numYears)
}

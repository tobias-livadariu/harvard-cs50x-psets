#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int popStartSize;
    do
    {
        popStartSize = get_int("Start size: ");
    }
    while (popStartSize < 9);

    // TODO: Prompt for end size
    int popEndSize;
    do
    {
        popEndSize = get_int("End size: ");
    }
    while (popEndSize < popStartSize);

    // TODO: Calculate number of years until we reach threshold
    int numYears = 0;
    while (popEndSize >= popStartSize);
    {
        popStartSize = popStartSize + (popStartSize / 3) - (popStartSize / 4);
        numYears += 1;
    }

    // TODO: Print number of years
    printf("Years: %i\n", numYears);
}

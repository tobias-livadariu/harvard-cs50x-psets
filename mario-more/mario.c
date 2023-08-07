#include <cs50.h>
#include <stdio.h>

// Referencing the function that is used to print the vertical columns.
void column_printer(int size);
// Referencing the function that can be used to repeatedly print white spaces.
void space_printer(int length);

int main(void)
{
    // Initializing the variable that will store the height of the pyramid.
    int height;
    /* Using a do-while loop to prompt the user for the integer height of the pyramid,
    and reprompting them if the height isn't between 1 and 8 inclusively (note that I learned to do multi-line comments in C from my dad). */
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    /* Using a for loop to print out the pyramid.
    Each iteration of this for loop prints out one row of the pyramid. */
    for (int row = 0; row < height; row++)
    {
        space_printer(height - (row + 1));
        column_printer(row);
        space_printer(1);
        column_printer(row);
        printf("\n");
    }
}

// Defining the function that is used to print the vertical columns.
void column_printer(int size)
{
    for (int column = 0; column <= size; column++)
        {
            printf("#");
        }
}

// Defining the function that is used to print spaces to properly space out the vertical columns of increasing and then decreasing height.
void space_printer(int length)
{
    for (int count = 0; count < length; count++)
    {
        printf(" ");
    }
}
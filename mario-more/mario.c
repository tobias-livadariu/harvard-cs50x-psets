#include <cs50.h>
#include <stdio.h>

// Referencing the function that is used to print the vertical columns
void column_printer(int size);
// Referencing the function that can be used to 
void space_printer(int length);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int row = 0; row < height; row++)
    {
        space_printer(height - (row + 1));
        column_printer(row);
        space_printer(1);
        column_printer(row);
        printf("\n");
    }
}

// Defining the function that is used to print the vertical columns
void column_printer(int size)
{
    for (int column = 0; column <= size; column++)
        {
            printf("#");
        }
}

// Defining the function that is used to print spaces to properly space out the vertical columns of increasing and then decreasing height
void space_printer(int length)
{
    for (int count = 0; count < length; count++)
    {
        printf(" ");
    }
}
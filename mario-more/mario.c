#include <cs50.h>
#include <stdio.h>

void column_printer(int size);
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

void column_printer(int size)
{
    for (int column = 0; column <= size; column++)
        {
            printf("#");
        }
}

void space_printer(int length)
{
    for (int count = 0; count < length; count++)
    {
        printf(" ");
    }
}
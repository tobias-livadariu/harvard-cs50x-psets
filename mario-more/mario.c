#include <cs50.h>
#include <stdio.h>

void column_printer(int size);

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
        column_printer(row);
        printf(" ");
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
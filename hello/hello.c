#include <cs50.h>
#include <stdio.h>

int main(void)
{
    /* Initializing a variable called name that takes string values
    and assigning to it the user's input when prompted to enter their name */
    string name = get_string("What's your name? ");
    // Printing the user's name to the screen in a more personalized version of "hello, world"
    printf("hello, %s\n", name);
}
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    float first = get_string("What is your first name? ");
    string last = get_string("What is your last name? ");
    printf("Hello, %s %s\n", first, last);
}
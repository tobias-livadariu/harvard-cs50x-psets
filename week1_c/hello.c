#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string first = get_string("What is your first name? ");
    string last = get_string("What is your last name? ");
    printf("Hello, %s %s\n" * 3, first, last);
}
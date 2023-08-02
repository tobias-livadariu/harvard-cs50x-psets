#include <stdio.h>

int main(void)
{
    string first = get_string("What is your first name? ");
    string last = get_string("What is your last name? ");
    printf("Hello, %s %s\n", first, last);
}

#include <cs50.h>
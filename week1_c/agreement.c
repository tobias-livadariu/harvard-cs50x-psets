#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

int main(void)
{
    char userRes = '';
    while (userRes != 'y' && userRes != 'n')
    {
        printf("TERMS AND AGREEMENTS:\n");
        printf("-------------------------------------\n");
        printf("1. No anime\n");
        printf("\n");
        userRes = tolower(get_char("DO YOU ACCEPT THE FOLLOWING TERMS AND AGREEMENTS? (Y/N) "));
        if (userRes == 'y')
        {
            printf("YOU HAVE ACCEPTED THE TERMS AND AGREEMENTS");
        }
        else if (userRes == 'n')
        {
            printf("YOU HAVE REJECTED THE TERMS AND AGREEMENTS");
        }
        else
        {
            printf("You entered this character: %c\nThis is invalid input, you must enter a Y or N\n", userRes);
        }
    }
}
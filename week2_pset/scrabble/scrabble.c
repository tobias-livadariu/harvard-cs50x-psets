#include <cs50.h>
#include <stdio.h>

/* prototype for a function that converts an input string
into its corresponding scrabble point value */

int scrabbler(string word);

int main(void)
{
    // getting the input strings
    string string1 = get_string("Player 1: ");
    string string2 = get_string("Player 2: ");

    // converting the input strings to their corresponding point values
    int points1 = scrabbler(string1);
    int points2 = scrabbler(string2);

    if (points1 > points2)
    {
        printf("Player 1 wins!\n");
    }
    else if (points1 < points2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int scrabbler(string word)
{
    int totalPoints = 0;
    /* for loop that iterates over every character in the variable word
    and increments totalPoints for the character's corresponding value */
    for (int i = 0; word[i] != '\0'; i++)
    {
        char c = word[i];

        /* conditional statements that increment totalPoints
        by the correct value for the character in string[i] */
        /* note that if the character is not in the alphabet,
        this conditional statement will ignore it */
        if (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'l' ||
            c == 'L' || c == 'n' || c == 'N' || c == 'o' || c == 'O' || c == 'r' || c == 'R' ||
            c == 's' || c == 'S' || c == 't' || c == 'T' || c == 'u' || c == 'U')
        {
            totalPoints += 1;
        }
        else if (c == 'd' || c == 'D' || c == 'g' || c == 'G')
        {
            totalPoints += 2;
        }
        else if (c == 'b' || c == 'B' || c == 'c' || c == 'C' || c == 'm' || c == 'M' || c == 'p' ||
                 c == 'P')
        {
            totalPoints += 3;
        }
        else if (c == 'f' || c == 'F' || c == 'h' || c == 'H' || c == 'v' || c == 'V' || c == 'w' ||
                 c == 'W' || c == 'y' || c == 'Y')
        {
            totalPoints += 4;
        }
        else if (c == 'k' || c == 'K')
        {
            totalPoints += 5;
        }
        else if (c == 'j' || c == 'J' || c == 'x' || c == 'X')
        {
            totalPoints += 8;
        }
        else if (c == 'q' || c == 'Q' || c == 'z' || c == 'Z')
        {
            totalPoints += 10;
        }
    }

    // returning the calculated number of total points for the string
    return totalPoints;
}

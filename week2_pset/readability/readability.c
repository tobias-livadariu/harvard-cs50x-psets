#include <cs50.h>
#include <stdio.h>

/* Prototype declarations for the functions
used in this program. */
int numLetters(string text);
int numWords(string text);
int numSentances(string text);

int main(void)
{
    // Getting a string from the user.
    string userText = get_string("Text: ");

    /* Using the prototyped functions above to find the number of words,
    letters, and sentances in the user's string. */
    float numUserLetters = numLetters(userText);
    float numUserWords = numWords(userText);
    float numUserSentances = numSentances(userText);

    /* Finding the values of L and S in the user's string
    for the Coleman-Lau index. */
    float L = (numUserLetters / numUserWords) * 100;
    float S = (numUserSentances / numUserWords) * 100;

    /* Finding the grade level of the user's text
    according to the Coleman-Lau index. */
    float gradeLvl = 0.0588 * L - 0.296 * S -15.8;

    /* Rounding gradeLvl to the nearest integer. */
    basicIntGradeLvl = (int)gradeLvl;
    if ((gradeLvl - basicIntGradeLvl) >= 0.5)
    {
        intGradeLvl = ++basicIntGradeLvl;
    }
    else
    {
        intGradeLvl = basicIntGradeLvl;
    }

    /* Printing the text's grade level back
    to the user. */
    if (gradeLvl = 0)
    {
        printf("Before Grade 1\n");
    }
    else if (gradeLvl => 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", intGradeLvl);
    }
}

/* Defining a function to find the number
of letters in the user's string. */
int numLetters(string text)
{
    int letterCount = 0;
    for (int i = 0; i++, text[i] != '\0')
    {
        char c = text[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            letterCount++;
        }
    }

    /* Returning the counted
    number of letters to the user. */
    return letterCount;
}

/* Defining a function to find the number
of words in the user's string. */
int numWords(string text)
{
    int wordCount = 0;
    for (int i = 0; i++, text[i] != '\0')
    {
        char c = text[i];
        if (c = ' ')
        {
            wordCount++;
        }
    }

    /* Returning the counted
    number of letters to the user. */
    return letterCount;
}

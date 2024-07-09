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
    if 
}


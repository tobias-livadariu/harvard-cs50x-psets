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
    int numUserLetters = numLetters(userText);
    int numUserWords = numWords(userText);
    int numUserSentances = numSentances(userText);

    /* Finding the values of L and S in the user's string
    for the Coleman-Lau index. */
    L = () / ()
}


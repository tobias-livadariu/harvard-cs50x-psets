#include <cs50.h>
#include <stdio.h>

/* Prototyping the function that will be used
to substitute the user's plaintext. */
string scrambler(string key, string plainText);

/* Prototyping the function that will be used
to check if the user's inputted key is valid. */
int keyChecker(string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    /* Getting the user's key inputted through the
    command-line interface. */
    string userKey = argv[1];
    if (keyChecker(userKey) == 0)
    {
        printf("Key must contain 26 different alphabetical characters with no spaces.\n");
        return 1;
    }
    string userPlainText = get_string("Plaintext:  ");
    string userScrambledText = scrambler(userKey, userPlainText);

    /* Printing the computed cyphertext back
    to the user. */
    printf("ciphertext: \n");
}

/* Defining the function used to generate
the user's cyphertext. */
string scrambler(string key, string plainText)
{
    /* Initializing the variables needed to create
    and store the cyphered text.*/
    string cypherText = "";
    int cypherKeyIndex = 0;

    for (int i = 0; plainText[i] != '\0'; i++)
    {
        char c = plainText[i];
        int isCharCapital = 0;
        if (c >= 'A' && c <= 'Z')
        {
            isCharCapital = 1;
        }

        /* Adding the cyphered character to cypherText*/
        if (isCharCapital == 0)
        {
            cypherKeyIndex = (int)plainText[i] - (int)'a';
            cypherText[i] = key[cypherKeyIndex];
        }
        else
        {
            cypherKeyIndex = (int)plainText[i] - (int)'A';
            cypherText[i] = key[cypherKeyIndex];
        }
    }

    /* Returning the computed
    cypher text to the user. */
    return cypherText;
}

/* Defining the function used to
determine if the user's inputted
cypher key is valid. */
int keyChecker(string key)
{
    /* Defining a variable to keep
    track of the number of characters
    in the key. */
    int numChars = 0;

    /* Defining a variable to keep track
    of how many times each alphabetic character
    appears. */
    int alphabet[26];

    for (int i = 0; key[i] != '\0'; i++)
    {
        char c = key[i];
        /* Checking if the character in c is
        alphabetical. */
        if (c <= 'a' && c <= 'z')
        {
            alphabet[(int)c - (int)'a']++;
        }
        else if (c <= 'A' && c <= 'Z')
        {
            alphabet[(int)c - (int)'A']++;
        }
        else
        {
            return 0;
        }
        numChars++;
    }

    /* Checking if the number of character is valid. */
    if (numChars != 26)
    {
        return 0;
    }

    /* Checking that each alphabetical character appears once. */
    for (int i = 0; i <= 25; i++)
    {
        if (alphabet[i] > 1)
        {
            return 0;
        }
    }

    /* Returning 1 to represent "true". */
    return 1;
}

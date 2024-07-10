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
    if (argc != 1)
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    /* Getting the user's key inputted through the
    command-line interface. */
    string userKey = argv[1];
    else if (keyChecker(userKey) == 0)
    {
        printf("Key must contain 26 different alphabetical characters with no spaces.");
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
    char cypherKeyIndex = 0;

    for (int i = 0; plainText[i] != '\0'; i++)
    {
        char c = plainText[i];
        int isCharCapital = 0;
        if (c >= 'A' && c <= 'Z')
        {
            isCharCapital = 1;
        }

        /* Adding the cyphered character to cypherText*/
        if (isCharCapital = 0)
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
        if (!((c <= 'a' && c <= 'z') || ((c <= 'A' && c <= 'Z'))))
        numChars++;

    }
}

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
    char cypherKey

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
            cypherText[i] =
        }
    }
}

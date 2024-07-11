#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* Prototyping the function that will be used
to substitute the user's plaintext. */
int scrambler(string key, string plainText, int lenPlainText);

/* Prototyping the function that will be used
to check if the user's inputted key is valid. */
int keyChecker(string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key (where the key is composed of 26 different alphabetical "
               "characters with no spaces).\n");
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
    string userPlainText = get_string("plaintext:  ");
    printf("ciphertext: ");
    int lenUserPlainText = strlen(userPlainText);

    /* Printing the scrambled text. */
    scrambler(userKey, userPlainText, lenUserPlainText);
    printf("\n");
}

/* Defining the function used to generate
the user's ciphertext. */
int scrambler(string key, string plainText, int lenPlainText)
{
    /* Initializing the variables needed to create
    and store the ciphered text.*/
    char cipheredCharacter = ' ';
    int cipherKeyIndex = 0;

    for (int i = 0; plainText[i] != '\0'; i++)
    {
        char c = plainText[i];
        if (c >= 'A' && c <= 'Z')
        {
            cipherKeyIndex = (int) c - (int) 'A';
            cipheredCharacter = toupper(key[cipherKeyIndex]);
        }

        /* Adding the ciphered character to cipherText*/
        else if (c >= 'a' && c <= 'z')
        {
            cipherKeyIndex = (int) c - (int) 'a';
            cipheredCharacter = tolower(key[cipherKeyIndex]);
        }
        else
        {
            cipheredCharacter = c;
        }
        printf("%c", cipheredCharacter);
    }

    /* Ending the function. */
    return 0;
}

/* Defining the function used to
determine if the user's inputted
cipher key is valid. */
int keyChecker(string key)
{
    /* Defining a variable to keep
    track of the number of characters
    in the key. */
    int numChars = 0;

    /* Defining a variable to keep track
    of how many times each alphabetic character
    appears. */
    int alphabet[26] = {0};

    for (int i = 0; key[i] != '\0'; i++)
    {
        char c = key[i];
        /* Checking if the character in c is
        alphabetical. */
        if (c >= 'a' && c <= 'z')
        {
            alphabet[(int) c - (int) 'a']++;
        }
        else if (c >= 'A' && c <= 'Z')
        {
            alphabet[(int) c - (int) 'A']++;
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

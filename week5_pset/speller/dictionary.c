// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 109225;

// Hash table
node *table[N];

/* Defining a variable to hold the
number of loaded words into the hash
table. */
int numLoaded = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    /* Getting the hash value of the
    current word being spell checked. */
    int hashValue = hash(word);

    /* Using a for loop and node pointer
    to run through the linked list at the
    word's hash value and check for matches. */
    for (node *runner = table[hashValue]; runner != NULL; runner = runner->next)
    {
        /* Checking if the word being spellchecked is
        the same as the word that the runner node pointer
        is pointing too. */
        if (strcasecmp(runner->word, word) == 0)
        {
            return true;
        }
    }

    /* If the runner has gone through the entire linked list and not found
    a match, that means the word being spell checked was not in the
    dictionary used. */
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    /* Initializing a variable to hold
    the hash value. */
    int hashValue = 0;

    /* Using a for loop to iterate
    over the first four characters
    of the word. */
    for (int i = 0, max = 4; i < max; i++)
    {
        char curChar = word[i];
        if (curChar == '\0')
        {
            break;
        }
        else if (curChar == '\'')
        {
            curChar = 'z';
        }

        /* Initializing a variable to
        store the necessary value from the
        current character to add to the hash
        value. */
        int valueAdding = ('A' - toupper(curChar)) * pow();
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    /* Changing all pointer values in the node table
    array to be false. */
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    /* Defining a string that will hold each individual
    word from the dictionary. */
    char *curWord = malloc(sizeof(char) * (LENGTH + 1));
    FILE *openDictionary = fopen(dictionary, "r");
    if (openDictionary == NULL)
    {
        free(curWord);
        return false;
    }

    /* Iterating over every string in the
    dictionary file and loading them to the
    hash table. */
    while (fscanf(openDictionary, "%s", curWord) != EOF)
    {
        /* Saving the hash value for the
        current word in a variable. */
        int curHashValue = hash(curWord);

        /* Allocating memory for the temporary node that will be
        used to form the linked list. */
        node *n = malloc(sizeof(node));
        strcpy(n->word, curWord);
        n->next = NULL;

        /* Handling the base case of if
        no collisions have occured in the
        current word's bucket. */
        if (table[curHashValue] == NULL)
        {
            table[curHashValue] = n;
        }
        else
        {
            n->next = table[curHashValue];
            table[curHashValue] = n;
        }

        /* Incrementing numLoaded to keep
        track of the additional word that
        been loaded into the hash table. */
        numLoaded++;
    }

    // Freeing variables used in this
    free(curWord);
    fclose(openDictionary);

    /* If the function reaches this point,
    that means the load function concluded successfully. */
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return numLoaded;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    /* Running through every linked list
    in the hash table with a for loop. */
    for (int i = 0; i < N; i++)
    {
        /* Running through every element in each
        linked list with another for loop. */
        for (node *runner = table[i], *tmp = table[i]; runner != NULL; runner = tmp)
        {
            /* Holding the next element in the tmp
            variable. */
            tmp = runner->next;
            free(runner);
        }
    }
    return true;
}

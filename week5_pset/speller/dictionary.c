// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

/* Defining a variable to hold the
number of loaded words into the hash
table. */
int numLoaded = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashValue = hash(word);
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
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
    char *curWord = malloc(sizeof(char) * LENGTH);
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
            table = n;
        }

        /* Incrementing numLoaded to keep
        track of the additional word that
        been loaded into the hash table. */
        nunLoaded++;
    }

    // Freeing variables used in this
    free(curWord);
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return numLoaded;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Defining the datatype structure that will
be used to store each candidate and their number of
votes. */
typedef struct
{
    string name;
    int votes;
}candidate;

int main(int argc, string argv[])
{
    if (argc < 1)
    {
        /* Warning the user for incorrect
        input. */
        printf("Usage: ./plurality [candidate ...]\n");
        return 1;
    }
    else
    {
        /* Getting the number of voters
        from the user. */
        int numVoters = get_int("Number of voters: ");
    }

    /* Defining the array that will
    store the candidates and their number of votes. */
    candidate runners[numVoters];

    /* Assigning the runners inputted
    into the program to the runners[] array. */
    for (int i = 0; i < numVoters; i++)
    {
        runners[i].name = argv[i];
    }

    
}

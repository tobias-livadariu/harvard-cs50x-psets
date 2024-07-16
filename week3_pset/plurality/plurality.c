#include <cs50.h>
#include <stdio.h>
#include <string.h>

/* Defining the datatype structure that will
be used to store each candidate and their number of
votes. */
typedef struct
{
    string name;
    int votes;
}candidate;

void voting(int voteCount, candidate names, int numNames);

int main(int argc, string argv[])
{
    int numCandidates = argc - 1;
    if (numCandidates < 1)
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
    candidate runners[numCandidates];

    /* Assigning the runners inputted
    into the program to the runners[] array. */
    for (int i = 0; i < numCandidates; i++)
    {
        runners[i].name = argv[i];
    }

    voting(numVoters, runners, numCandidates);
    return 0;
}

void voting(int voteCount, candidate names, int numNames)
{
    for (int i = 0; i < voteCount; i++)
    {
        /* Getting the current vote. */
        string curVote = get_string("Vote: ");

        /* Seeing if the current vote
        matches any candidates. */
        int numErrors = 0;
        for (int i = 0; i < numNames; i++)
        {
            if (strcmp(curVote, names[i]) == 1)
            {
                names[i].votes++;
            }
            else
            {
                numErrors++;
            }

            /* Checking if no candidates had their votes
            incremented. */
            if (numErrors = numNames)
            {
                printf("Invalid vote.\n");
            }
        }
    }

    /* Finding who got the most votes. */
    int numEqual = 0;
    int curBiggest = 0;
    string curWinner = "none";
    char* curTied[numCandidates];
    for (int i == 0; i < numCandidates; i++)
    {
        if (runners[i].votes > curBiggest)
        {
            numEqual = 0;
            curBiggest = runners[i].votes;
            curTied[numCandidates];
            curWinner = runners[i].name;
        }
        else if (runners[i].votes = curBiggest)
        {
            if (strcmp(curWinner, "none") == 1)
            {
                curTied[numEqual] = runners[i].names;
                numEqual++;
            }
            else
            {
                curTied[numEqual] = curWinner;
                curTied[numEqual + 1] = runners[i].name;
                curWinner = "none";
            }
        }
    }

    /* Printing out the winner. */
    if (strcmp(curWinner, "none") == 1)
    {
        for (int i = 0; i < numEqual; i++)
        {
            printf("%s\n", curTied[numEqual]);
        }
    }
    else
    {
        printf("%s\n", curWinner);
    }
}

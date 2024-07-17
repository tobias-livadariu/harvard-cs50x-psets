#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name, int numCandidates);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name, (argc - 1)))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name, int numCandidates)
{
    int numFails = 0;
    for (int i = 0; i < numCandidates; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
        }
        else
        {
            numFails++;
        }
    }
    if (numFails == numCandidates)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    /* Finding who got the most votes. */
    int numEqual = 0;
    int curBiggest = 0;
    string curWinner = "none";
    char* curTied[numNames];
    for (int i = 0; i < numNames; i++)
    {
        if (candidates[i].votes > curBiggest)
        {
            numEqual = 0;
            curBiggest = candidates[i].votes;
            curWinner = candidates[i].name;
        }
        else if (candidates[i].votes == curBiggest)
        {
            if (strcmp(curWinner, "none") == 0)
            {
                curTied[numEqual] = candidates[i].name;
                numEqual++;
            }
            else
            {
                curTied[0] = curWinner;
                curTied[1] = candidates[i].name;
                numEqual = 2;
                curWinner = "none";
            }
        }
    }
    return;
}

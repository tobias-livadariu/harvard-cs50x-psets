#include <cs50.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool tempLock(int index);
bool checkCycles(int pathway[], int destinations[]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i == 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[rank[i]][rank[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    /* Giving pair count a value
    so it can be easily incremented
    later. */
    pair_count = 0;
    for (int i == 0; i < candidate_count; i++)
    {
        for (int j == 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                /* TODO: Check to see if using
                pair_count here messes up the logic. */
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    /* Initializing a variable to keep track
    of how many pairs have been sorted. */
    int numSorted = 0;

    /* Initializing a variable to hold the
    pair being swapped while swapping is occuring. */
    pair carrier;

    /* Making a for loop to iterate through
    all the pairs in the unsorted pairs array. */
    for (int i = 0; i < pair_count; i++)
    {
        int biggestVictory = 0;
        int locBiggestVictory = 0;
        for (int j = numSorted; j < pair_count; j++)
        {
            /* Defining a variable to hold the margin
            at which the current pairs' victor won*/
            int curVictory = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (curVictory > biggestVictory)
            {
                biggestVictory = curVictory;
                locBiggestVictory = j;
            }
        }

        /* Swapping the biggest victory with the
        first victory in accordance to the
        selection sort algorithm. */
        carrier = pairs[numSorted];
        pairs[numSorted] = pairs[locBiggestVictory];
        pairs[locBiggestVictory] = carrier;

        /* Incrementing the variable to keep track
        of how many pairs were sorted. */
        numSorted++;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!tempLock(i))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

/* Temporarily locking the index
to allow for the checkCycles() function
to check if a cycle has been formed. */
bool tempLock(int index)
{
    int winner = pairs[index].winner;
    int loser = pairs[index].loser;
    locked[winner][loser] = true;
    bool isCycle = checkCycles();
    locked[winner][loser] = false;

    /* Defining an array to hold the start points
    of the paths taken. */
    int pathway[candidate_count];
    for (int i == 0; i < candidate_count; i++)
    {
        pathway[i] = 0;
    }
    /* Defining an array variable to hold the
    upcoming candidate destinations of the search. */
    int maxNumDestinations = 
    int destinations[];
    if (isCycle(pathway, destinations))
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* Function that checks if the locked[][] 2D array
contains any edge cycles. */
bool checkCycles(int pathway[], int destinations[])
{

    return false;
}

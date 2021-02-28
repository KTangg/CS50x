#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
}
pair;

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
    // TODO
    // check the name in candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            //giving a index of candidate arrange by rank
            ranks[rank] = i;

            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // coming first is higher rank
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    //Checking all of record_preference if ij > ji = i more prefer than j
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            //record the result in pairs array
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }

            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    //looking for preference_number
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            //compare the preference
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                //create dummy to transfer data before overwritten
                pair dummy;
                dummy.winner = pairs[i].winner;
                dummy.loser = pairs[i].loser;

                //moving up
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;

                //moving down
                pairs[j].winner = dummy.winner;
                pairs[j].loser = dummy.loser;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        printf("%s win %s\n", candidates[pairs[i].winner], candidates[pairs[i].loser]);
        int limit = candidate_count - 1;
        for (int c = 0; c < candidate_count; c++)
        {
            for (int r = 0; r < candidate_count; r++)
            {
                if (locked[r][c] == true)
                {
                    limit -= 1;
                    break;
                }
            }
        }
        if (limit != 0)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            //if (locked[pairs[i].winner][pairs[i].loser] == true)
                //{
                    //printf("%s ---> %s\n",candidates[pairs[i].winner], candidates[pairs[i].loser]);
                //}
        }
    }
    //for (int i = 0; i < candidate_count; i++)
    //{
        //for (int j = 0; j < candidate_count; j++)
        //{
            //if (locked[i][j] == true)
                //{
                    //printf("%i %i is True\n", i, j);
                //}
            //else
                //{
                    //printf("%i %i is Fault\n", i, j);
                //}
        //}
    //}
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    //no true in candidate column
    for (int j = 0; j < candidate_count; j++)
    {
        int fault_count = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == false)
            {
                fault_count += 1;

                //printf("%s %i Fault \n", candidates[j], fault_count);
            }

            if (fault_count == candidate_count)
            {
                printf("%s\n", candidates[j]);
            }
        }
    }
    return;
}


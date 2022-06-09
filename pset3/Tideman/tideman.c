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
    int difference;
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
bool make_circle(int a, int b);
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
    for(int i = 0; i < candidate_count; i++){

        if(strcmp(candidates[i], name) == 0){

            ranks[i] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    int positionI;
    int positionJ;
    int compared_candidate;

    for(int i = 0; i < candidate_count; i++){

        positionI = 0;
        positionJ = 0;

        for(int j = 0; j < candidate_count; j++){

            //if j Ranked vote match candidate i, save candidate i's position in ranks
            if(ranks[j] == i){

                positionI = j;

             //if j Ranked vote match candidate j, save candidate j's position in ranks}
            }else if(ranks[j] == j){

                positionJ = j;
                compared_candidate = ranks[j];
            }
        }

        //Compare position of candidate i and j and update preferencces[i][j]
        if(positionI < positionJ){

                preferences[i][compared_candidate]++;
        }

    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    pair_count = 0;

    for(int i = 0; i < candidate_count; i++){

        for(int j = 0; j < candidate_count; j++){


            //If the pair has a defined winner add it to the pair array and move to the next position on that array
            if(preferences[i][j] > preferences[j][i]){

                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pairs[pair_count].difference = preferences[i][j] - preferences[j][i];

                pair_count++;

            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    //Bubble sort of the pair array
    int swap_counter;
    pair storage_pair;

    for(int i = 0; i < pair_count - 1; i++){

        swap_counter = 0;

        for(int j = i + 1; j <pair_count; j++){

            if(pairs[i].difference < pairs[j].difference){

                storage_pair = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = storage_pair;
                swap_counter++;

            }

        }

        //If no change have been made to the array leave the loop
        if(swap_counter == 0){

            break;

        }

    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i = 0; i < pair_count; i++){


        //if the winner of the previous pair lose the current pair the pair is not locked
        if(!make_circle(pairs[i].winner, pairs[i].loser)){

            locked[pairs[i].winner][pairs[i].loser] = true;

        }
    }
    return;
}


//Recursive function checking if a circle is created in lock_pairs
bool make_circle(int cycle_start, int loser)
{

    //Base case : if the loser is the cycle starter it will cause circle
    if(loser == cycle_start){

        return true;
    }

    //
    for (int i = 0; i < candidate_count; i++){

        if(locked[loser][i]){

            if(make_circle(cycle_start, i)){

                return true;
            }

        }

    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{

    for(int i = 0; i < candidate_count; i++){

        int arrow_count = 0;

        for(int j = 0; j < candidate_count; j++){

            if(locked[i][j]){

                arrow_count++;
            }
        }
        if(arrow_count == 0){

            printf("The winner is : %s\n", candidates[i]);
            break;
        }
    }
    return;
}


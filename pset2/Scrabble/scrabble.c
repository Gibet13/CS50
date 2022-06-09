#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

const int points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int computeScore(string s);
int main(void){

    //Get words from the two player
    string p1string = get_string("Player 1 :");
    string p2string = get_string("Player 2 :");

    printf("Player 1 Score : %i \n", computeScore(p1string));
    printf("Player 2 Score : %i \n", computeScore(p2string));

    //Compare the 2 words and print the result
    if(computeScore(p1string) > computeScore(p2string)){

        printf("Player 1 Wins ! \n");
    }
    else if(computeScore(p1string) < computeScore(p2string)){

        printf("Player 2 Wins ! \n");
    }
    else{printf("I's a Tie ! \n");}
};

//Convert each letter of the word into an int and add the corresponding amont of points to the score via the points array
int computeScore(string s){

    int n = strlen(s);
    int score = 0;
    int currentletter;

    for(int i = 0 ; i < n; i++){

        currentletter = toupper(s[i]) - 65;
        score += points[currentletter];
    }
    return score;
};
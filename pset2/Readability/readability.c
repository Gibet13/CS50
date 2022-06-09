#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>

void textparser(string text);

int main(void){

    //Get text from user
    string text = get_string("Text :");

    //Call parsing function
    textparser(text);

}

void textparser(string text){

    int l = strlen(text);
    int letters = 0;
    int words = 1;
    int sentences = 0;

    //Parse the word and count words letter and sentences depending on the character encountered
    for(int i = 0; i < l; i++){

        if(text[i] == ' '){
            words++;
        }else if(text[i] == '.'|| text[i] == '?' || text[i] == '!'){
            sentences++;
        }else if(isupper(text[i]) || islower(text[i])){
            letters++;
        }else{}
    }
    printf("\nLetters : %i \n", letters);
    printf("Words : %i \n", words);
    printf("Sentences : %i \n\n", sentences);

    //Get average number of letters and sentences per 100 words
    letters = letters * 100/words;
    sentences  = sentences * 100/words;

    //calculate the grade of the text with the Cordman-Liau formula
    float textgrade = 0.0588 * letters - 0.296 * sentences - 15.8;

    //Print the result
    if(textgrade < 1){
        printf("Grade 1 \n");
    }else if(textgrade > 16){
        printf("Grade 16+ \n");
    }else{
        printf("Grade %f \n", round(textgrade));
    }
}
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){
    float change = 0;
    int coins = 0;

    do{
        change = get_float("change owed :");
    }while(change < 0);

    int cents = round(change * 100);

    do{
        if(cents >= 25){
            cents -= 25;
            coins++;
        }else if(cents >= 10 & cents < 25){
            cents -= 10;
            coins++;
        }else if(cents >= 5 & cents < 10){
            cents -= 5;
            coins++;
        }else{
            cents -= 1;
            coins++;
        }
    }while(cents > 1);

    printf("%i coins \n", coins);
}
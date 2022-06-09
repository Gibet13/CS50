#include <stdio.h>
#include <cs50.h>

int growth(int a,int b)
{
    int n = 0;
    do{
        a = a + (a/3)-(a/4);
        n++;

    }while(a < b);
    return n;
}

int main(void)
{
    int startPop = 0;
    int endPop = 0;

    do{
        startPop = get_int("Start Population :");
        endPop = get_int("End Population :");
    }while(startPop < 9 || endPop < startPop);

    printf("%i years \n", growth(startPop, endPop));
}
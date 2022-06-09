#include <cs50.h>
#include <stdio.h>

void builder(int n)
    {
        for(int a = 0; a < n; a++){
            printf("#");
        };
    };
void spacer(int s)
    {
        for(int f = 0; f < s; f++){
            printf(" ");
        };
    };


int main(void)
{

    //Get pyramid's dimentions
    int pyramidH;

    do{
        pyramidH = get_int("Pyramid Height :");

    }while(pyramidH < 1 );


    //Display Pyramid

        int x = 0;
        int y = pyramidH;

        do{
            spacer(y);
            builder(x);
            printf(" ");
            builder(x);
            x++;
            y--;
            printf("\n");
        }while(x < pyramidH + 1);
}
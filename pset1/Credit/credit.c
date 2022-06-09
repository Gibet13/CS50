#include <stdio.h>
#include <cs50.h>

int lengthchk(long nmb){
    int n = 1;
    do{
        nmb = (nmb/10);
        n++;
    }while(nmb > 10);
    return n;
}

int checksum(long nmb, int n){

    int modchk = 0;
    int store = 0;
    long dplct = nmb;

    // grab every other digit, starting with the number’s second-to-last digit
    for(int x = 0; x < n; x++){
        nmb = nmb - (nmb%10);
        nmb = nmb / 10;

        store = (nmb%10)*2;

        //add those products’ digits (not the products themselves) together
        if(store > 10){

            modchk += store%10;
            modchk++;
        }else{
            modchk += store%10;
        }


        nmb = nmb / 10;
        if(nmb == 0){
            x = n;
        }
    }

    //add that sum to the sum of the digits that weren’t multiplied by 2
    for(int x = 0; x < n; x++){
        store = dplct%10;

        dplct = dplct - (dplct%10);
        dplct = dplct / 10;

        modchk += store%10;

        dplct = dplct / 10;
        if(dplct == 0){
            x = n;
        }
    }return modchk;
}

//Check first 2 digits
long checkfirst(long n){
    do{
        n = n - (n%10);
        n = n / 10;
    }while(n > 100);
    return n;
}


int main(void)
{
    // Get card number from user
    long crednmber = 0;
    do{
        crednmber = get_long("Credit Card Number :");
    }while(lengthchk(crednmber) < 13 || lengthchk(crednmber) > 16);

    printf("numbers length %i \n", lengthchk(crednmber));
    printf("first digits %li \n", checkfirst(crednmber));

    // Test for card number length match then for checksum
    if(lengthchk(crednmber) == 13 || lengthchk(crednmber) == 16){
        if((int)checkfirst(crednmber) > 51 || (int)checkfirst(crednmber) < 55){
            if((checksum(crednmber, lengthchk(crednmber))%10) == 0){
                printf("Valid MasterCard \n");
            }else{printf("Invalid \n");}

        }else if((int)checkfirst(crednmber) > 40 || (int)checkfirst(crednmber) < 49){
            if((checksum(crednmber, lengthchk(crednmber))%10) == 0){
                printf("Valid VISA \n");
            }else{printf("Invalid \n");}

        }else{printf("Invalid \n");}

    }else if(lengthchk(crednmber) == 15){
        if((int)checkfirst(crednmber) == 34 || (int)checkfirst(crednmber) == 37){
            if((checksum(crednmber, lengthchk(crednmber))%10) == 0){
                printf("Valid American Express \n");
            }else{printf("Invalid \n");}
        }
    }else{printf("Invalid \n");}

}
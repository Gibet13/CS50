#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[]){

    //Verify if there is the correct amount of argment argument  
    if(argc == 2){

        //Convert the string key into an int
        int key = atoi(argv[1]);
        //Receive text from the user
        string text = get_string("Enter Text : ");

        int l = strlen(text);
        int currentletter;


        for(int i = 0; i < l; i++){

            if(isupper(text[i])){
                //Convert uppercase end check for overflow
                text[i] += key%26;
                if(text[i] > 90){
                    text[i] -= 26;
                }
            }else if(islower(text[i])){
                //Convert lowercase end check for overflow
                text[i] += key%26;
                if(text[i] > 122){
                    text[i] -= 26;
                }
            }else{};
        }
        //Print the cypher text
        printf("New Text :  %s \n", text);
    }
    //Error message in case of invalid argument
    else{printf("Incorrect Argument \nplease use ./caesar key\n");}
}
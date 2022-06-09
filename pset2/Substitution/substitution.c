#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

//Prototype function
bool keycheck(string s);

int main(int argc, string argv[]){
    
    //Verify the amount of arguments and its length
    if(argc == 2 && strlen(argv[1]) == 26){

        if(keycheck(argv[1]) == true){
            
            //Get text from user imput 
            string text = get_string("Enter text : ");
            int l = strlen(text);

            for(int i = 0; i < l; i++){
                
                //Convert the  text string using the key while maintaining case
                if(isupper(text[i])){

                    int currentletter = toupper(text[i]) - 65;
                    text[i] = argv[1][currentletter];
                    text[i] = toupper(text[i]);

                }else if(islower(text[i])){

                    int currentletter = tolower(text[i]) - 97;
                    text[i] = argv[1][currentletter];
                    text[i] = tolower(text[i]);

                }else{}
            }
            printf("Cipher text : %s \n", text);

        }else{
            printf("key characters must all be alphabetical with no duplicate\n");
        }
    }
    else{printf("please use ./substitution key(26 character)\n");}
}


//Function checking if all character are alphabetical and if there is no duplicate
bool keycheck(string s){

    int l = strlen(s);

    bool validity;

    for(int i = 0; i < l; i++){
        
        //is it a letter ?
        if(isupper(s[i]) || islower(s[i])){
            for(int x = (i+1); x < l; x++){
                
                //is it repeted anywhere in the key ?
                if(isupper(s[i]) == isupper(s[x])){
                    validity = false;
                    x = l;
                    i = l;
                }
                else{validity = true;}
            }
        }else{
            validity = false;
            i = l;
        }
    }
    return validity;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int BLOCK = 512;


int main(int argc, char *argv[])
{

    if(argc != 2)
    {

        printf("Usage : ./recover image");
        return 1;
    }

    //open memory card
    FILE *memory_card = fopen(argv[1], "r");

    if(memory_card == NULL)
    {

        printf("Could not open %s \n", argv[1]);
        return 2;
    }


    uint8_t buffer[BLOCK];

    //Count the image recovered
    int image_count = 0;

    //Name of the file created
    char file_name[100];
    FILE *image_output;


    while(fread(buffer, sizeof(buffer), 1, memory_card) != 0)
    {

        //Copy block into 512 bytes buffer Array


        //Read first bytes to see if they match the header
        if(buffer[0] ==  0xff && buffer[1] ==  0xd8 &&  buffer[2] ==  0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            //update image count
            image_count++;

            //if a file was already open -> close it
            if (image_output != NULL)
            {
                fclose(image_output);

            }

            sprintf(file_name, "%03i.jpeg", image_count);

            image_output = fopen(file_name , "w");


            if(image_output == NULL)
            {

                printf("Could not create file\n");
                return 3;
            }

        }

        if (image_output != NULL)
        {
            fwrite(buffer, sizeof(char), BLOCK, image_output);

        }
    }

    fclose(image_output);
    fclose(memory_card);

    return 0;
}
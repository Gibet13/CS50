#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){

            RGBTRIPLE original = image[i][j];

            image[i][j].rgbtBlue = (original.rgbtRed +  original.rgbtGreen +  original.rgbtBlue) / 3;
            image[i][j].rgbtGreen = (original.rgbtRed + original.rgbtGreen + original.rgbtBlue) / 3;
            image[i][j].rgbtRed = (original.rgbtRed +  original.rgbtGreen + original.rgbtBlue) / 3;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){

        for(int j = 0; j < width/2; j++){

            RGBTRIPLE original = image[i][j];

            image[i][j].rgbtBlue = image[i][width-j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width-j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width-j].rgbtRed ;

            image[i][width-j].rgbtBlue = original.rgbtBlue;
            image[i][width-j].rgbtGreen = original.rgbtGreen;
            image[i][width-j].rgbtRed = original.rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    //Cooy of the image (so that the blurring is not polluted by previously blurred pixel)
    RGBTRIPLE copy_image[height][width];

    for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){

            copy_image[i][j] = image[i][j];
            }
        }

    for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){

            int counter = 0;
            int RedBuffer = 0;
            int GreenBuffer = 0;
            int BlueBuffer = 0;

            //Go through each of the neighbouring pixel, add their value to the buffer and update the counter
            for(int x = -1;x < 2; x++){

                for(int y = -1; y < 2; y++){

                    //If they are bigger that 0 and smaller than height or width they exist
                    if(i+x > 0 && i+x < height && j+y > 0 && j+y < width){

                        BlueBuffer += copy_image[i+x][j+y].rgbtBlue;
                        GreenBuffer += copy_image[i+x][j+y].rgbtGreen;
                        RedBuffer += copy_image[i+x][j+y].rgbtRed;

                        counter++;
                    }

                }
            }

            //update RGB value to the average of the neighbouring pixels
            image[i][j].rgbtBlue = round(BlueBuffer) / counter;
            image[i][j].rgbtGreen = round(GreenBuffer) / counter;
            image[i][j].rgbtRed = round(RedBuffer) / counter;
            }
        }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    //Cooy of the image (so that the blurring is not polluted by previously blurred pixel)
    RGBTRIPLE copy_image[height][width];

    for(int i = 0; i < height; i++)
    {

        for(int j = 0; j < width; j++)
        {

            copy_image[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {

        for(int j = 0; j < width; j++)
        {

            int GxRedBuffer = 0;
            int GxGreenBuffer = 0;
            int GxBlueBuffer = 0;

            int GyRedBuffer = 0;
            int GyGreenBuffer = 0;
            int GyBlueBuffer = 0;

            //Go through each of the neighbouring pixel, add their value to the buffer and update the counter
            for(int x = -1;x < 2; x++)
            {

                for(int y = -1; y < 2; y++)
                {

                    //If they are bigger that 0 and smaller than height or width they exist
                    if(i+x > 0 && i+x < height && j+y > 0 && j+y < width)
                    {

                        //
                        if (y == -1 && x != 0)
                        {
                            GxBlueBuffer += -1 * (copy_image[i+x][j+y].rgbtBlue);
                            GxGreenBuffer += -1 * (copy_image[i+x][j+y].rgbtGreen);
                            GxRedBuffer += -1 * (copy_image[i+x][j+y].rgbtRed);

                        }
                        if(y == -1 && x == 0){


                            GxBlueBuffer += -2 * (copy_image[i+x][j+y].rgbtBlue);
                            GxGreenBuffer += -2 * (copy_image[i+x][j+y].rgbtGreen);
                            GxRedBuffer += -2 * (copy_image[i+x][j+y].rgbtRed);

                        }
                        if (y == 1 && x != 0)
                        {
                            GxBlueBuffer += (copy_image[i+x][j+y].rgbtBlue);
                            GxGreenBuffer += (copy_image[i+x][j+y].rgbtGreen);
                            GxRedBuffer += (copy_image[i+x][j+y].rgbtRed);

                        }
                        if(y == 1 && x == 0){


                            GxBlueBuffer += 2 * (copy_image[i+x][j+y].rgbtBlue);
                            GxGreenBuffer += 2 * (copy_image[i+x][j+y].rgbtGreen);
                            GxRedBuffer += 2 * (copy_image[i+x][j+y].rgbtRed);

                        }
                    }
                }
            }

            for(int x = -1;x < 2; x++)
            {

                for(int y = -1; y < 2; y++)
                {

                    //If they are bigger that 0 and smaller than height or width they exist
                    if(i+x > 0 && i+x < height && j+y > 0 && j+y < width)
                    {

                        if (y != 0 && x == -1)
                        {
                            GyBlueBuffer += -1 * (copy_image[i+x][j+y].rgbtBlue);
                            GyGreenBuffer += -1 * (copy_image[i+x][j+y].rgbtGreen);
                            GyRedBuffer += -1 * (copy_image[i+x][j+y].rgbtRed);

                        }
                        if(y == 0 && x == -1){


                            GyBlueBuffer += -2 * (copy_image[i+x][j+y].rgbtBlue);
                            GyGreenBuffer += -2 * (copy_image[i+x][j+y].rgbtGreen);
                            GyRedBuffer += -2 * (copy_image[i+x][j+y].rgbtRed);

                        }
                        if (y != 0 && x == 1)
                        {
                            GyBlueBuffer += (copy_image[i+x][j+y].rgbtBlue);
                            GyGreenBuffer += (copy_image[i+x][j+y].rgbtGreen);
                            GyRedBuffer += (copy_image[i+x][j+y].rgbtRed);

                        }
                        if(y == 0 && x == 1){


                            GyBlueBuffer += 2 * (copy_image[i+x][j+y].rgbtBlue);
                            GyGreenBuffer += 2 * (copy_image[i+x][j+y].rgbtGreen);
                            GyRedBuffer += 2 * (copy_image[i+x][j+y].rgbtRed);

                        }
                    }
                }
            }

            //update RGB value to the average of the neighbouring pixels
            image[i][j].rgbtBlue = sqrt((GxBlueBuffer * GxBlueBuffer) + (GyBlueBuffer * GyBlueBuffer));
            image[i][j].rgbtGreen = sqrt((GxGreenBuffer * GxGreenBuffer) + (GyGreenBuffer * GyGreenBuffer));
            image[i][j].rgbtRed = sqrt((GxRedBuffer * GxRedBuffer) + (GyRedBuffer * GyRedBuffer));

            if(image[i][j].rgbtBlue > 255)
                {image[i][j].rgbtBlue = 255;}

            if(image[i][j].rgbtBlue < 0)
                {image[i][j].rgbtBlue = 0;}


            if(image[i][j].rgbtGreen > 255)
                {image[i][j].rgbtGreen = 255;}

            if(image[i][j].rgbtGreen < 0)
                {image[i][j].rgbtGreen = 0;}


            if(image[i][j].rgbtRed > 255)
                {image[i][j].rgbtRed = 255;}

            if(image[i][j].rgbtRed < 0)
                {image[i][j].rgbtRed = 0;}
        }
    }
    return;
}

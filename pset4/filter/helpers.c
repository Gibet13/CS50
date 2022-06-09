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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){

            int blue = image[i][j].rgbtBlue;
            int red  = image[i][j].rgbtRed;
            int green  = image[i][j].rgbtGreen;
            
            float sepia_blue = round(.272 * red + .534 *green + .131 * blue);
            float sepia_green = round(.349 * red + .686 * green + .168 * blue);
            float sepia_red = round(.393 * red + .769 * green + .189 * blue);
            
            //
            if(sepia_blue > 255){

                sepia_blue = 255;

            }
            if(sepia_green > 255){

                sepia_green = 255;

            }
            if(sepia_red > 255){

                sepia_red = 255;
            }

            image[i][j].rgbtBlue = round(sepia_blue);
            image[i][j].rgbtGreen = round(sepia_green);
            image[i][j].rgbtRed = round(sepia_red);

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

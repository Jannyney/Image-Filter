
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avr = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avr;
            image[i][j].rgbtGreen = avr;
            image[i][j].rgbtBlue = avr;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sred = round((image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) + (image[i][j].rgbtBlue * 0.189));
            int sgreen = round((image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) + (image[i][j].rgbtBlue * 0.168));
            int sblue = round((image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) + (image[i][j].rgbtBlue * 0.131));
            // Check if the number exceeds 255
            if (sred > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sred;
            }

            if (sgreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sgreen;
            }

            if (sblue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sblue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    if (width % 2 == 0)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j <= (width / 2) - 1; j++)
            {
                // store left side value
                int tmpred = image[i][j].rgbtRed;
                int tmpgreen = image[i][j].rgbtGreen;
                int tmpblue = image[i][j].rgbtBlue;
    
                // left side
                {
                    image[i][j].rgbtRed =  image[i][width - 1 - j].rgbtRed;
                    image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
                    image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
                }
    
                // right side
                image[i][width - 1 - j].rgbtRed = tmpred;
                image[i][width - 1 - j].rgbtGreen = tmpgreen;
                image[i][width - 1 - j].rgbtBlue = tmpblue;
    
            }
        }
    }
    if (width % 2 != 0)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < (width / 2); j++)
            {
                // store left side value
                int tmpred = image[i][j].rgbtRed;
                int tmpgreen = image[i][j].rgbtGreen;
                int tmpblue = image[i][j].rgbtBlue;
    
                // left side
                {
                    image[i][j].rgbtRed =  image[i][width - 1 - j].rgbtRed;
                    image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
                    image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
                }
    
                // right side
                image[i][width - 1 - j].rgbtRed = tmpred;
                image[i][width - 1 - j].rgbtGreen = tmpgreen;
                image[i][width - 1 - j].rgbtBlue = tmpblue;
    
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    float sum_blue;
    float sum_green;
    float sum_red;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //corner
            //corner on the top left
            if ((i == 0) && (j == 0))
            {
                sum_red   = temp[i][j].rgbtRed   + temp[i][j + 1].rgbtRed   + temp[i + 1][j].rgbtRed   + temp[i + 1][j + 1].rgbtRed;
                sum_green = temp[i][j].rgbtGreen + temp[i][j + 1].rgbtGreen + temp[i + 1][j].rgbtGreen + temp[i + 1][j + 1].rgbtGreen;
                sum_blue  = temp[i][j].rgbtBlue  + temp[i][j + 1].rgbtBlue  + temp[i + 1][j].rgbtBlue  + temp[i + 1][j + 1].rgbtBlue;


                image[i][j].rgbtRed = round(sum_red / 4);
                image[i][j].rgbtGreen = round(sum_green / 4);
                image[i][j].rgbtBlue = round(sum_blue / 4);
            }

            //corner on the top right
            else if ((i == 0) && (j == (width - 1)))
            {

                sum_red   = temp[i][j].rgbtRed   + temp[i][j - 1].rgbtRed   + temp[i + 1][j].rgbtRed   + temp[i + 1][j - 1].rgbtRed;
                sum_green = temp[i][j].rgbtGreen + temp[i][j - 1].rgbtGreen + temp[i + 1][j].rgbtGreen + temp[i + 1][j - 1].rgbtGreen;
                sum_blue  = temp[i][j].rgbtBlue  + temp[i][j - 1].rgbtBlue  + temp[i + 1][j].rgbtBlue  + temp[i + 1][j - 1].rgbtBlue;

                image[i][j].rgbtRed = round(sum_red / 4.0);
                image[i][j].rgbtGreen = round(sum_green / 4.0);
                image[i][j].rgbtBlue = round(sum_blue / 4.0);
            }


            //corner on the bottom left
            else if (i == (height - 1) && (j == 0))
            {
                sum_red   = temp[i][j].rgbtRed   + temp[i - 1][j].rgbtRed   + temp[i][j + 1].rgbtRed   + temp[i - 1][j + 1].rgbtRed;
                sum_green = temp[i][j].rgbtGreen + temp[i - 1][j].rgbtGreen + temp[i][j + 1].rgbtGreen + temp[i - 1][j + 1].rgbtGreen;
                sum_blue  = temp[i][j].rgbtBlue  + temp[i - 1][j].rgbtBlue  + temp[i][j + 1].rgbtBlue  + temp[i - 1][j + 1].rgbtBlue;

                image[i][j].rgbtRed = round(sum_red / 4.0);
                image[i][j].rgbtGreen = round(sum_green / 4.0);
                image[i][j].rgbtBlue = round(sum_blue / 4.0);
            }

            //corner on the bottom right
            else if (i == (height - 1) && j == (width - 1))
            {
                sum_red = temp[i][j].rgbtRed + temp[i - 1][j].rgbtRed + temp[i][j - 1].rgbtRed + temp[i - 1][j - 1].rgbtRed;
                sum_green = temp[i][j].rgbtGreen + temp[i - 1][j].rgbtGreen + temp[i][j - 1].rgbtGreen + temp[i - 1][j - 1].rgbtGreen;
                sum_blue  = temp[i][j].rgbtBlue  + temp[i - 1][j].rgbtBlue  + temp[i][j - 1].rgbtBlue  + temp[i - 1][j - 1].rgbtBlue;

                image[i][j].rgbtRed = round(sum_red / 4.0);
                image[i][j].rgbtGreen = round(sum_green / 4.0);
                image[i][j].rgbtBlue = round(sum_blue / 4.0);
            }

            //edge
            //top edge
            else if ((i == 0 && j > 0) && (i == 0 && j < width - 1))
            {
                sum_red   = temp[i][j].rgbtRed   + temp[i][j - 1].rgbtRed   + temp[i + 1][j - 1].rgbtRed   + temp[i + 1][j].rgbtRed   + temp[i][j +
                            1].rgbtRed + temp[i + 1][j + 1].rgbtRed;
                sum_green = temp[i][j].rgbtGreen + temp[i][j - 1].rgbtGreen + temp[i + 1][j - 1].rgbtGreen + temp[i + 1][j].rgbtGreen + temp[i][j +
                            1].rgbtGreen + temp[i + 1][j + 1].rgbtGreen;
                sum_blue  = temp[i][j].rgbtBlue  + temp[i][j - 1].rgbtBlue  + temp[i + 1][j - 1].rgbtBlue  + temp[i + 1][j].rgbtBlue  + temp[i][j +
                            1].rgbtBlue + temp[i + 1][j + 1].rgbtBlue;

                image[i][j].rgbtRed = round(sum_red / 6.0);
                image[i][j].rgbtGreen = round(sum_green / 6.0);
                image[i][j].rgbtBlue = round(sum_blue / 6.0);
            }

            //left edge
            else if ((i > 0 && j == 0) && (i < (height - 1) && j == 0))
            {
                sum_red = temp[i][j].rgbtRed + temp[i - 1][j].rgbtRed + temp[i - 1][j + 1].rgbtRed + temp[i][j + 1].rgbtRed + temp[i + 1][j].rgbtRed
                          + temp[i + 1][j + 1].rgbtRed;
                sum_green = temp[i][j].rgbtGreen + temp[i - 1][j].rgbtGreen + temp[i - 1][j + 1].rgbtGreen + temp[i][j + 1].rgbtGreen + temp[i +
                            1][j].rgbtGreen + temp[i + 1][j + 1].rgbtGreen;
                sum_blue = temp[i][j].rgbtBlue + temp[i - 1][j].rgbtBlue + temp[i - 1][j + 1].rgbtBlue + temp[i][j + 1].rgbtBlue + temp[i +
                           1][j].rgbtBlue + temp[i + 1][j + 1].rgbtBlue;

                image[i][j].rgbtRed = round(sum_red / 6.0);
                image[i][j].rgbtGreen = round(sum_green / 6.0);
                image[i][j].rgbtBlue = round(sum_blue / 6.0);
            }

            //right edge
            else if ((i > 0 && j == (width - 1)) && (i < (height - 1) && j == (width - 1)))
            {
                sum_red = temp[i][j].rgbtRed + temp[i - 1][j - 1].rgbtRed + temp[i - 1][j].rgbtRed + temp[i][j - 1].rgbtRed + temp[i + 1][j -
                          1].rgbtRed + temp[i + 1][j].rgbtRed;
                sum_green = temp[i][j].rgbtGreen + temp[i - 1][j - 1].rgbtGreen + temp[i - 1][j].rgbtGreen + temp[i][j - 1].rgbtGreen + temp[i +
                            1][j - 1].rgbtGreen + temp[i + 1][j].rgbtGreen;
                sum_blue = temp[i][j].rgbtBlue + temp[i - 1][j - 1].rgbtBlue + temp[i - 1][j].rgbtBlue + temp[i][j - 1].rgbtBlue + temp[i + 1][j -
                           1].rgbtBlue + temp[i + 1][j].rgbtBlue;

                image[i][j].rgbtRed = round(sum_red / 6.0);
                image[i][j].rgbtGreen = round(sum_green / 6.0);
                image[i][j].rgbtBlue = round(sum_blue / 6.0);
            }
            //just dont know what to comment
            //just dont know what to comment
            //just dont know what to comment
            //just dont know what to comment
            //bottom edge
            else if ((i == (height - 1) && j > 0) && (i == (height - 1) && j < (width - 1)))
            {
                sum_red = temp[i][j].rgbtRed + temp[i][j - 1].rgbtRed + temp[i][j + 1].rgbtRed + temp[i - 1][j].rgbtRed + temp[i - 1][j + 1].rgbtRed
                          + temp[i - 1][j - 1].rgbtRed;
                sum_green = temp[i][j].rgbtGreen + temp[i][j - 1].rgbtGreen + temp[i][j + 1].rgbtGreen + temp[i - 1][j].rgbtGreen + temp[i - 1][j +
                            1].rgbtGreen + temp[i - 1][j - 1].rgbtGreen;
                sum_blue = temp[i][j].rgbtBlue + temp[i][j - 1].rgbtBlue + temp[i][j + 1].rgbtBlue + temp[i - 1][j].rgbtBlue + temp[i - 1][j +
                           1].rgbtBlue + temp[i - 1][j - 1].rgbtBlue;

                image[i][j].rgbtRed = round(sum_red / 6.0);
                image[i][j].rgbtGreen = round(sum_green / 6.0);
                image[i][j].rgbtBlue = round(sum_blue / 6.0);
            }

            //middle
            else
            {
                sum_red = temp[i - 1][j - 1].rgbtRed + temp[i - 1][j].rgbtRed + temp[i - 1][j + 1].rgbtRed + temp[i][j - 1].rgbtRed +
                          temp[i][j].rgbtRed + temp[i][j + 1].rgbtRed + temp[i + 1][j - 1].rgbtRed + temp[i + 1][j].rgbtRed + temp[i + 1][j + 1].rgbtRed;
                sum_green = temp[i - 1][j - 1].rgbtGreen + temp[i - 1][j].rgbtGreen + temp[i - 1][j + 1].rgbtGreen + temp[i][j - 1].rgbtGreen + 
                            temp[i][j].rgbtGreen + temp[i][j + 1].rgbtGreen + temp[i + 1][j - 1].rgbtGreen + temp[i + 1][j].rgbtGreen + temp[i + 1][j +
                                    1].rgbtGreen;
                sum_blue = temp[i - 1][j - 1].rgbtBlue + temp[i - 1][j].rgbtBlue + temp[i - 1][j + 1].rgbtBlue + temp[i][j - 1].rgbtBlue +
                           temp[i][j].rgbtBlue + 
                           temp[i][j + 1].rgbtBlue + temp[i + 1][j - 1].rgbtBlue + temp[i + 1][j].rgbtBlue + temp[i + 1][j + 1].rgbtBlue;

                image[i][j].rgbtRed = round(sum_red / 9.0);
                image[i][j].rgbtGreen = round(sum_green / 9.0);
                image[i][j].rgbtBlue = round(sum_blue / 9.0);
            }
        }
    }

    return;
}

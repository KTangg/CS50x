#include <stdio.h>
#include "helpers.h"
#include <math.h>
#include <stddef.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //looping down the height
    for (int h = 0; h < height; h++)
    {
        //looping to the right
        for (int w = 0; w < width; w++)
        {
            //get rgb color from the pixel

            int red = image[h][w].rgbtRed;
            int green = image[h][w].rgbtGreen;
            int blue = image[h][w].rgbtBlue;

            //average red green blue
            float avg_rgb = (red + green + blue) / 3.0;

            //check the tone(black or white)
            if (avg_rgb >= 0 && avg_rgb <= 255)
            {
                image[h][w].rgbtRed = round(avg_rgb);
                image[h][w].rgbtGreen = round(avg_rgb);
                image[h][w].rgbtBlue = round(avg_rgb);
            }

            else
            {
                printf("Invalid RGB number in Grayscale.");
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //looping down the height
    for (int h = 0; h < height; h++)
    {
        //looping to the right
        for (int w = 0; w < (width + 1) / 2; w++)
        {
            //Create rgb buffer
            int red = image[h][w].rgbtRed;
            int green = image[h][w].rgbtGreen;
            int blue = image[h][w].rgbtBlue;

            //Swap
            image[h][w].rgbtRed = image[h][width - w - 1].rgbtRed;
            image[h][w].rgbtGreen = image[h][width - w - 1].rgbtGreen;
            image[h][w].rgbtBlue = image[h][width - w - 1].rgbtBlue;

            image[h][width - w - 1 ].rgbtRed  = red;
            image[h][width - w - 1].rgbtGreen = green;
            image[h][width - w - 1].rgbtBlue = blue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];
    //looping down the height
    for (int h = 0; h < height; h++)
    {
        //looping to the right
        for (int w = 0; w < width; w++)
        {
            //setting new summary value
            int red = 0;
            int green = 0;
            int blue = 0;
            int pixel_count = 0;

            //looping for square height
            for (int i = -1; i < 2; i++)
            {
                //looping for square width
                for (int j = -1; j < 2; j++)
                {
                    //checking the pixel in the image?
                    if (h + i >= 0 && h + i < height && w + j >= 0 && w + j < width)
                    {
                        //get rgb color from pixel around
                        red += image[h + i][w + j].rgbtRed;
                        green += image[h + i][w + j].rgbtGreen;
                        blue += image[h + i][w + j].rgbtBlue;
                        pixel_count += 1;
                    }
                }
            }

            //get the average
            float avg_r = red / (float)pixel_count;
            float avg_g = green / (float)pixel_count;
            float avg_b = blue / (float)pixel_count;

            //adding value to buffer
            buffer[h][w].rgbtRed = round(avg_r);
            buffer[h][w].rgbtGreen = round(avg_g);
            buffer[h][w].rgbtBlue = round(avg_b);
        }
    }

    for (int h = 0; h < height; h++)
    {
        //looping to the right
        for (int w = 0; w < width; w++)
        {
            //painting the image
            image[h][w].rgbtRed = buffer[h][w].rgbtRed;
            image[h][w].rgbtGreen = buffer[h][w].rgbtGreen;
            image[h][w].rgbtBlue = buffer[h][w].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE buffer[height][width];

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //looping down the height
    for (int h = 0; h < height; h++)
    {
        //looping to the right
        for (int w = 0; w < width; w++)
        {
            //setting new summary value
            float redX = 0;
            float greenX = 0;
            float blueX = 0;
            float redY = 0;
            float greenY = 0;
            float blueY = 0;

            //looping for square height
            for (int i = -1; i < 2; i++)
            {
                //looping for square width
                for (int j = -1; j < 2; j++)
                {
                    //checking the pixel in the image?
                    if (h + i >= 0 && h + i < height && w + j >= 0 && w + j < width)
                    {
                        //Useing Sobel operation
                        redX += image[h + i][w + j].rgbtRed * Gx[i + 1][j + 1];
                        greenX += image[h + i][w + j].rgbtGreen * Gx[i + 1][j + 1];
                        blueX += image[h + i][w + j].rgbtBlue * Gx[i + 1][j + 1];

                        redY += image[h + i][w + j].rgbtRed * Gy[i + 1][j + 1];
                        greenY += image[h + i][w + j].rgbtGreen * Gy[i + 1][j + 1];
                        blueY += image[h + i][w + j].rgbtBlue * Gy[i + 1][j + 1];
                    }
                }
            }

            //get the combination
            float red = 0;
            float green = 0;
            float blue = 0;

            red = sqrt(pow(redX, 2) + pow(redY, 2));
            green = sqrt(pow(greenX, 2) + pow(greenY, 2));
            blue = sqrt(pow(blueX, 2) + pow(blueY, 2));

            if (red > 255)
            {
                red = 255;
            }


            if (green > 255)
            {
                green = 255;
            }

            if (blue > 255)
            {
                blue = 255;
            }

            //adding value to buffer
            buffer[h][w].rgbtRed = round(red);
            buffer[h][w].rgbtGreen = round(green);
            buffer[h][w].rgbtBlue = round(blue);
        }
    }

    for (int h = 0; h < height; h++)
    {
        //looping to the right
        for (int w = 0; w < width; w++)
        {
            //painting the image
            image[h][w].rgbtRed = buffer[h][w].rgbtRed;
            image[h][w].rgbtGreen = buffer[h][w].rgbtGreen;
            image[h][w].rgbtBlue = buffer[h][w].rgbtBlue;
        }
    }
    return;
}


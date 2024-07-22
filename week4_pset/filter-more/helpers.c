#include <stdlib.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Defining a variable to hold the average of RGB values for each pixel
            float averageRGB = 0.0;
            averageRGB += image[i][j].rgbtRed;
            averageRGB += image[i][j].rgbtGreen;
            averageRGB += image[i][j].rgbtBlue;
            averageRGB /= 3;
            int intAverageRBG = (int) round(averageRGB);
            image[i][j].rgbtRed = intAverageRBG;
            image[i][j].rgbtGreen = intAverageRBG;
            image[i][j].rgbtBlue = intAverageRBG;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    /* Defining a container variable to make the
    switch easier. */
    RGBTRIPLE *tempContainer = malloc(sizeof(RGBTRIPLE) * width);

    // Iterating through every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempContainer[j] = image[i][j];
        }
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempContainer[(width - 1) - j].rgbtRed;
            image[i][j].rgbtGreen = tempContainer[(width - 1) - j].rgbtGreen;
            image[i][j].rgbtBlue = tempContainer[(width - 1) - j].rgbtBlue;
        }
    }
    free(tempContainer);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Making a temporary copy of the image
    RGBTRIPLE *imageCopy = malloc(sizeof(RGBTRIPLE) * (height * width));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i * width + j] = image[i][j];
        }
    }

    // Iterating through every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* Defining variables to hold the
            blurred values. */
            int blurredAverageRed = 0;
            int blurredAverageGreen = 0;
            int blurredAverageBlue = 0;
            /* Defining a variable to hold the
            number of values to average. */
            int numToAverage = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                // checking if outside bounds
                if (k < 0 || k >= height)
                {
                    continue;
                }
                for (int l = j - 1; l <= j + 1; l++)
                {
                    // checking if outside bounds
                    if (l < 0 || l >= width)
                    {
                        continue;
                    }
                    blurredAverageRed += imageCopy[k * width + l].rgbtRed;
                    blurredAverageGreen += imageCopy[k * width + l].rgbtGreen;
                    blurredAverageBlue += imageCopy[k * width + l].rgbtBlue;
                    numToAverage++;
                }
            }
            blurredAverageRed /= numToAverage;
            blurredAverageGreen /= numToAverage;
            blurredAverageBlue /= numToAverage;

            // Assigning blurred color values
            image[i][j].rgbtRed = blurredAverageRed;
            image[i][j].rgbtGreen = blurredAverageGreen;
            image[i][j].rgbtBlue = blurredAverageBlue;
        }
    }
    free(imageCopy);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Defining the 2D kernels array
    int kernelGx[3][3] = {{-1, 0, 1},
                        {-2, 0, 2},
                        {-1, 0, 1}};
    int kernelGy[3][3] = {{-1, -2, -1},
                        {0, 0, 0},
                        {1, 2, 1}};
    // Making a temporary copy of the image
    RGBTRIPLE *imageCopy = malloc(sizeof(RGBTRIPLE) * (height * width));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i * width + j] = image[i][j];
        }
    }

    // Iterating through every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* Determining if the pixel lies on
            the image's border. */
            bool isOnTopEdge = false;
            bool isOnBottomEdge = false;
            bool isOnLeftEdge = false;
            bool isOnRightEdge = false;
            if (i == 0)
            {
                isOnTopEdge = true;
            }
            else if (i == (height - 1))
            {
                isOnBottomEdge = true;
            }
            if (j == 0)
            {
                isOnLeftEdge = true;
            }
            else if (j == (width - 1))
            {
                isOnRightEdge = true;
            }

            /* Defining variables to hold the
            channel values. */
            int multiplierGx = 0;
            int multiplierGy = 0;
            int redGx = 0;
            int redGy = 0;
            int red = 0;
            int greenGx = 0;
            int greenGy = 0;
            int green = 0;
            int blueGx = 0;
            int blueGy = 0;
            int blue = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (isOnTopEdge )

                    /* Setting the value of the
                    multipliers. */
                    multiplierGx = kernelGx[k - (i - 1)][l - (j - 1)];
                    multiplierGy = kernelGy[k - (i - 1)][l - (j - 1)];

                    /* Setting the values of the
                    Gx colors. */
                    redGx += multiplierGx * imageCopy[k * width + l].rgbtRed;
                    greenGx += multiplierGx * imageCopy[k * width + l].rgbtGreen;
                    blueGx += multiplierGx * imageCopy[k * width + l].rgbtBlue;
                    /* Setting the values of the
                    Gy colors. */
                    redGy += multiplierGy * imageCopy[k * width + l].rgbtRed;
                    greenGy += multiplierGy * imageCopy[k * width + l].rgbtGreen;
                    blueGy += multiplierGy * imageCopy[k * width + l].rgbtBlue;

                    /* Finding the overall color
                    values. */
                    red = (int) sqrt(pow(redGx, 2) + pow(redGy, 2));
                    green = (int) sqrt(pow(greenGx, 2) + pow(greenGy, 2));
                    blue = (int) sqrt(pow(blueGx, 2) + pow(blueGy, 2));

                    /* Checking to see if red, green, and blue
                    are all within the acceptable value range*/
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
                }
            }
            // Assigning edged color values
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    free(imageCopy);
    return;
}

#include <stdlib.h>
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
            int averageRGB = 0;
            averageRGB += image[i][j].rgbtRed;
            averageRGB += image[i][j].rgbtGreen;
            averageRGB += image[i][j].rgbtBlue;
            averageRGB /= 3;
            image[i][j].rgbtRed = averageRGB;
            image[i][j].rgbtGreen = averageRGB;
            image[i][j].rgbtBlue = averageRGB;
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
            imageCopy[i][j] = image[i][j];
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
            int numToAverage = 9;
            for (int k = i - 1; k <= i + 1; k++)
            {
                // checking if outside bounds
                if (k < 0 || k >= height)
                {
                    numToAverage -= 1;
                    continue;
                }
                for (int l = j - 1; l <= j + 1; j++)
                {
                    // checking if outside bounds
                    if (l < 0 || l >= width)
                    {
                        numToAverage -= 1;
                        continue;
                    }
                    blurredAverageRed += imageCopy[k][l].rgbtRed;
                    blurredAverageGreen += imageCopy[k][l].rgbtGreen;
                    blurredAverageBlue += imageCopy[k][l].rgbtBlue;
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
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

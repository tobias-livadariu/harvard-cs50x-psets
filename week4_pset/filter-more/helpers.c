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
            float blurredAverageRed = 0;
            float blurredAverageGreen = 0;
            float blurredAverageBlue = 0;
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
            int intBlurredAverageRed = (int) round(blurredAverageRed);
            int intBlurredAverageGreen = (int) round(blurredAverageGreen);
            int intBlurredAverageBlue = (int) round(blurredAverageBlue);

            image[i][j].rgbtRed = intBlurredAverageRed;
            image[i][j].rgbtGreen = intBlurredAverageGreen;
            image[i][j].rgbtBlue = intBlurredAverageBlue;
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
            /* Defining variables to hold the
            channel values. */
            int multiplierGx = 0;
            int multiplierGy = 0;
            int redGx = 0;
            int redGy = 0;
            float red = 0.0;
            int intRed = 0;
            int greenGx = 0;
            int greenGy = 0;
            float green = 0.0;
            int intGreen = 0;
            int blueGx = 0;
            int blueGy = 0;
            float blue = 0.0;
            int intBlue = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    /* Determining if the pixel lies on
                    the image's border. */
                    if ((k < 0) || (k >= height) || (l < 0) || (l >= width))
                    {
                        /* If pixel being accessed
                        is out of bounds, skip this iteration. */
                        continue;
                    }

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
                    red = sqrt(pow(redGx, 2) + pow(redGy, 2));
                    green = sqrt(pow(greenGx, 2) + pow(greenGy, 2));
                    blue = sqrt(pow(blueGx, 2) + pow(blueGy, 2));

                    /* Rounding the values. */
                    intRed = (int) round(red);
                    intGreen = (int) round(green);
                    intBlue = (int) round(blue);

                    /* Checking to see if red, green, and blue
                    are all within the acceptable value range*/
                    if (intRed > 255)
                    {
                        intRed = 255;
                    }
                    if (intGreen > 255)
                    {
                        intGreen = 255;
                    }
                    if (intBlue > 255)
                    {
                        intBlue = 255;
                    }
                }
            }
            // Assigning edged color values
            image[i][j].rgbtRed = intRed;
            image[i][j].rgbtGreen = intGreen;
            image[i][j].rgbtBlue = intBlue;
        }
    }
    free(imageCopy);
    return;
}

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
    // Iterating through every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j]
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

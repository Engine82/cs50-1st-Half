#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each pixel in each row
        for (int j = 0; j < width; j++)
        {
            // Change color if not white
            if (image[i][j].rgbtBlue != 255 && image[i][j].rgbtGreen != 255 && image[i][j].rgbtRed != 255)
            {
                image[i][j].rgbtBlue = 255;
                image[i][j].rgbtGreen = 255;
                image[i][j].rgbtRed = 0;
            }
        }
    }
}

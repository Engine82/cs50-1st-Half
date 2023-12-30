#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each pixel in each row, from L to R
        for (int j = 0; j < width; j++)
        {
            // Get average of color values, and set each to the average
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Save original color values (temporarily)
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;

            int original[] = {originalBlue, originalGreen, originalRed};

            // Create sepia values for each RGB
            int sepiaBlue = round((0.272 * originalRed) + (0.534 * originalGreen) + (0.131 * originalBlue));
            int sepiaGreen = round((0.349 * originalRed) + (0.686 * originalGreen) + (0.168 * originalBlue));
            int sepiaRed = round((0.393 * originalRed) + (0.769 * originalGreen) + (0.189 * originalBlue));

            // Cap values at 0xff/255
            int sepia[] = {sepiaBlue, sepiaGreen, sepiaRed};

            for (int k = 0; k < 3; k++)
            {
                if (sepia[k] > 255)
                {
                    sepia[k] = 255;
                }
            }

            // Save sepia values in place of original values
            image[i][j].rgbtBlue = sepia[0];
            image[i][j].rgbtGreen = sepia[1];
            image[i][j].rgbtRed = sepia[2];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create placeholder variable
    RGBTRIPLE tmp[width];

    // Loop through each row
    for (int i = 0; i < height; i++)
    {
        // Loop through each pixel and copy into temporary array
        for (int j = 0; j < width; j++)
        {
            tmp[j] = image[i][j];
        }

        // Copy image in reverse back into original file
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[(width - j - 1)];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create placeholder variable
    RGBTRIPLE tmp[height][width];

    // Loop through each row
    for (int i = 0; i < height; i++)
    {
        // Loop through each pixel in that row and copy into temporary array
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    // Loop through each row's pixel, to access each pixel to be blurred.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Create integers for sum of each color value, and a counter (must be float for division calculations uuuuuugghh)
            int sBlue = 0;
            int sGreen = 0;
            int sRed = 0;
            float count = 0.00;

            // Loop through each pixel in box contributing for blurring
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    // Get coordinates of current pixel in box by starting with the initial pixel (i, j) and adding x/y, which will access the pixels around it
                    int currentx = i + x;
                    int currenty = j + y;

                    // Exclude calculations for pixels outside the boundaries of the image (acount for corners/edges) with if statement
                    if (currentx < 0 || currentx >= height || currenty < 0 || currenty >= width)
                    {
                        continue;
                    }

                    // Add current grid pixel to total count and add one to the counter.
                    sRed += image[currentx][currenty].rgbtRed;
                    sGreen += image[currentx][currenty].rgbtGreen;
                    sBlue += image[currentx][currenty].rgbtBlue;

                    count++;
                }
            }

            // Average RGB values into temporary image struct
            tmp[i][j].rgbtBlue = round(sBlue / count);
            tmp[i][j].rgbtGreen = round(sGreen / count);
            tmp[i][j].rgbtRed = round(sRed / count);
        }
    }

    // Copy temporary image to original image file.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}

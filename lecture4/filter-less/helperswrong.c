    // Create placeholder variable
    RGBTRIPLE copy[height][width];

    // Loop through each row
    for (int i = 0; i < height; i++)
    {
        // Loop through each pixel in that row and copy into temporary array
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Loop through each row and column, to access each pixel to be blurred.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sBlue = 0;
            float sGreen = 0;
            float sRed = 0;
            int count = 0;

            // Loop through each pixel contributing for blurring
            for (int k = i - 1; k < i + 1; k++)
            {
                for (int l = j - 1; l < j + 1; l++)
                {
                    // Keep our calculations inside the boundary of the image
                    if (k >= 0 || k < height || l >= 0 || l < width)
                    {
                        sBlue += copy[k][l].rgbtBlue;
                        sGreen += copy[k][l].rgbtGreen;
                        sRed += copy[k][l].rgbtRed;
                        count++;
                    }
                }
            }

            // Average RGB values into image struct
            image[i][j].rgbtBlue = round(sBlue / count);
            image[i][j].rgbtGreen = round(sGreen / count);
            image[i][j].rgbtRed = round(sRed / count);
        }
    }
    return;
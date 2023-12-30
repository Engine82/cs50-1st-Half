#include <stdio.h>
#include <stdlib.h>

// Main function.  Recieves one command line argument.
int main(int argc, char *argv[])
{
    // Check for only 1 command line argument
    if (argc != 2)
    {
        printf("Improper usage: one input file");
        return 1;
    }

    // Open memory card
    FILE *memorycard = fopen(argv[1], "r");
    // If unsuccessful at opening, return error
    if (memorycard == NULL)
    {
        printf("Improper usage: file not found");
        return 1;
    }

    // Create variables outside of loops:
    unsigned char buffer[512];
    int imagecounter = 0;
    char *filename  = malloc(8);
    FILE *newimage = NULL;

    // Repeat until end of card - fread returns # bytes read, so if less than 512 bytes, at end of card
    // Read 512 bytes into buffer
    while (fread(buffer, 1, 512, memorycard) == 512)
    {
        // If start of new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If not first jpeg, close previous jpeg
            if (imagecounter > 0)
            {
                fclose(newimage);
            }
            // Create name for new file
            sprintf(filename, "%03i.jpg", imagecounter);

            // Create/open new file
            newimage = fopen(filename, "w");

            // Copy contents from buffer to new file.
            fwrite(buffer, 1, 512, newimage);

            // Increase image counter
            imagecounter++;
        }
        // Else if already found jpeg
        else if (imagecounter > 0)
        {
            // write next 512 byte block to open jpeg file
            fwrite(buffer, 1, 512, newimage);
        }
    }
    // Close any remaining files
    free(filename);
    fclose(newimage);
    fclose(memorycard);
    return 0;
}
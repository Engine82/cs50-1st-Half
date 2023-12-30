#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Error: improper usage. Format: input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Error: unable to open file\n");
        return 1;
    }

    // Read header
    WAVHEADER infile_header;
    fread(&infile_header, 43, 1, infile);

    // Use check_format to ensure WAV format
    if (check_format(infile_header) != 1)
    {
        printf("Improper file type\n");
        return 1;
    }

    // Open output file for writing
    FILE *outfile = fopen(argv[2], "w");
    if (outfile == NULL)
    {
        printf("Error: file open\n");
        return 1;
    }

    // Write header to file
    fwrite(&infile_header, sizeof(WAVHEADER), 1, outfile);

    // Use get_block_size to calculate size of block
    int blocksize = get_block_size(infile_header);



    // Create buffer & copy audio file in reverse
    BYTE buffer[blocksize];

    fseek(infile, blocksize, SEEK_END);
    while (ftell(infile) - blocksize > 44)
    {
        fseek(infile, blocksize * -2, SEEK_CUR);
        fread(buffer, blocksize, 1, infile);
        fwrite(buffer, blocksize, 1, outfile);
    }

    // Close and free
    fclose(infile);
    fclose(outfile);

}

int check_format(WAVHEADER header)
{
    if (header.format[0] == 0x57 && header.format[1] == 0x41 && header.format[2] == 0x56 && header.format[3] == 0x45)
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // BLOCK SIZE == # channels * bytes per sample
    int blocksize = (header.numChannels * (header.bitsPerSample / 8));
    return blocksize;
}
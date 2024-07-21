// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// Renaming the uint8_t datatype to BYTE
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // Defining a header variable
    BYTE *header = malloc(sizeof(BYTE) * HEADER_SIZE);
    fread(header, sizeof(BYTE) * HEADER_SIZE, 1, input);
    fwrite(header, sizeof(BYTE) * HEADER_SIZE, 1, output);
    free(header);

    // TODO: Read samples from input file and write updated data to output file
    BYTE *singleRead = malloc(sizeof(BYTE) * 2);
    while (fread(singleRead, sizeof(BYTE) * 2, 1, input) != 0)
    {
        printf("before multiply: %i\n", *singleRead);
        *singleRead *= factor;
        printf("after multiply: %i\n", *singleRead);
        fwrite(singleRead, sizeof(BYTE) * 2, 1, output);
    }
    free (singleRead);

    // Close files
    fclose(input);
    fclose(output);
}

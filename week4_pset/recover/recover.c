#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Defining a byte datatype
typedef uint8_t BYTE;

// Function prototype
bool recursiveCopying(BYTE *bufferArray, FILE *curImage, FILE *forensicImage, BYTE *overloadBufferArray, bool isOverloaded);

int main(int argc, char *argv[])
{
    /* Checking if the user inputted
    the correct number of command-line arguments. */
    if (argc != 2)
    {
        printf("Usage: ./recover [forensic image]\n\
        --> note that exactly one command-line argument must be used\n");
        return 1;
    }

    /* Opening the forensic image for reading,
    and warning the user if it was unable to
    be opened.*/
    FILE *forensicImage = fopen(argv[1], "r");
    if (forensicImage == NULL)
    {
        printf("Unable to open forensic image for reading!\n\
        Check the inputted forensic image address for errors.\n");
        return 1;
    }

    /* Initializing an integer to keep
    track of the number of files copied
    to assist with naming the recovered JPGS. */
    int numJPGSCopied = 0;

    /* Keeping track of if a JPG is currently being read. */
    bool curReadingJPG = false;

    /* Allocating memory for the JPG names. */
    char *curJPGName = malloc(7 * sizeof(char));

    /* Allocating memory for an overload
    buffer used when a JPG is initially found. */
    BYTE *overloadBufferArray = malloc(512 * sizeof(BYTE));
    bool isOverloaded = false;

    /* Using a while loop to run through
    all the information in the forensic image,
    with an integer buffer to keep track of
    the information being read. */
    BYTE *bufferArray = malloc(512 * sizeof(BYTE));
    while (fread(bufferArray, sizeof(BYTE), 512, forensicImage) != 0)
    {
        if (curReadingJPG == false)
        {
            /* If the buffer does not begin with the specified
            header, continue to the next 512 byte block. */
            if (bufferArray[0] != 0xff || bufferArray[1] != 0xd8 ||
            bufferArray[2] != 0xff || (bufferArray[3] & 0xf0) != 0xe0)
            {
                continue;
            }

            /* If the loop did not continue to the
            next iteration, that means a JPG has been
            discovered. */
            for (int i = 0; i < 512; i++)
            {
                overloadBufferArray[i] = bufferArray[i];
            }
            curReadingJPG = true;
            isOverloaded = true;
        }
        else if (curReadingJPG == true)
        {
            /* Setting the name of the
            JPG file currently being written in. */
            sprintf(curJPGName, "%03i.jpg", numJPGSCopied);

            /* Opening a file
            to store the next
            JPG being copied. */
            FILE *curImage = fopen(curJPGName, "w");

            /* Writing the overload buffer into the
            current opened JPG image if an overload
            buffer exists. */
            if (isOverloaded == true)
            {
                fwrite(overloadBufferArray, sizeof(BYTE), 512, curImage);
                isOverloaded = false;
            }

            /* Writing in the current JPG until a new one is found. */
            if (recursiveCopying(bufferArray, curImage, forensicImage, overloadBufferArray, isOverloaded) == false)
            {
                fclose(curImage);

                /* Incrementing the
                number of JPGS copied. */
                numJPGSCopied++;
            }
        }
    }

    /* Freeing the memory used for
    bufferArray. */
    free(bufferArray);

    /* Freeing the memory used for
    overloadBufferArray. */
    free(overloadBufferArray);

    /* Freeing the memory used for
    curJPGName. */
    free(curJPGName);

    /* Closing the main forensic image
    file. */
    if (fclose(forensicImage) != 0)
    {
        printf("Error closing forensic image file.\n");
        return 1;
    }

    /* Warning the user if no
    files were able to be recovered. */
    if (numJPGSCopied == 0)
    {
        printf("No JPGS were able to be recovered from the forensic image.\n");
    }
}

bool recursiveCopying(BYTE *bufferArray, FILE *curImage, FILE *forensicImage, BYTE *overloadBufferArray, bool isOverloaded)
{
    /* Checking if a new JPG has been found. */
    if (bufferArray[0] != 0xff || bufferArray[1] != 0xd8 ||
    bufferArray[2] != 0xff || (bufferArray[3] & 0xf0) != 0xe0)
    {
        // writing to the current JPG
        fwrite(bufferArray, sizeof(BYTE), 512, curImage);

        // reading more information to the buffer
        if (fread(bufferArray, sizeof(BYTE), 512, forensicImage) == 0)
        {
            return false;
        }

        // using recursion
        return recursiveCopying(bufferArray, curImage, forensicImage, overloadBufferArray, isOverloaded);
    }
    else
    {
        /* Copying the first 512 bytes of the
        next found JPG into the overloaded buffer
        array. */
        for (int i = 0; i < 512; i++)
        {
            overloadBufferArray[i] = bufferArray[i];
        }
        isOverloaded = true;
        return false;
    }
}

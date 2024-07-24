#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Defining a byte datatype
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    /* Checking if the user inputted
    the correct number of command-line arguments. */
    if (argc != 2)
    {
        printf("Usage: ./recover [forensic image]\n
        --> note that exactly one command-line argument must be used\n");
        return 1;
    }
    /* Opening the forensic image for reading,
    and warning the user if it was unable to
    be opened.*/
    FILE *forensicImage = openf(argv[1], "r");
    if (forensicImage == NULL)
    {
        printf("Unable to open forensic image for reading!\n
        Check the inputted forensic image address for errors.\n");
        return 1;
    }
    /* Initializing an integer to keep
    track of the number of files copied
    to assist with naming the recovered JPGS. */
    int numJPGSCopied = 0;

    /* Using a while loop to run through
    all the information in the forensic image,
    with an integer buffer to keep track of
    the information being read. */
    int *intBufferArray = malloc(512 * sizeof(BYTE));
    while (readf(intBufferArray, sizeof(BYTE), 512, forensicImage) != 0)
    {
        
    }

}

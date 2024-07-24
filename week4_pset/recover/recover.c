#include <stdio.h>
#include <stdlib.h>

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
    /*  */
    int numFilesCopied = 0;

}

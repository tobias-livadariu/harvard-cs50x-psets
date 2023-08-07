#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Getting the user's credit card number as a long
    long userNumber = get_long("Number: ");

    // Determining the number of digits in the user's credit card number
    long storageVar = userNumber;
    int numLength = 0;
    while (! (storageVar = 0))
    {
        storageVar /= 10;
        numLength += 1;
    }

    // Determining if the user's inputted number passes the chucksum as described by Luhan's Algorithm
    int checksum = 0;
    int curDigit;
    for (digitCount = 0; digitCount < numLength; digitCount++)
    {
        curDigit = userNumber % (10 )
    }
}

int exponentation(int num, int pow)
{
    int exponentedNum = 0;
    for (count = 0; count < pow; count++)
    {
        exponentedNum
    }
}
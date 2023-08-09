#include <cs50.h>
#include <stdio.h>

long exponentation(int num, int pow);

int main(void)
{
    // Getting the user's credit card number as a long
    long userNumber = get_long("Number: ");

    // Determining the number of digits in the user's credit card number
    long storageVar = userNumber;
    int numLength = 0;
    while (! (storageVar == 0))
    {
        storageVar /= 10;
        numLength += 1;
    }

    printf("length = %i\n", numLength);

    // Determining the two starting digits in the user's credit card number
    // These values will be used to check if the user's credit card is AMEX/MASTERCARD/VISA/INVALID if the number passes Luhan's Algorithm
    int firstTwo = (userNumber - (userNumber % exponentation(10, numLength - 2))) / exponentation(10, numLength - 2);

    printf("first two digits = %i\n", firstTwo);

    // Determining if the user's inputted number passes the chucksum as described by Luhan's Algorithm
    int checksum = 0;
    int tensDigit;
    int onesDigit;
    int curDigit;
    for (int digitCount = 1; digitCount <= numLength; digitCount++)
    {
        if (digitCount % 2 == 0)
        {
            curDigit = ((userNumber % exponentation(10, digitCount)) - (userNumber % exponentation(10, digitCount - 1))) / exponentation(10, digitCount - 1);
            if (curDigit > 4)
            {
                curDigit *= 2;
                onesDigit = curDigit % 10;
                tensDigit = (curDigit - onesDigit) / 10;
                checksum += onesDigit;
                checksum += tensDigit;
            }
            else
            {
                curDigit *= 2;
                checksum += curDigit;
            }
        }
        else
        {
            if (digitCount == 1)
            {
                curDigit = userNumber % 10;
                checksum += curDigit;
            }
            else
            {
                curDigit = ((userNumber % exponentation(10, digitCount)) - (userNumber % exponentation(10, digitCount - 1))) / exponentation(10, digitCount - 1);
                checksum += curDigit;
            }
        }
    }

    // If the user's credit card number passes Luhan's Algorithm, determining if it falls into the AMEX/MASTERCARD/VISA category or is INVALID regardless
    if (checksum % 10 == 0)
    {
        if (numLength == 15 && (firstTwo == 34 || firstTwo == 37))
        {
            printf("AMEX\n");
        }
        else if (numLength == 16 && (firstTwo == 51 || firstTwo == 52 || firstTwo == 53 || firstTwo == 54 || firstTwo == 55))
        {
            printf("MASTERCARED\n");
        }
        else if ((numLength == 13 || numLength == 16) && (firstTwo % 10) / 10 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Defining a function that can be used to raise numbers to exponents
// This function will be used to generate powers of ten for getting individual digits of the user's number
long exponentation(int num, int pow)
{
    long exponentedNum = 1;
    for (int count = 0; count < pow; count++)
    {
        exponentedNum *= num;
    }
    return exponentedNum;
}
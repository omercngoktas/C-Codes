#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatypes.h"
#define MAX_SIZE 256

/* reading txt file, then and converting them into correct type from string */
void readFile(char fileName[], int intSize, int floatSize, char endianType[])
{
    FILE *inputFile = fopen(fileName, "r");
    if(inputFile == NULL)
    {
        printf("Error: %s does not exist.\n", fileName);
        return;
    }

    char currentInput[MAX_SIZE];
    int i, check, signedInput, unsignedInput;
    float floatInput;

    while(!feof(inputFile))
    {
        /* check is used to determine if number float or unsigned, check will be 1,
        and if condition which is at the end of function is not going to work.
        but if number is not either float or unsigned, because check is still 0,
        last if condition will work, because number is signed */
        check = 0;
        fscanf(inputFile, "%s", currentInput);
        printf("-------------------------------------------------\n");
        for(i = 0; i < strlen(currentInput); i++)
        {
            /* because input contains '.', we know that this number is float. */
            if(currentInput[i] == '.')
            {
                /* converting string to float number */
                floatInput = atof(currentInput);
                floatNumber(floatInput, floatSize, currentInput, endianType);
                check = 1;
            }

            /* because input includes 'u' or 'U', we know that this number is unsigned. */
            else if(currentInput[i] == 'u' || currentInput[i] == 'U')
            {
                /* converting string to int number */
                unsignedInput = atoi(currentInput);
                unsignedNumber(unsignedInput, intSize, endianType);
                check = 1;
            }
        }

        /* because input does not contain either '.' or 'u', number must be signed. */
        if(check == 0)
        {
            /* converting string to int number */
            signedInput = atoi(currentInput);
            signedNumber(signedInput, intSize, endianType);
        }
    }
}
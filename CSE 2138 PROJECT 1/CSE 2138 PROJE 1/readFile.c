#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "datatypes.h"
#define MAX_SIZE 256

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
        check = 0;
        fscanf(inputFile, "%s", currentInput);
        printf("-------------------------------------------------\n");
        for(i = 0; i < strlen(currentInput); i++)
        {
            /* because input contains '.', we know that this number is float. */
            if(currentInput[i] == '.')
            {
                floatInput = atof(currentInput);
                floatNumber(floatInput, floatSize, currentInput, endianType);
                check = 1;
            }

            /* because input includes 'u' or 'U', we know that this number is unsigned. */
            else if(currentInput[i] == 'u' || currentInput[i] == 'U')
            {
                unsignedInput = atoi(currentInput);
                unsignedNumber(unsignedInput, intSize, endianType);
                check = 1;
            }
        }

        /* because input does not contain either '.' or 'u', number must be signed. */
        if(check == 0)
        {
            signedInput = atoi(currentInput);
            signedNumber(signedInput, intSize, endianType);
        }
    }
}
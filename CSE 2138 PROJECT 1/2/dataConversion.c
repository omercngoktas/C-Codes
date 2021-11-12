#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decimalToBinary.h"
#define MAXSIZE 256

int readFile(char fileName[], char inputs[MAXSIZE][MAXSIZE])
{
    FILE *inputFile = fopen(fileName, "r");
    
    //checking if file does not exist.
    if(inputFile == NULL)
    {
        printf("Error: %s does not exist.\n", fileName);
        return;
    }

    //creating char array list to use it later.
    char tempInput[MAXSIZE];
    int count = 0;

    //reading inputs and assigning them into char array list.
    while(!feof(inputFile))
    {
        fscanf(inputFile, "%s", tempInput);
        strcpy(inputs[count], tempInput);
        count++;
    }
    return count;
}

/* determining data type of input */
void determineDataType(char inputArray[MAXSIZE][MAXSIZE], int arraySize)
{
    int i, j, control, isSent;
    int digitNumber;

    /* traversing on inputs to determine whether
    they are floating point, signed or unsigned. */
    for(i = 0; i < arraySize; i++)
    {
        /* determining how many digit does have input
        to traverse on it */
        digitNumber = strlen(inputArray[i]);
       
        /* traversing on each digit of current input */
        for(j = 0; j < digitNumber; j++)
        {
            control = inputArray[i][j];
            isSent = 0;

            /* checking current digit if digit equals to '.' which is 46 in decimal */
            if(control == 46)
            {
                /* because input contains '.', we know that this number is floating point,
                so number is sent to function with char array type. */
                floatingPointNumber(inputArray[i]);
                isSent = 1;
                break;
            }

            /* checking current digit if digit equals to 'u' or 'U',
            so we will know that number is unsigned. */
            else if((control == 117) || (control == 85))
            {
                /* because input contains 'u' or 'U', we know that number is unsigned. */
                unsignedNumber(inputArray[i]);
                isSent = 1;
                break;
            }
        }

        /* isSent = 0, so we know that input was not sent other functions because
        it is not either floating point or unsigned number, so it must be signed number.*/
        if(isSent == 0)
        {
            signedNumber(inputArray[i]);
        }
    }
}

int floatingPointNumber(char inputNumber[])
{
    /* converting string to float number, because now we know that current input is float*/
    float inputFloating = atof(inputNumber);

    printf("float: %f\n", inputFloating);
}

int unsignedNumber(char inputNumber[])
{
    char *temp;
    unsigned inputUnsigned = strtoul(inputNumber, &temp, 10);
    printf("unsigned: %uu\n", inputUnsigned);
    unsignedToBinary(inputUnsigned);

}

int signedNumber(char inputNumber[])
{
    int inputSigned = atoi(inputNumber);
    printf("signed number: %d\n", inputSigned);
}
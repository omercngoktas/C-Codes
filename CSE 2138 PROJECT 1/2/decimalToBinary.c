#include <stdio.h>
#include <stdlib.h>
#include "dataConversion.h"
#define MAX_SIZE 256
#define CONST_BITS 16

void unsignedToBinary(unsigned number);
void convertToMantissa(int numberArray[], int mantissaArray[], int arrayLength);
void printDecimal(int numberArray[]);

/* converts decimal number to binary number*/
void unsignedToBinary(unsigned number)
{
    unsigned tempNumber = number;
    int count = 0, tempNumberArray[MAX_SIZE], i, tempCount, numberArray[MAX_SIZE];

    while(tempNumber > 0)
    {
        tempNumberArray[count] = tempNumber % 2;
        tempNumber = tempNumber / 2;
        count++;
    }

    tempCount = count;

    for(i = 0; i < CONST_BITS - count; i++)
    {
        numberArray[i] = 0;
    }

    for(i = CONST_BITS - count; i < CONST_BITS; i++)
    {
        numberArray[i] = tempNumberArray[--tempCount];
    }

    printDecimal(numberArray);
}

void convertToMantissa(int numberArray[], int mantissaArray[], int arrayLength)
{
    int i;
    for(i = 0; i < arrayLength; i++)
    {
        mantissaArray[i] = numberArray[i+1];
    }
}

void printDecimal(int numberArray[])
{
    int i;
    char byteArray1[4], byteArray2[4], byteArray3[4], byteArray4[4];
    //int binary1 = 0, binary2, binary3, binary4;

    for(i = 0; i < CONST_BITS; i++)
    {
        printf("%d", numberArray[i]);
    }
    printf("\n");
    for(i = 0; i < CONST_BITS; i++)
    {
        if(i < 4)
        {
            byteArray1[i] = numberArray[i];
        }

        if(i < 8 && i > 3)
        {
            byteArray2[i] = numberArray[i];
        }

        if(i < 12 && i > 7)
        {
            byteArray3[i] = numberArray[i];
        }

        if(i < 16 && i > 11)
        {
            byteArray4[i] = numberArray[i];
        }
    }

}
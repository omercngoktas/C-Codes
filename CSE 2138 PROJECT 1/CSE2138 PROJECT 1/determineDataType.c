#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fractionPartToBinary.h"
#include "decimalToBinary.h"
#define MAX_SIZE 256
#define BITS_SIZE 32
#define FLOAT_SIZE 32
#include "binaryToHex.h"
#include "rounding.h"
#include <math.h>

void determineDataType(char inputsArray[][MAX_SIZE], int arraySize, int floatPointSize);
int floatingPointNumber(char inputNumber[], int floatPointSize);
int unsignedNumber(char inputNumber[]);
int signedNumber(char inputNumber[]);

/* determining data type of input */
void determineDataType(char inputsArray[][MAX_SIZE], int arraySize, int floatPointSize)
{
    int i, j, control, isSent;
    int digitNumber;

    /* traversing on inputs to determine whether
    they are floating point, signed or unsigned. */
    for(i = 0; i < arraySize; i++)
    {
        /* determining how many digit does have input
        to traverse on it */
        digitNumber = strlen(inputsArray[i]);
       
        /* traversing on each digit of current input */
        for(j = 0; j < digitNumber; j++)
        {
            control = inputsArray[i][j];
            isSent = 0;

            /* checking current digit if digit equals to '.' which is 46 in decimal */
            if(control == 46)
            {
                /* because input contains '.', we know that this number is floating point,
                so number is sent to function with char array type. */
                floatingPointNumber(inputsArray[i], floatPointSize);
                isSent = 1;
                break;
            }

            /* checking current digit if digit equals to 'u' or 'U',
            so we will know that number is unsigned. */
            else if((control == 117) || (control == 85))
            {
                /* because input contains 'u' or 'U', we know that number is unsigned. */
                unsignedNumber(inputsArray[i]);
                isSent = 1;
                break;
            }
        }

        /* isSent = 0, so we know that input was not sent other functions because
        it is not either floating point or unsigned number, so it must be signed number.*/
        if(isSent == 0)
        {
            signedNumber(inputsArray[i]);
        }
    }
}

int floatingPointNumber(char inputNumber[], int floatPointSize)
{
    char binaryRepresentation[BITS_SIZE], hexRepresentation[BITS_SIZE/8];
    int i, j, decimalPart, count;
    float rawNumber;
    char tempDecimalPart[MAX_SIZE], decimalPartBinary[BITS_SIZE], tempBinary[BITS_SIZE];
    char fractionPartBinary[BITS_SIZE];
    float fractionPart;
    printf("float: %s\n", inputNumber);
    /* assigning decimal part of float number. */
    for(i = 0; i < MAX_SIZE; i++)
    {
        if(inputNumber[i] == '.')
            break;
        tempDecimalPart[i] = inputNumber[i];
    }
    /* assigning decimal part of float number.
    but it need to be converted into int from char array. */
    decimalPart = atoi(tempDecimalPart);
    rawNumber = atof(inputNumber);

    fractionPart = rawNumber - decimalPart;

    if(decimalPart < 0)
    {
        decimalPart = decimalPart * -1;
    }

    convertDecimalToBinary(decimalPart, decimalPartBinary);
    count = 0;
    while(decimalPartBinary[count] == 48)
    {
        count++;
    }

    i = count;
    j = 0;
    while(i < BITS_SIZE)
    {
        tempBinary[j] = decimalPartBinary[i];
        i++; j++;
    }
    tempBinary[j] = '\0';

    floatingPointToBinary(fractionPart, fractionPartBinary);

    char floatingPointRepresentInBinary[BITS_SIZE * 2];
    
    /*printf("decimalPartBinary: ");
    for(i = 0; i < BITS_SIZE; i++)
    {
        if(tempBinary[i] == '\0')
            break;
        printf("%c", tempBinary[i]);
    }
    printf("\nfractionPartBinary: ");
    for(i = 0; i < BITS_SIZE; i++)
    {
        if(fractionPartBinary[i] == '\0')
        {
            break;
        }
        printf("%c", fractionPartBinary[i]);
    }*/

    int index;
    i = 0;
    for(index = 0; index < BITS_SIZE * 2; index++)
    {
        if(tempBinary[i] == '\0')
        {
            floatingPointRepresentInBinary[index] = '\0';
            break;
        }
        floatingPointRepresentInBinary[index] = tempBinary[i++];
    }
    i = 0;
    for(index; index < BITS_SIZE * 2; index++)
    {
        if(fractionPartBinary[i] == '\n')
        {
            floatingPointRepresentInBinary[index] = '\0';
            break;
        }
        floatingPointRepresentInBinary[index] = fractionPartBinary[i++];
    }

    printf("float:\t");
    for(i = 0; i < BITS_SIZE * 2; i++)
    {
        if(floatingPointRepresentInBinary[i] == '\0')
        {
            break;
        }
        printf("%c", floatingPointRepresentInBinary[i]);
    }

    int signBit, eBits, exp, e = j - 1, fractionBits;
    exp = e + pow(2, (eBits - 1)) - 1;

    /* 1 byte equals to 8 bits, 4 bits will be used for exponent part,
	1 bit for signing bit and rest of the 3 bits for fraction*/
    if(floatPointSize == 1)
    {
        signBit = 1;
        fractionBits = 3;
        eBits = 4;
        //exp = e + pow(2, (eBits - 1)) - 1;
    }

    /* 2 bytes equals to 16 bits, 6 bits will be used for exponent part,
	1 bit for signing bit and rest of the 3 bits for fraction*/
    else if(floatPointSize == 2)
    {
        signBit = 1;
        fractionBits = 9;
        eBits = 6;
        //exp = e + pow(2, )
    }
    
    /* 3 bytes equals to 24 bits, 8 bits will be used for exponent part,
	1 bit for signing bit and rest of the 3 bits for fraction*/
    else if(floatPointSize == 3)
    {
        signBit = 1;
        fractionBits = 15;
        eBits = 8;
        //exp = pow(2, )
    }

    /* 4 bytes equals to 32 bits, 10 bits will be used for exponent part,
	1 bit for signing bit and rest of the 21 bits for fraction*/
    else if(floatPointSize == 4)
    {
        signBit = 1;
        fractionBits = 21;
        eBits = 10;
        //exp = pow(2, )
    }

    char *tempFractionPart = floatingPointRepresentInBinary;
    tempFractionPart++;

    int isExit = -1, halfCheckIndex = fractionBits, lengthFraction = strlen(tempFractionPart);
    if(lengthFraction > fractionBits)
    {
        for(halfCheckIndex; halfCheckIndex < lengthFraction; halfCheckIndex++)
        {
            if(tempFractionPart[halfCheckIndex] == '1')
                isExit++;
        }
    }
    if(isExit > 0)
        roundFractionToUp(tempFractionPart, fractionBits);
    
    if(lengthFraction < fractionBits)
    {
        int indexToAddZeroz = lengthFraction;
        for(indexToAddZeroz; indexToAddZeroz < fractionBits; indexToAddZeroz++)
        tempFractionPart[indexToAddZeroz] = '0';
    }

    if(floatPointSize == 3)
    {
        strcat(tempFractionPart, '\0');
        tempFractionPart[13] = '\0';
    }
    else if(floatPointSize == 4)
    {
        strcat(tempFractionPart, "0000000");
        tempFractionPart[19] = '\0';
    }
    char expBinary[BITS_SIZE];
    convertDecimalToBinary(exp, expBinary);
    expBinary[eBits] = '\0';
    char ieeeFormat[BITS_SIZE];
    if(rawNumber < 0)
    {
        ieeeFormat[0] = '1';
    }
    else if(rawNumber >= 0)
    {
        ieeeFormat[0] = '0';
    }
    ieeeFormat[1] = '\0';
    strcat(ieeeFormat, expBinary);
    strcat(ieeeFormat, tempFractionPart);

    for(i = 0; i < BITS_SIZE; i++)
    {
        if(ieeeFormat[i] == '\0')
            break;
        printf("%c", ieeeFormat[i]);
    }

}

int unsignedNumber(char inputNumber[])
{
    //unsigned inputUnsigned = strtoul(inputNumber, &temp, 10);
    int inputUnsigned = atoi(inputNumber), i;
    char unsignedBinary[BITS_SIZE];
    char hexaDecimalRep[BITS_SIZE];
    printf("\n************************************\n");
    printf("unsigned: %du\n", inputUnsigned);

    convertDecimalToBinary(inputUnsigned, unsignedBinary);
    for(i = 0; i < BITS_SIZE; i++)
    {
        printf("%c", unsignedBinary[i]);
    }
    printf("\nhex: ");
    convertBinToHex(unsignedBinary, hexaDecimalRep, BITS_SIZE);
    for(i = 0; i < 8; i++)
    {
        printf("%c", hexaDecimalRep[i]);
    }
    printf("\n************************************\n");
}

int signedNumber(char inputNumber[])
{
    int inputSigned = atoi(inputNumber);
    char signedBinary[BITS_SIZE];
    printf("\n---------------------------------------\n");
    printf("signed number: %d\n", inputSigned);
    convertDecimalToBinary(inputSigned, signedBinary);
    int i;
    for(i = 0; i < 8; i++)
    {
        printf("%c", signedBinary[i]);
    }
    printf("\n---------------------------------------\n");

}
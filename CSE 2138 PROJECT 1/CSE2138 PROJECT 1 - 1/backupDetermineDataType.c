#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fractionPartToBinary.h"
#include "decimalToBinary.h"
#define MAX_SIZE 256
#define BITS_SIZE 32
#include "binaryToHex.h"

void determineDataType(char inputsArray[][MAX_SIZE], int arraySize);
int floatingPointNumber(char inputNumber[]);
int unsignedNumber(char inputNumber[]);
int signedNumber(char inputNumber[]);

/* determining data type of input */
void determineDataType(char inputsArray[][MAX_SIZE], int arraySize)
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
                floatingPointNumber(inputsArray[i]);
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

int floatingPointNumber(char inputNumber[])
{
    /* to use in for or while loop. */
    int i;
    /* getting decimal part of float and declaring to int. */
    int leftPartInt;
    /* will take decimal part of float and then will be converting into int. */
    char leftPartChar[MAX_SIZE];
    /* it will include binary representation of decimal part. */
    char leftPartBinary[MAX_SIZE];
    /* converting string to float number, because now we know that current input is float. */
    float inputFloating = atof(inputNumber);

    char fractionPartBinary[BITS_SIZE];
    int count;

    /* assigning decimal part of float number. */
    for(i = 0; i < MAX_SIZE; i++)
    {
        if(inputNumber[i] == '.')
            break;
        leftPartChar[i] = inputNumber[i];
    }
    /* assigning decimal part of float number.
    but it need to be converted into int from char array. */
    leftPartInt = atoi(leftPartChar);

    printf("float: %f\n", inputFloating);
    count = floatingPointToBinary(leftPartBinary, inputNumber, leftPartInt, 1, 2, inputFloating, fractionPartBinary);
    printf("decPartBinary: ");
    for(i = 0; i < BITS_SIZE; i++)
    {
        printf("%c", leftPartBinary[i]);
    }
    printf("\nfraction: ---");
	for(i = 0; i < count; i++)
	{
		printf("%c", fractionPartBinary[i]);
	}
	printf("\n");
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
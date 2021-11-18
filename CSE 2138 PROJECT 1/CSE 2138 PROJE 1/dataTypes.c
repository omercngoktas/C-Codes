#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "decimalToBinary.h"
#include "binaryToHex.h"
#include "fractionPartToBinary.h"
#include "roundingFractionPart.h"
#include "endianType.h"
#define MAX_SIZE 256
#define BIT_SIZE 8

int floatConverter(float floatNumber, int floatSize, char inputNumber[]);

/* converting unsigned number to binary, then binary number is converted to hexadecimal,
   at the end of the function, type of the endian is determined whatever the user entered before */
void unsignedNumber(int unsignedNumber, int integerSize, char endianType[])
{
    /* creating char arrays for binary representation */
    char binaryRepr[integerSize * BIT_SIZE];
    /* creating char array for hexadecimal representation */
    char hexaDecimalRepr[integerSize * 2];

    printf("Unsigned number:\t\t%d\n", unsignedNumber);

    /* converting unsigned (decimal representation) number to binary */
    convertDecimalToBinary(unsignedNumber, binaryRepr, integerSize * BIT_SIZE);

    printf("Binary Representation:\t\t%s\n", binaryRepr);
    
    /* converting binary number to hexadecimal representations */
    convertBinToHex(binaryRepr, hexaDecimalRepr, integerSize * BIT_SIZE);

    printf("Hexadecimal Representation:\t0x%s\n", hexaDecimalRepr);

    /* checking if the endianType is equals to 'Little Endian' which user entered before */
    if(strcmp(endianType, "Little Endian") == 0)
    {
        littleEndian(hexaDecimalRepr, strlen(hexaDecimalRepr));
    }
    /* checking if endianType is 'Big Endian' */
    else if(strcmp(endianType, "Big Endian") == 0)
    {
        bigEndian(hexaDecimalRepr, strlen(hexaDecimalRepr));
    }
}

/* converting signed number to binary, then hexadecimal and
   at the end of the function determining endian type */
void signedNumber(int signedNumber, int integerSize, char endianType[])
{
    /* creating char arrays to store binary and hexadecimal representations */
    char binaryRepr[integerSize * BIT_SIZE], hexaDecimalRepr[integerSize*2];

    printf("Signed number:\t\t\t%d\n", signedNumber);
    /* converting decimal number to binary number */
    convertDecimalToBinary(signedNumber, binaryRepr, integerSize * BIT_SIZE);

    printf("Binary Representation:\t\t%s\n", binaryRepr);
    
    /* converting binary number to hexadecimal number representation */
    convertBinToHex(binaryRepr, hexaDecimalRepr, integerSize * BIT_SIZE);
    printf("Hexadecimal Representation:\t0x%s\n", hexaDecimalRepr);

    /* checking conditions for endian type */
    if(strcmp(endianType, "Little Endian") == 0)
    {
        littleEndian(hexaDecimalRepr, strlen(hexaDecimalRepr));
    }
    else if(strcmp(endianType, "Big Endian") == 0)
    {
        bigEndian(hexaDecimalRepr, strlen(hexaDecimalRepr));
    }
}

/* 
   converting decimal part of float number to binary then converting fraction part to
   binary then checking size of the floating point number to represent. if it is necessity, 
   number is going to be rounding up or down according to its value. 
   Then, all the binary numbers will be merged together. After that, binary number
   representation will be converted to hexadecimal representation and again at the end of
   the function, hexadecimal representation will change its position or not according to
   endian type.
*/
void floatNumber(float floatNumber, int floatSize, char inputNumber[], char endianType[])
{
    /* creating char arrays to store binary representations of decimal part and fraction part*/
    char decPartBinaryRepr[floatSize * BIT_SIZE], tempDecPartBin[floatSize * BIT_SIZE];
    char floatPartBinaryRepr[floatSize * BIT_SIZE], floatBinaryRepresentation[MAX_SIZE];
    int rawNumber = floatConverter(floatNumber, floatSize, inputNumber), i = 0, j = 0;
    float floatPart = floatNumber - rawNumber;
    char fractionPart15[] = "00", fractionPart21[] = "00000000";

    printf("Float number:\t\t\t%f\n", floatNumber);
    /* converting decimal part of the float point number to binary number */
    convertDecimalToBinary(rawNumber, decPartBinaryRepr, floatSize * BIT_SIZE);

    while(i < floatSize * BIT_SIZE)
    {
        /* getting rid of unnecessity part of binary number which will not change the value */
        if(decPartBinaryRepr[i] != '0')
            break;
        i++;
    }

    /* adding '\0' at the end of the array to be able to know end of the array */
    decPartBinaryRepr[floatSize * BIT_SIZE] = '\0';

    while(i < floatSize * BIT_SIZE)
    {
        if(decPartBinaryRepr[i] == '\0')
            break;

        tempDecPartBin[j] = decPartBinaryRepr[i];
        j++; i++;
    }

    tempDecPartBin[j] = '\0';
    strcpy(floatBinaryRepresentation, tempDecPartBin);
    /* converting fraction part of the number to binary number */
    floatingPointToBinary(floatPart, floatPartBinaryRepr);

    int signBit, fractionBits, eBits, exponent, twosPowerE = strlen(tempDecPartBin);
    twosPowerE--;
    /* 1 byte equals to 8 bits, 4 bits will be used for exponent part,
	1 bit for signing bit and rest of the 3 bits for fraction */
    if(floatSize == 1)
    {
        fractionBits = 3;
        eBits = 4;
        exponent = twosPowerE + pow(2, (eBits - 1)) - 1;
    }

    /* 2 bytes equals to 16 bits, 6 bits will be used for exponent part,
	1 bit for signing bit and rest of the 9 bits for fraction */
    else if(floatSize == 2)
    {
        fractionBits = 9;
        eBits = 6;
        exponent = twosPowerE + pow(2, (eBits - 1)) - 1;
    }
    
    /* 3 bytes equals to 24 bits, 8 bits will be used for exponent part,
	1 bit for signing bit and rest of the 13 bits for fraction */
    else if(floatSize == 3)
    {
        fractionBits = 13;
        eBits = 8;
        exponent = twosPowerE + pow(2, (eBits - 1)) - 1;
    }

    /* 4 bytes equals to 32 bits, 10 bits will be used for exponent part,
	1 bit for signing bit and rest of the 13 bits for fraction */
    else if(floatSize == 4)
    {
        fractionBits = 13;
        eBits = 10;
        exponent = twosPowerE + pow(2, (eBits - 1)) - 1;
    }
    
    /* adding binary rep. of fraction part to array which has already
       binary representation of decimal part */
    strcat(floatBinaryRepresentation, floatPartBinaryRepr);
    char *fractionPart = floatBinaryRepresentation;

    fractionPart++;

    int check = -1, checkIndex = fractionBits, lengthOfFraction = strlen(fractionPart);

    /* number needs to be rounded up if most right value is '1' */
    if(lengthOfFraction >= fractionBits)
    {
        while(checkIndex <= lengthOfFraction)
        {
            if(fractionPart[checkIndex] == '1')
                check += 1;
            checkIndex++;
        }
    }

    /* because most right value is '1', number needs to be rounding up */
    if(check >= 0)
    {
        roundFractionToUp(fractionPart, fractionBits);
    }

    /* because lenght of the fraction part is not bigger than the value which
       has allocated for it, it needs to be filling up with '0's */
    if(lengthOfFraction < fractionBits)
    {
        int indexToAddZeroz = lengthOfFraction;
        while(indexToAddZeroz < fractionBits)
        {
            fractionPart[indexToAddZeroz] = '0';
            indexToAddZeroz++;
        }
        /* putting '\0' to determine end of the array */
        fractionPart[indexToAddZeroz] = '\0';
    }

    /* putting more zeros to fill the array */
    if(floatSize == 3)
    {
        strcat(fractionPart, fractionPart15);
        fractionPart[15] = '\0';
    }
    /* putting more zeros to fill the array */
    else if(floatSize == 4)
    {
        strcat(fractionPart, fractionPart21);
        fractionPart[21] = '\0';
    }

    char expBinary[10];
    convertDecimalToBinary(exponent, expBinary, eBits);
    expBinary[eBits] = '\0';
    char floatingPointRep[floatSize * BIT_SIZE];

    /* putting sign bit, if number is less than 0,
       putting '1', if bigger, putting '0' */
    if(floatNumber < 0)
        floatingPointRep[0] = '1';
    else if(floatNumber >= 1)
        floatingPointRep[0] = '0';

    /* putting '\0' to know where strcat function will add next value from */
    floatingPointRep[1] = '\0';

    char hexRep[floatSize * 2];

    /* merging array together to convert it hexadecimal representation */
    strcat(floatingPointRep, expBinary);
    strcat(floatingPointRep, fractionPart);

    printf("IEEE Format:\t\t\t%s\n", floatingPointRep);

    /* converting float point representation to hexadecimal representation */
    convertBinToHex(floatingPointRep, hexRep, floatSize * BIT_SIZE);

    printf("Hexadecimal Representation:\t0x%s\n", hexRep);

    /* controlling endian type */
    if(strcmp(endianType, "Little Endian") == 0)
    {
        littleEndian(hexRep, strlen(hexRep));
    }
    else if(strcmp(endianType, "Big Endian") == 0)
    {
        bigEndian(hexRep, strlen(hexRep));
    }
}

/* getting decimal part of the float poing number
   and returning it from the function */
int floatConverter(float floatNumber, int floatSize, char inputNumber[])
{
    char tempDecimalPart[MAX_SIZE];
    int i, rawNumber;
    for(i = 0; i < floatSize * BIT_SIZE; i++)
    {
        if(inputNumber[i] == '.')
            break;
        tempDecimalPart[i] = inputNumber[i];
    }
    rawNumber = atoi(tempDecimalPart);
    return rawNumber;
}
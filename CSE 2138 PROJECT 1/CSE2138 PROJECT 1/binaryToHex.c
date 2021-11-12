#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 256
#define BITS_SIZE 32
#define REP_ARRAY 8

void convertBinToHex(char binaryNumberRep[], char hexNumberRep[], int arraySize)
{
	int i = 1, j, v, exponentPart = 3, fourBits = 0,
    hexRepArray[REP_ARRAY], tempArraySize = arraySize + 1,
    multiply, tempExponent;

    j = 0;
    /* calculating binary values 4 by 4 to handle hexadecimal representation. */
    while(i < tempArraySize)
    {
        multiply = 1;
        tempExponent = exponentPart;
        while(tempExponent != 0)
        {
            /* we multiply by 2 because we take power of 2. */
            multiply *= 2;
            tempExponent--;
        }

        multiply = multiply * (binaryNumberRep[i - 1] - 48);
        fourBits = fourBits + multiply;
		exponentPart--;

        /* when calculating 4 bits done, we pass next bits to calculate its hexadecimal value. */
		if(i % 4 == 0)
        {
            /* assigning exponen part again because there will be new 4 bits to calculate its hexd. value. */
			exponentPart = 3;
            /* adding hexadecimal representation of prev. byte to array. */
			hexRepArray[j] = fourBits;
            /* incrementing 'j' by one because new byte will be added to array. */
            j++;
			fourBits = 0;
		}
        i++;
	}

    v = 0;
    /* dividing arraySize by 4 because 4 bits (1 byte)
    can be represented by 1 hexadecimal letter or number. */
	while(v < arraySize / 4)
    {
        /* becasue current number is bigger than 10,
        its hexadecimal representation will be represented by letters.
        so, we should add 55 to represented from A to F according to its current value.*/
		if (hexRepArray[v] >= 10)
        {
            hexNumberRep[v] = hexRepArray[v] + 55;
        }

        /* because hexadecimal representation of the number is between 0 and 9,
        we should add 48 to current value. so, if number is 0, and when we add 48,
        its hexadecimal representation will be 0, because in ascii 48 is 0.*/
		else
        {
            hexNumberRep[v] = hexRepArray[v] + 48;
        }
        v++;
	}
}
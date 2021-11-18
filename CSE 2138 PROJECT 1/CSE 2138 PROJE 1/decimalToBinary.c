#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 256

void convertDecimalToBinary(int number, char binaryFormOfNumber[], int intSize)
{
	int tempNumber = number, i = 0, displayMask = 1 << (intSize-1), k = 0, j = intSize - 1;
    char currentBit;

	if (tempNumber < 0)
        tempNumber = tempNumber * (-1);

    while(i < intSize)
    {
        currentBit = tempNumber & displayMask ? '1':'0'; 
		binaryFormOfNumber[i] = currentBit;
		tempNumber <<= 1;
        i++;
    }
	
	if (number < 0)
    {	
        while(j >= 0)
        {
            if (binaryFormOfNumber[j] == '0' && binaryFormOfNumber[j-1] == '0' 
                || binaryFormOfNumber[j] == '0' && binaryFormOfNumber[j-1] == '1')
            {
                j--;
                continue;
            }
            else
            {
                j--;
                break;
            }
        }

        while(k < j)
        {
            if (binaryFormOfNumber[k] == '0')
            {
                binaryFormOfNumber[k] = '1';
                k++;
            }
                
			else 
            {
                binaryFormOfNumber[k] = '0';
                k++;
            }
        }
	}
    binaryFormOfNumber[intSize] = '\0';
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 256

/* converting decimal number to binary number */
void convertDecimalToBinary(int number, char binaryRepresentation[], int intSize)
{
	int tempNumber = number, i = 0, displayMask = 1 << (intSize-1), k = 0, j = intSize - 1;
    char currentBit;

    /* if number less than zero, multipliying it with -1 */
	if (tempNumber < 0)
        tempNumber = tempNumber * (-1);

    while(i < intSize)
    {
        /* looking i. bit of number, if it is 1, displaying 1,
        if it is 0, displaying 0 */
        currentBit = tempNumber & displayMask ? '1':'0'; 
		binaryRepresentation[i] = currentBit;
        /* shifting left tempNumber by 1 */
		tempNumber <<= 1;
        i++;
    }
	

	if (number < 0)
    {	
        while(j >= 0)
        {
            if (binaryRepresentation[j] == '0' && binaryRepresentation[j - 1] == '0' 
                || binaryRepresentation[j] == '0' && binaryRepresentation[j - 1] == '1')
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
            if (binaryRepresentation[k] == '0')
            {
                binaryRepresentation[k] = '1';
                k++;
            }
                
			else 
            {
                binaryRepresentation[k] = '0';
                k++;
            }
        }
	}
    binaryRepresentation[intSize] = '\0';
}
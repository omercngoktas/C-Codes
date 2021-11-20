#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 256

/* converting fraction part of number to binary number */
void floatingPointToBinary(float fractionPart, char fractionPartBinary[])
{
	int i = 0, count = 0;

	while(fractionPart != 1)
	{
		if(fractionPart == 0)
		{
			strcpy(fractionPartBinary, "0");
			fractionPartBinary[1] = '\0';
			break;
		}
		else if(fractionPart > 1)
		{
			fractionPart--;
		}
		
		fractionPart = fractionPart * 2;
		
		if(fractionPart < 1)
		{
			fractionPartBinary[count] = '0';
			count++;
		}
		else if(fractionPart > 1)
		{
			fractionPartBinary[count] = '1';
			count++;
		}
		else
		{
			fractionPartBinary[count] = '1';
			count++;
			break;
		}
	}
	
	if(count != 0)
	{
		fractionPartBinary[count] = '\0';
	}
}
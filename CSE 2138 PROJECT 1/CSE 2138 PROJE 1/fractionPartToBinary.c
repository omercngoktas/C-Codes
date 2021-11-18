#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 256

void floatingPointToBinary(float floatPart, char floatPartBinary[])
{
	int i = 0, count = 0;

	while(floatPart != 1)
	{
		if(floatPart == 0)
		{
			strcpy(floatPartBinary, "0");
			floatPartBinary[1] = '\0';
			break;
		}
		else if(floatPart > 1)
		{
			floatPart--;
		}
		
		floatPart = floatPart * 2;
		
		if(floatPart < 1)
		{
			floatPartBinary[count] = '0';
			count++;
		}
		else if(floatPart > 1)
		{
			floatPartBinary[count] = '1';
			count++;
		}
		else
		{
			floatPartBinary[count] = '1';
			count++;
			break;
		}
	}
	
	if(count != 0)
	{
		floatPartBinary[count] = '\0';
	}
}
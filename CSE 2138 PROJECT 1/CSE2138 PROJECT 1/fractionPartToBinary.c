#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "decimalToBinary.h"
#define MAX_SIZE 256
#define BITS_SIZE 32

void floatingPointToBinary(float floatPart, char floatPartBinary[]);

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
	/*printf("fraction: ");
	for(i = 0; i < count; i++)
	{
		printf("%c", floatPartBinary[i]);
	}
	printf("\n");*/
}
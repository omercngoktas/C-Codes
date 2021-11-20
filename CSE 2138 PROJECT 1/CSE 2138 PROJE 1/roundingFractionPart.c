#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 256

void roundFractionToUp(char *fracPartBinaryRepr, int fractionBit)
{
	int tempFractionBit = fractionBit;
	
	while(fractionBit >= 0)
	{
		/* if last index of the binary number is 1, number is rounded to up with 0 */
		if (fracPartBinaryRepr[fractionBit] == '1')
		{
			fracPartBinaryRepr[fractionBit] = '0';
		}
			
		/* if last index of the binary number is not 1,
		   it means that there will not be rounding anymore */
		else
		{	
			/* converting current index to 1, for rounding */
			fracPartBinaryRepr[fractionBit] = '1';
			break;
		}
		/* decresing index to come back from last index */
		fractionBit--;
	}

	/* determining end of the char array by putting '\0' */
	fracPartBinaryRepr[tempFractionBit] = '\0';
}
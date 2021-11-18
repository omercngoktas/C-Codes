#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 256

void roundFractionToUp(char *fractionPart, int fractionBit)
{
	int lastIndexToRound = fractionBit;
	for(lastIndexToRound; lastIndexToRound >= 0; lastIndexToRound--){
		if (fractionPart[lastIndexToRound] == '1') fractionPart[lastIndexToRound] = '0'; // if the bit is 1 converts it to 0 
		else {
			fractionPart[lastIndexToRound] = '1';	// if the bit is 0 converts it to 1 so that addition is completed 		
			break; // ends rounding process
		}
	} fractionPart[fractionBit]='\0'; // chops the binary number after rounding
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 256

void roundFractionToUp(char *fractionPart, int fractionBit)
{
    int lastIndexToRound = fractionBit - 1;
    for(lastIndexToRound; lastIndexToRound >= 0; lastIndexToRound--)
    {
        if(fractionPart[lastIndexToRound] = '1')
            fractionPart[lastIndexToRound] = '0';
        else
        {
            fractionPart[lastIndexToRound] = '1';
            break;
        }
    }
    fractionPart[fractionBit] = '\0';
}
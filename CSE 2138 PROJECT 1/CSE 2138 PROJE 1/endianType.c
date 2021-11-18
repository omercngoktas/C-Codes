#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 256

void littleEndian(char hexDecRep[], int arraySize)
{
	char tempArray[MAX_SIZE];
	int i = 0, j = 0;
	printf("Little Endian Representation:\t");
	while(arraySize > 0)
	{
		printf("%c%c ", hexDecRep[arraySize-2], hexDecRep[arraySize-1]);
		arraySize = arraySize - 2;
	}
    printf("\n");
}

void bigEndian(char hexDecRep[], int arraySize)
{
	int i = 0;
	printf("Big Endian Representation:\t");
	while(i < arraySize)
	{
		printf("%c%c ", hexDecRep[i], hexDecRep[i + 1]);
		i += 2;
	}
    printf("\n");
}
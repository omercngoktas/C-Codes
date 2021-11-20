#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "writeToFile.h"

/* if given endian type is little, representation should be reverse */
void littleEndian(char hexDecRep[], int arraySize)
{
	int i = 0, tempSize = arraySize;
	char endianArray[arraySize];
	
	while(arraySize > 0)
	{
		/* adding hexadecimal representation reverse to array */
		endianArray[i++] = hexDecRep[arraySize - 2];
		endianArray[i++] = hexDecRep[arraySize - 1];
		endianArray[i++] = ' ';
		arraySize -= 2;
	}
	endianArray[i] = '\0';

    printf("Little Endian Representation:\t%s\n", endianArray);
	
	writeToOutputFile(endianArray);
}

/* if given endian type is big, representation is not going to change */
void bigEndian(char hexDecRep[], int arraySize)
{
	int i = 0, j = 0;
	char endianArray[arraySize];
	
	while(i < arraySize)
	{
		if(i %2 == 0 && i != 0)
		{
			endianArray[j++] = ' ';
		}
		endianArray[j++] = hexDecRep[i++];
		
	}
	endianArray[j] = '\0';

    printf("Big Endian Representation:\t%s\n", endianArray);
	writeToOutputFile(endianArray);
}
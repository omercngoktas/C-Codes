#include <stdio.h>
#include <string.h>
#include "readFile.h"
#define MAX_SIZE 256

int main()
{
    int floatSize, intSize = 2;
    char endianType[MAX_SIZE];
    printf("Please enter the endian type (enter only Little Endian or Big Endian): ");
    scanf("%[^\n]", &endianType);

    if((strcmp(endianType, "Little Endian") != 0) 
        && (strcmp(endianType, "Big Endian") != 0))
    {
        printf("You have been entered wrong endian type.\n");
        return -1;
    }

    printf("Please enter the floating point size: ");
    scanf("%d", &floatSize);

    readFile("input.txt", intSize, floatSize, endianType);
    return 0;
}
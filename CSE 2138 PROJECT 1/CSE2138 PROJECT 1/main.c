#include <stdio.h>
#include <string.h>
#include "readFile.h"
#include "determineDataType.h"
#define MAX_SIZE 256

int main()
{
    char inputs[MAX_SIZE][MAX_SIZE];
    char byteOrder[MAX_SIZE];
    char fileName[MAX_SIZE];
    int size, i, byteOrdering, floatSize;
    printf("Byte Ordering: ");
    scanf("%d", &byteOrdering);
    printf("Floating Point Size: ");
    scanf("%d", &floatSize);

    /*printf("Name of the input file: ");
    scanf("%s", fileName);*/
    size = readFile("input.txt", inputs);
    
    determineDataType(inputs, size, floatSize);



    return 0;
}
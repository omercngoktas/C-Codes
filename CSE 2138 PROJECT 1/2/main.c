#include "dataConversion.h"
#include "decimalToBinary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 256

int main()
{
    int numberArray[MAX_SIZE], mantissaArray[MAX_SIZE];
    char name[MAX_SIZE];

    char inputs[MAX_SIZE][MAX_SIZE];



    /*printf("Please enter the name of input file: ");
    scanf("%s", name);*/
    determineDataType(inputs, readFile("input.txt", inputs));

    return 0;
}
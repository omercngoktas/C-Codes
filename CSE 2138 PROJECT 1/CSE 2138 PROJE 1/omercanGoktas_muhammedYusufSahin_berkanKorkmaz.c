/*
Ömercan Göktaş 150119671
Muhammed Yusuf Şahin 150119790
Berkan Korkmaz 150119623

When compiling the c files, you can copy and paste these;

gcc omercanGoktas_muhammedYusufSahin_berkanKorkmaz.c binaryToHex.c dataTypes.c decimalToBinary.c endianType.c fractionPartToBinary.c readFile.c roundingFractionPart.c writeToFile.c

*/

#include <stdio.h>
#include <string.h>
#include "readFile.h"
#define MAX_SIZE 256

/* main function of the project. */

int main()
{
    /* creating output file */
    FILE *tempOutputFile = fopen("output.txt", "w");
    fclose(tempOutputFile);

    int floatSize, intSize = 2;
    char inputFile[MAX_SIZE];
    char endianType[] = "Little Endian";

    if((strcmp(endianType, "Little Endian") != 0) 
    && (strcmp(endianType, "Big Endian") != 0))
    {
        printf("You have been entered wrong endian type.\n");
        return -1;
    }
    printf("Please enter name of the input file: ");
    scanf("%s", inputFile);
    printf("Please enter the floating point size: ");
    scanf("%d", &floatSize);

    readFile(inputFile, intSize, floatSize, endianType);
    return 0;
}
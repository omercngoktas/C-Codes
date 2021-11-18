#include <stdio.h>
#include <string.h>
#define MAX_SIZE 256

int readFile(char fileName[], char inputs[MAX_SIZE][MAX_SIZE])
{
    FILE *inputFile = fopen(fileName, "r");

    /* checking if file does not exist. */
    if(inputFile == NULL)
    {
        printf("Error: %s does not exist.\n", fileName);
        return -1;
    }

    /* creating char array list to use it later. */
    char tempInput[MAX_SIZE];
    int count = 0;

    /* reading inputs and assigning them into char array list. */
    while(!feof(inputFile))
    {
        fscanf(inputFile, "%s", tempInput);
        strcpy(inputs[count], tempInput);
        count++;
    }

    /* returns how many inputs there are in the input file. */
    return count;
}
#define MAX_SIZE 256
#include "decimalToBinary.h"

void determineDataType(char inputsArray[][MAX_SIZE], int arraySize, int floatPointSize);
int floatingPointNumber(char inputNumber[], int floatPointSize);
int unsignedNumber(char inputNumber[]);
int signedNumber(char inputNumber[]);
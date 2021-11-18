#define MAX_SIZE 256
#include "decimalToBinary.h"

void determineDataType(char inputsArray[][MAX_SIZE], int arraySize, int floatPointSize, int intSize);
int floatingPointNumber(char inputNumber[], int floatPointSize, int intSize);
int unsignedNumber(char inputNumber[], int intSize);
int signedNumber(char inputNumber[], int intSize);
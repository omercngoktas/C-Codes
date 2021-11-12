#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 256
#define BITS_SIZE 32

// converts float number to IEEE format
void floatToIEEE(char lineInputTxt[], char ieeeFormat[], int size){
	int i, j, bitNumberOfDecimalPart = 0;
	char binaryNumWithZeros[32], integerBinary[32];
	float number = atof(lineInputTxt);
	char *tokenPtr = strtok(lineInputTxt, "."); // tokenizes the line
	int integerPartOfFloat = atoi(tokenPtr); // integer part of the number
	float fractionPartOfFloat = number - integerPartOfFloat; //fraction part of the number
	
	if(integerPartOfFloat < 0)integerPartOfFloat -= 2*integerPartOfFloat;

	decToBinary(integerPartOfFloat, binaryNumWithZeros, 32); // converts integer part of float number to binary
	
	for(i = 0; i < 32; i++) {
		if (binaryNumWithZeros[i] == '0') continue;
		else break;
	}	
   
    // binary version of integer part without unnecessary zeros at the beginning
	for(j = i; j < 32; j++) 
		integerBinary[bitNumberOfDecimalPart++] = binaryNumWithZeros[j];
	integerBinary[bitNumberOfDecimalPart] = '\0';

	char fractionBinary[32]; //array for binary version of fraction part
	fractionToBinary(fractionBinary, fractionPartOfFloat);	

	char floatBinaryRepresent[64]; // array for binary version of whole float number
	strcpy(floatBinaryRepresent, integerBinary);
	strcat(floatBinaryRepresent, fractionBinary);
}

int main()
{
    char returnedStr[32];
    convertDecimalToBinary(-63, returnedStr);
    int i;
    for(i = 0; i < BITS_SIZE; i++)
    {
        printf("%c", returnedStr[i]);
    }
    return 0;
}
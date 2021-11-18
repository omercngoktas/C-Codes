
#include <stdio.h>
#include <string.h>
#include <math.h>

// converts a binary number to hexadecimal
void binaryToHex(char binaryNum[], char hexNum[], int size){	
	int i, j = 0, k = 0;
	int exponentOfTwo = 3;
	int binaryToDecimalFor4Bits = 0;
	int decimalArray[8];
	
	// calculates decimal values for each 4 bit pairs in binary number
	for (i=1; i< size + 1; i++) {	
		binaryToDecimalFor4Bits += (pow(2, exponentOfTwo) * (binaryNum[i-1] - '0'));		
		exponentOfTwo--;
		if (i%4 == 0) {
			exponentOfTwo = 3;		
			decimalArray[j++] = binaryToDecimalFor4Bits;			
			binaryToDecimalFor4Bits = 0;
		}	
	}
	
	// converts decimal values to letters if the value is greater than or equal to 10
	for (k; k < size/4; k++) {
		if (decimalArray[k] >= 10) hexNum[k] = decimalArray[k] + 55;
		else hexNum[k] = decimalArray[k] + 48;		
	}
}

// converts decimal numbers to binary for signed and unsigned integers
void decToBinary(int number, char binaryNum[], int size ) {
	int value = number;
	if (number < 0) number -= 2*number;

	int c, displayMask = 1 << (size-1); 
	char bit;  
	// loop through bits 
	for (c = 0; c < size; ++c) { 
		bit = number & displayMask ? '1':'0'; 
		binaryNum[c]=bit;
		number <<= 1; // shift number left by 1 	
	} 		
	
	// if value is less than zero, takes two's complement of the value
	if (value < 0) {	
		int j = size- 1; 
		for (j; j >= 0; j--) {
			if (binaryNum[j] == '0' && binaryNum[j-1] == '0' || binaryNum[j] == '0' && binaryNum[j-1] == '1') continue;	
			else break;	
		}	
		int i = 0;
		for (i; i < j; i++) {
			if (binaryNum[i] == '0') binaryNum[i] = '1';
			else binaryNum[i] = '0';
		}		
	}	
}

// converts fraction part of the number to binary
void fractionToBinary(char fractionBinary[], float fractionPartOfFloat){
 	int i = 0;
 	while(fractionPartOfFloat != 1)
	 { //fraction to binary
		if (fractionPartOfFloat == 0) 
		{
			strcpy(fractionBinary, "0");
			fractionBinary[1] = '\0';
			break;
		}
		else if(fractionPartOfFloat > 1)
			fractionPartOfFloat -= 1;	 	
		
		fractionPartOfFloat *= 2;

		if(fractionPartOfFloat < 1)
			fractionBinary[i++] = '0';

		else if(fractionPartOfFloat>1)
			fractionBinary[i++] = '1';		 
		else
		{
			fractionBinary[i++] = '1';
			break;
		}		 
	} 
	if(i != 0) fractionBinary[i] = '\0';
}

// rounds the number up by adding 1 
void roundUp(char *fractionPart, int fractionBit)
{
	printf("fractionBit: %d\n", fractionBit);
	int lastIndexToRound = fractionBit-1;
	for(lastIndexToRound; lastIndexToRound >= 0; lastIndexToRound--){
		if (fractionPart[lastIndexToRound] == '1') fractionPart[lastIndexToRound] = '0'; // if the bit is 1 converts it to 0 
		else {
			fractionPart[lastIndexToRound] = '1';	// if the bit is 0 converts it to 1 so that addition is completed 		
			break; // ends rounding process
		}
	} fractionPart[fractionBit]='\0'; // chops the binary number after rounding
}


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
	printf("\nbitNumberOfDecimalPart: %d\n",bitNumberOfDecimalPart);
	char fractionBinary[32]; //array for binary version of fraction part
	fractionToBinary(fractionBinary, fractionPartOfFloat);
	printf("\nfractionPartBinary: %s\n", fractionBinary);

	char floatBinaryRepresent[64]; // array for binary version of whole float number
	
	strcpy(floatBinaryRepresent, integerBinary);
	strcat(floatBinaryRepresent, fractionBinary);
	printf("\nintegerBinary: %s\nfractionBinary: %s\n", integerBinary, fractionBinary);
	printf("floatBinaryRep: %s\n", floatBinaryRepresent);


	// calculates exponent part of floating point represent as a decimal value
	int fractionBit, expBit, exp, e = bitNumberOfDecimalPart - 1;
	switch(size)
	{		
		case 1:
			/* 1 byte equals to 8 bits, 4 bits for exponent part,
			1 bit for signing bit and rest of the 3 bits for fraction*/
			fractionBit = 4;

			expBit = 3;

			exp = e + pow(2, (expBit-1)) - 1;		
			break;
		case 2:
			fractionBit = 7;

			expBit = 8;

			exp = e + pow(2, (expBit-1)) - 1;
			break;
		case 3:
			fractionBit = 12;

			expBit = 10;

			exp = e + pow(2, (expBit-1)) - 1;		
			break;
		case 4:
			fractionBit = 12;

			expBit = 12;

			exp = e + pow(2, (expBit-1)) - 1;		
			break;
	}
	printf("floatBinaryRepresent: %s\n", floatBinaryRepresent);
	char *fractionPart = floatBinaryRepresent;
	fractionPart++; // drops the first bit(which is one) of binary float number so that obtains main fraction part of IEEE format
	printf("fractionPart:\t%s\n", fractionPart);
	// determines whether the part to be dropped to round the number is greater than half or not
	int oneExistCheck = -1, halfCheckIndex = fractionBit, lengthOfFraction = strlen(fractionPart);
	if(lengthOfFraction > fractionBit) {
		for(halfCheckIndex; halfCheckIndex < lengthOfFraction; halfCheckIndex++) {
			if(fractionPart[halfCheckIndex] == '1') oneExistCheck += 1;
		}
	}
	printf("before round:\t%s\n", fractionPart);

	if(oneExistCheck > 0) roundUp(fractionPart, fractionBit); /* if first bit of the part after the part which will be rounded is 1 and it has 1's more than one, 
	                                                          this means that part is greater than half. so the number should be rounded up */
	printf("Rounded:\t%s", fractionPart);
	// if the binary fraction has less bits then the fraction part of IEEE format, adds zeros to the end		
	if(lengthOfFraction < fractionBit) {
		int indexToAddZeros = lengthOfFraction;
		for(indexToAddZeros; indexToAddZeros < fractionBit; indexToAddZeros++) fractionPart[indexToAddZeros] = '0';
		fractionPart[indexToAddZeros] = '\0';	
	}
	printf("\nAfter adding zeroz:\t%s", fractionPart);
	
	// if the byte is 3, it is constant that 12 bits will be the fraction part of IEEE format,
	// so that adds a zero to complete the binary fraction to 13 bits
	if(size == 3) {
		strcat(fractionPart, "0");
		fractionPart[15] = '\0';
    }else if (size == 4) { // if the byte is 4, adds seven zeros to complete the binary fraction to 19 bits
		strcat(fractionPart, "0000000");
		fractionPart[21] = '\0';
	}	
	 
	char expBinary[12];
	decToBinary(exp, expBinary, expBit); // converts exponent of IEEE format to binary
	expBinary[expBit] = '\0';
	
	// if float number is negative, the sign bit is 0 and if it is positive the sign bit is 1
	if(number < 0) {
		ieeeFormat[0] = '1';
	}else ieeeFormat[0] = '0';			
	ieeeFormat[1] = '\0';
	strcat(ieeeFormat, expBinary);
	strcat(ieeeFormat, fractionPart);
}

// prints the hexadecimal value in Little Endian ordering into the output.txt file and to the command prompt 
void littleEndian(FILE *output, char hexNum[], int hexIndex, int size ){
	int i;
	printf("\nHexadecimal: ");					
	for (i=0; i < size; i++) {					
		fprintf(output, "%c%c ", hexNum[hexIndex], hexNum[hexIndex +1]);		
		printf("%c%c ", hexNum[hexIndex], hexNum[hexIndex+1]);				
        hexIndex -= 2;
	}
    printf("\n");
    fprintf(output, "\n");
}

// prints the hexadecimal value in Big Endian ordering into the output.txt file and to the command prompt 
void bigEndian(FILE *output, char hexNum[], int size ){
	int i, hexIndex = 0;
	printf("\nHexadecimal: ");
	for(i=0; i < size; i++) {
		fprintf(output,"%c%c ", hexNum[hexIndex], hexNum[hexIndex+1]);
		printf("%c%c ", hexNum[hexIndex], hexNum[hexIndex+1]);		
        hexIndex += 2;
    }   
    printf("\n");
    fprintf(output, "\n");
}

int main(int argc, char *argv[]){
	FILE *input=fopen("input.txt", "r");
	FILE *output=fopen("output.txt", "w");	
	char byte_order[30], float_size[30], line[100];
	
	printf("Byte Ordering: ");
	fgets(byte_order, 30, stdin);
	printf("Floating point size: ");
	fgets(float_size, 30, stdin);
	int size = atoi(float_size);	
	
	// reads output.txt line by line and assigns that string to the line
	while(fgets(line, 100, input)) {
		
		// determines whether the number in each line is signed-unsigned integer or float
		char *floatCh = strpbrk(line, ".");
		char *signedCh = strpbrk(line, "-");
		char *unsignedCh = strpbrk(line, "u");
		
		// calls related functions according to the type of the numbers to convert hexadecimal 
	    if(floatCh) {
			char ieeeFormat[32];
			char hexNum[8];
			floatToIEEE(line, ieeeFormat, size);
			printf("\nIEEE Format: %s", ieeeFormat);
			binaryToHex(ieeeFormat, hexNum, 8*size);
			if(strncmp(byte_order, "Little Endian", 13) == 0) {
				int hexIndex = 2*size - 2;					
				littleEndian(output, hexNum, hexIndex, size);       				
			} else bigEndian(output, hexNum, size);			
		}
		
		else {	
			int sizeForIntegers = 2; // byte is 2 for all integers as default	
			char binaryNum[32];
			char hexNum[8];
			int number = atoi(line);
			printf("----- %s\n", line);
			decToBinary(number, binaryNum, 8*sizeForIntegers);
			binaryNum[16] = '\0'; 
			printf("\nBinary Representation: %s", binaryNum);
			binaryToHex(binaryNum, hexNum, 8*sizeForIntegers);		       						
			if(strncmp(byte_order, "Little Endian",13) == 0) {
				int hexIndex = 2*sizeForIntegers - 2;
				littleEndian(output, hexNum, hexIndex,sizeForIntegers);					
			} else bigEndian(output, hexNum, sizeForIntegers);				
			
		}	
	}	
	fclose(input);
	fclose(output);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* writing hexadecimal representation of endian to output file */
void writeToOutputFile(char hexaDecRepr[])
{
    FILE *outputFile = fopen("output.txt", "a");
    fprintf(outputFile, "%s\n", hexaDecRepr);
}
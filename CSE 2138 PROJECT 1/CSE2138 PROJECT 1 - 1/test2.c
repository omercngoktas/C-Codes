#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *inputFile = fopen("input.txt", "r");
    char line[100];

    while(fgets(line, 100, inputFile))
    {
        char *floatCh = strpbrk(line, ".");
		char *signedCh = strpbrk(line, "-");
		char *unsignedCh = strpbrk(line, "u");

        printf("%s\n", line);
    }
    return 0;
}
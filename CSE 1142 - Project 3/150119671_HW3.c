// Omercan Goktas 150119671
// In this program, I created string struct and created 4 functions which are given from .pdf file.
// Moreover, to make project simple, I created 4 more functions name as -> findFirstString, findSecondString, findNumberLetters, findNumberWords.
// In these functions I returned first string which is before ':', and second string which is after ',' from txt files.
// Also, I applied functions to return number of letters and number of words which are in one line, after that I added them together in main function.
// I want to mention about compiling. On 13.01.2021, I talked to Sanem Hoca. I mentioned that I wrote these code on Ubuntu system. That is why, it does not work on
// Windows system. If it is possible, I can open my screen and you can try on my computer.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *string;
    char *string2;
} String;

int charAt(String *s, int index)
{
    index -= 48; // while calling charAt, index was sent in char value. that's why it needs to change into integer value.
    int lenghtString = strlen(s->string); // this holds lenght of string.
    int asciValue = (s->string)[index] - 32; // this holds ascii value of the character.
    if (index < 0) // this if checks whether index less than 0.
    {
        return -1;
    }

    else if (lenghtString <= index) // this else if checks whether given index equals or greather than lenght of the string.
    {
        return -1;
    }
    
    else // if 'if' and 'else if' did not apply, it returns asci value of character.
    {
        return asciValue;
    }
}

String *concat(String *s1, String *s2)
{
    int i = 0, j; // they are going to be used in while and for loops.
    int lenghtS1 = 0; // this is going to hold lenght of string.
    while((s1->string)[i] != '\0') // this loop counts lenght of the string.
    {
        i++;
        if ((s1->string)[i] == ' ')
        {
            continue;
        }
        lenghtS1++;
    }

    (s1->string)[lenghtS1+2] = ' ';
    for(j = 0; j < strlen(s2->string2); lenghtS1++, j++) // this for loop adds s2 to ends of s1.
    {
        (s1->string)[lenghtS1+3] = (s2->string2)[j];
    }
}

unsigned int strSearch(String *s1, String *s2)
{
    int lenghtStringOne = strlen((s1->string));
    int lenghtStringTwo = strlen((s2->string2));
    int i = 0, j = 0;
    int count = 0; // this is going to be higher according to lenght of the word which in string1, contains string2.

    while ((i < lenghtStringOne) && (j < lenghtStringTwo)) // this while loop finds the word of s2 which is in word of s2.
    {
        if ((s1->string)[i] != (s2->string2)[j]) // this 'if' checks if character of s2 not equals to character of s1.
        {
            i++; j = 0;
        }
        else if ((s1->string)[i] == (s2->string2)[j]) // this 'else if' checks if character of s2 equals to character of s1.
        {
            i++; j++;
        }
    }
    i--; j--; // after finding second string in first string, i and j are higher 1 value than they need to be. that's why they need to be declereated.

    while((s1->string)[i] != ' ') // after finding second string, to find its lenght, this while loop goes beggining of the first string.
    {
        i--;
    }

    i++;

    while((s1->string)[i] != ' ')  // after going to the beggining of the first string, 
    {
        i++;            // this while loop goes up to end of the string, while it goes end of the string, it counts the lenght of the string.
        count++;
    }

    return count;
}

unsigned int findScore(String *s1)
{
    int score = 0; // this holds score of the string.
    int lenghtString = strlen(s1->string); // this is lenght of the s1.;
    int i; // this is going to be used in for loop.

    for (i = 0; i < lenghtString; i++) // this loop is implemented according to lenght of the string.
    {
        switch((s1->string)[i]) // this switch-case checks the letter and then it increases 'score' according to points.
        {
            case('A'): case('E'): case('I'): case('O'): case('U'): case('L'): case('N'): case('R'):
            case('S'): case('T'): case('a'): case('e'): case('i'): case('o'): case('u'): case('l'):
            case('n'): case('r'): case('s'): case('t'):
            score += 1;
            break;

            case('D'): case('G'): case('d'): case('g'):
            score += 2;
            break;

            case('B'): case('C'): case('M'): case('P'): case('b'): case('c'): case('m'): case('p'):
            score += 3;
            break;

            case('F'): case('H'): case('V'): case('W'): case('Y'): 
            case('f'): case('h'): case('v'): case('w'): case('y'):
            score += 4;
            break;

            case('K'): case('k'):
            score += 5;
            break;

            case('J'): case('X'): case('j'): case('x'):
            score += 8;
            break;

            case('Q'): case('Z'): case('q'): case('z'):
            score += 10;
            break;

            default:
            break;
        }
    }
    return score;
}

char* findFirstString(char currentString[]) // this function finds first string of current line.
{
    int tempLength = strlen(currentString); // tempLenght takes length of hole given line.
    int lengthCurrentString = 0; // this is going to be changing according to lenght of first string.
    int i, j;
    char finalString[100]; // this is going to be first string after searching.
    char *returnString = malloc(sizeof(char) * tempLength); // this is going to be finalString and then will be returned.

    for (i = 0; i < tempLength; i++) // for loop checks where is the ':', and while checking it increases lengthCurrentString.
    {
        lengthCurrentString++;
        if (currentString[i] == ':')
        {
            break;
        }
    }

    for (j = 0; j < lengthCurrentString - 1; j++) // for loop applies part of first string to the finalString.
    {
        finalString[j] = currentString[j];
    }

    finalString[j] = '\0'; // it puts 'ending' character at the end of the string.
    returnString = finalString; // because of the fact that string need to be returning, string should be assigned char pointer.
    return returnString;
}

char* findSecondString(char currentString[]) // this function finds string which is after comma.
{
    int tempLength = strlen(currentString); // tempLenght takes length of hole given line.
    int lengthCurrentString = 0; // this is going to be changing according to lenght of first string.
    int i, j, k = 0;
    int index = 0, m;
    char finalString[100]; // this is going to be first string after searching.
    char *returnString = malloc(sizeof(char) * tempLength); // this is going to be finalString and then will be returned.

    for (i = 0; i < tempLength; i++) // for loop checks where is the ':', and while checking it increases lengthCurrentString.
    {
        lengthCurrentString++;
        if (currentString[i] == ':')
        {
            break;
        }
    }

    lengthCurrentString += 2;
    int v;
    for (v = 0; currentString[lengthCurrentString] != 13; v++)
    {
        finalString[v] = currentString[lengthCurrentString];
        lengthCurrentString++;
    }
    finalString[v] = '\0';
    returnString = finalString;
    return returnString;
}

int findNumberLetters(char words[]) // this function calculates number of letters on current line and returns this number.
{
    int numberLetters = 0;
    int i;
    int lenghtWords = strlen(words);
    for (i = 0; i < lenghtWords; i++)
    {
        switch(words[i]) // this switch-case checks the letter and then it increases 'score' according to points.
        {
            case('A'): case('E'): case('I'): case('O'): case('U'): case('L'): case('N'): case('R'):
            case('S'): case('T'): case('a'): case('e'): case('i'): case('o'): case('u'): case('l'):
            case('n'): case('r'): case('s'): case('t'): case('D'): case('G'): case('d'): case('g'):
            case('B'): case('C'): case('M'): case('P'): case('b'): case('c'): case('m'): case('p'):
            case('F'): case('H'): case('V'): case('W'): case('Y'): case('f'): case('h'): case('v'):
            case('w'): case('y'): case('K'): case('k'): case('J'): case('X'): case('j'): case('x'):
            case('Q'): case('Z'): case('q'): case('z'):
            numberLetters++;
            default:
            break;
        }
    }
    return numberLetters;
}

int findNumberWords(char words[]) // this function calculates number of words on current line and returns this number.
{
    int lenghtWords = strlen(words);
    int i;
    int numberWords = 1;

    for (i = 0; i < lenghtWords; i++)
    {
        if (words[i] == ' ')
        {
            numberWords++;
        }
    }
    return numberWords;
}

int main()
{
    String currentString;
    currentString.string = malloc(sizeof(char) * 50);
    currentString.string2 = malloc(sizeof(char) * 50);
    String *pointerCurrentString = &currentString;

    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL)
    {
        printf("File couldn't find. Please make sure that input.txt is in the same folder as .c file.\n");
        return 0;
    }
    int lenghtString; // this will be changing according to lenght of the string.
    int valueOperator[100]; // this will be changing according to operation as 1, 2, 3, or 4.
    int count = 0; // this will be used for counting line of text file.
    int i = 0, j, k, m;
    char currentLine[100][100]; // this holds each lines in itself.
    int numberWords = 0; // it counts number of the words in the txt file.
    int numberLetters = 0; // it counts number of the letters in the txt file.

    FILE *outputFile = fopen("output.txt", "w");

    while (1) // this while loop adds each line to the currentLine according to line number.
    { 
        if (fgets(currentLine[i],150, inputFile) == NULL)
        {
            break;
        }
        i++; count++;
    }

    for (k = 0; k < count - 2; k++) // for loop works according to number of the lines.
    {
        lenghtString = strlen(currentLine[k]);

        for (j = 0; j < lenghtString; j++) // for loop works according to each character in one line.
        {
            if (currentLine[k][j] == ':') // 'if' checks ':'.
            {
                valueOperator[k] = (currentLine[k][j+1]); // valueOperator implemented after finding ':' in line.
            }
        }
    }

    char tempString[100];
    int tempLenght;
    int v, lenghtCurrentString;

    for (m = 0; m < count - 2; m++) // this for loop applies operators and calls functions.
    {
        switch (valueOperator[m])
        {
            case '1':
                strcpy((*pointerCurrentString).string, findFirstString(currentLine[m]));
                strcpy((*pointerCurrentString).string2, findSecondString(currentLine[m]));
                
                numberLetters += findNumberLetters(pointerCurrentString->string);
                numberWords += findNumberWords(pointerCurrentString->string);
                
                int sendIndex = (int)((pointerCurrentString->string2)[0]);
                char lastValue = charAt(pointerCurrentString, sendIndex);
                printf("%c\n", charAt(pointerCurrentString, sendIndex));
                fputc(lastValue, outputFile);
                fputc('\n', outputFile);
                break;

            case '2':
                strcpy((*pointerCurrentString).string, findFirstString(currentLine[m]));
                strcpy((*pointerCurrentString).string2, findSecondString(currentLine[m]));
                concat(pointerCurrentString, pointerCurrentString);
                
                numberLetters += findNumberLetters(pointerCurrentString->string);
                numberWords += findNumberWords(pointerCurrentString->string);
                
                printf("%s\n", pointerCurrentString->string);
                fputs(pointerCurrentString->string, outputFile);
                fputc('\n', outputFile);
                break;

            case '3':
                strcpy((*pointerCurrentString).string, findFirstString(currentLine[m]));
                strcpy((*pointerCurrentString).string2, findSecondString(currentLine[m]));

                numberLetters += findNumberLetters(pointerCurrentString->string);
                numberWords += findNumberWords(pointerCurrentString->string);
                numberLetters += findNumberLetters(pointerCurrentString->string2);
                numberWords += findNumberWords(pointerCurrentString->string2);
                
                int resultSearch = strSearch(pointerCurrentString, pointerCurrentString);
                printf("%d\n", resultSearch);
                fprintf(outputFile, "%d", resultSearch);
                fputc('\n', outputFile);
                break;

            case '4':
                strcpy((*pointerCurrentString).string, findFirstString(currentLine[m]));
                int totalScore = findScore(pointerCurrentString);

                numberLetters += findNumberLetters(pointerCurrentString->string);
                numberWords += findNumberWords(pointerCurrentString->string);

                printf("%d\n", totalScore);
                fprintf(outputFile, "%d", totalScore);
                fputc('\n', outputFile);
                break;
        }
    }

    int x = 0;
    if (currentLine[m][x] == 's' && currentLine[m][x+1] == 't' && currentLine[m][x+2] == 'a' && currentLine[m][3] == 't')
    {
        fprintf(outputFile, "The number of words: %d\n", numberWords);
        printf("The number of words: %d\n", numberWords);
        fprintf(outputFile, "The number of alphabetic letters: %d\n", numberLetters);
        printf("The number of alphabetic letters: %d\n", numberLetters);
    }
    x = 0;
    if (currentLine[m+1][x] == 'q' && currentLine[m+1][x+1] == 'u' && currentLine[m+1][x+2] == 'i' && currentLine[m+1][+3] == 't')
    {
        printf("Program ends. Bye\n");
        fputs("Program ends. Bye", outputFile);
        fclose(outputFile);
    }
    else if (currentLine[m+1][x] == 'e' && currentLine[m+1][x+1] == 'x' && currentLine[m+1][x+2] == 'i' && currentLine[m+1][+3] == 't')
    {
        printf("Program ends. Bye\n");
        fputs("Program ends. Bye", outputFile);
        fclose(outputFile);
    }
    else
    {
        printf("Some problem has occured. Sorry :(.");
        fclose(outputFile);
        return 0;
    }
    
    fclose(inputFile);
    return 0;
}
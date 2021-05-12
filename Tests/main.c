#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_NAME 256

void displayUsers(char name[], char surname[])
{
    setlocale(LC_ALL, "Turkish");
    printf("%s %s\n", name, surname);
}

void openText()
{
    setlocale(LC_ALL, "Turkish");
    char name[MAX_NAME], surname[MAX_NAME];
    FILE *userText = fopen("userList.txt", "r");
    if(userText == NULL)
    {
        printf("Dosya acilamadi.\n");
        return;
    }
    while(!feof(userText))
    {
        fscanf(userText, "%s %s", name, surname);
        displayUsers(name, surname);
    }
}

int main()
{
    setlocale(LC_ALL, "Turkish");
    openText();
    return 0;
}
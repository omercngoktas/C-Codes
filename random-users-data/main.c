#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 256

struct users
{
    int id;
    char name[MAX_NAME], surname[MAX_NAME];
    struct users *next;
};

typedef struct users users;
typedef users usersPtr;
usersPtr *usersNode = NULL;

void display()
{
    usersPtr *iter = usersNode;
    while(iter != NULL)
    {
        printf("%d\t%s\t%s\n", iter->id, iter->name, iter->surname);
        iter = iter->next;
    }
}

void connectUsers(char name[], char surname[])
{
    if(usersNode == NULL)
    {
        usersNode = (usersPtr *) malloc(sizeof(usersPtr));
        usersNode->next = NULL;
        usersNode->id = -1;
        strcpy(usersNode->name, name);
        strcpy(usersNode->surname, surname);
        return;
    }

    usersPtr *iterUsers = usersNode;

    while(iterUsers->next != NULL)
        iterUsers = iterUsers->next;
    
    iterUsers->next = (usersPtr *) malloc(sizeof(usersPtr));
    iterUsers->next->id = -1;
    strcpy(iterUsers->next->name, name);
    strcpy(iterUsers->next->surname, surname);
    iterUsers->next->next = NULL;
}

void openFile()
{
    char name[MAX_NAME], surname[MAX_NAME];
    FILE *userList = fopen("userList.txt", "r");
    if(userList == NULL)
        return;

    while(!feof(userList))
    {
        fscanf(userList, "%s %s", name, surname);
        if(feof(userList))
            break;
        connectUsers(name, surname);
    }

    fclose(userList);
}

void addId(int id)
{
    usersPtr *iter = usersNode;
    while(iter->id != -1)
    {
        iter = iter->next;
    }
    iter->id = id;
}

void openRandomNumbers()
{
    int id;
    FILE *randomNumber = fopen("randomSayilar.txt", "r");

    while(!feof(randomNumber))
    {
        fscanf(randomNumber, "%d", &id);
        if(feof(randomNumber))
            return;
        addId(id);
    }
    fclose(randomNumber);
}

void addToFile()
{
    FILE *newFile = fopen("usersList.txt", "w");
    usersPtr *iter = usersNode;
    while(iter != NULL)
    {
        fprintf(newFile, "%d %s %s\n", iter->id, iter->name, iter->surname);
        iter = iter->next;
    }
}

int main()
{
    int id;
    openFile();
    display();
    openRandomNumbers();
    display();
    scanf("%d", &id);
    addToFile();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 10
#define MAX_SIZE 256

struct usersArray
{
    int key;
    struct usersData *data;
    struct usersArray *next;
};

struct usersData
{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
};

struct usersArray *usersArray;
int size = 0;
typedef struct usersArray usersArrayP;
typedef usersArrayP usersArrayPtr;
typedef struct usersData usersData;
typedef usersData usersDataPtr;

/*this function returns a unique hash code for given key.*/
int hashCode(int key)
{
    return (key % CAPACITY);
}

/*this function starts array list and initiliazes values as -1 and null.*/
void initialArray()
{
    usersArray = (struct usersArray *) malloc(sizeof(struct usersArray) * CAPACITY);
    int i;
    for(i = 0; i < CAPACITY; i++)
    {
        usersArray[i].key = -1;
        usersArray[i].next = NULL;
        usersArray[i].data = NULL;
    }
}

void insert(int key, char name[], char surname[])
{
    int index = hashCode(key); //holds index for given key.
    int preindex = index + 1;

    //checking index 0.
    if(index == 0)
    {
        //checking whether first element of index 0 is initialized or not.
        if(usersArray[index].key == -1)
        {
            usersArray[index].next = NULL;
            usersArray[index].key = key;
            usersDataPtr *iterData = usersArray[index].data;
            iterData = (usersDataPtr *) malloc(sizeof(usersDataPtr));
            strcpy(iterData->name, name);
            strcpy(iterData->surname, surname);
            return;
        }

        //first element has created. so this will check next elements.
        if(usersArray[index].key != -1)
        {
            usersArrayPtr *iterArray = usersArray;
            //it will search until next element is equal null.
            while(iterArray[index].next != NULL)
                iterArray[index].next = iterArray[index].next->next;

            iterArray[index].next = (struct usersArray *) malloc(sizeof(struct usersArray));
            iterArray[index].next->next = NULL;
            iterArray[index].next->key = key;
            usersDataPtr *iterData = usersArray[index].next->data;
            iterData = (usersDataPtr *) malloc(sizeof(usersDataPtr));
            strcpy(iterData->name, name);
            strcpy(iterData->surname, surname);
            return;
        }
    }

    //checking if there is data or not for current key.
    if(usersArray[preindex].key == -1)
    {
        usersArray[preindex].key = key;
        usersDataPtr *iterData = usersArray[preindex].data;
        iterData = (usersDataPtr *) malloc(sizeof(usersDataPtr));
        strcpy(iterData->name, name);
        strcpy(iterData->surname, surname);
        usersArray[preindex].next = NULL;
        return;
    }

    //there is data which has created before. so they must connect them with using 'next'.
    if(usersArray[preindex].key != -1)
    {
        usersArrayPtr *iterArray = usersArray;
        //searching until there is no data.
        while(iterArray[preindex].next != NULL)
            iterArray[preindex].next = iterArray[preindex].next->next;

        iterArray[preindex].next = (struct usersArray *) malloc(sizeof(struct usersArray));
        iterArray[preindex].next->next = NULL;
        iterArray[preindex].next->key = key;
        usersDataPtr *iterData = iterArray[preindex].next->data;
        iterData = (usersDataPtr *) malloc(sizeof(usersDataPtr));
        strcpy(iterData->name, name);
        strcpy(iterData->surname, surname);
        return;
    }
}

int main()
{
    printf("%d\n", 193%CAPACITY);
    return 0;
}
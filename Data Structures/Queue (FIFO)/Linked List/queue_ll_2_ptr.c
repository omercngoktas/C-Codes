#include <stdio.h>
#include <stdlib.h>

struct queue
{
    int data;
    struct queue *next;
    struct queue *prev;
};

typedef struct queue queue;
typedef queue queuePtr;
queue *headerNode = NULL;
queue *lastNode = NULL;

void enqueue(int number)
{
    if(headerNode == NULL)
    {
        headerNode = (queuePtr *) malloc(sizeof(queuePtr));
        headerNode->next = NULL;
        headerNode->prev = NULL;
        headerNode->data = number;
        lastNode = headerNode;
        return;
    }

    queuePtr *iter = lastNode;
    iter->next = (queuePtr *) malloc(sizeof(queuePtr));
    iter->next->data = number;
    lastNode = lastNode->next;
    lastNode->next = NULL;
    lastNode->prev = iter;
    return;
}

int dequeue()
{
    if(headerNode == NULL)
    {
        printf("There is no number to delete.\n");
        return -1;
    }

    int numberToReturn;
    queuePtr *temp = headerNode;
    if(headerNode->next == NULL)
    {
        free(headerNode->next);
        numberToReturn = headerNode->data;
        free(headerNode);
        headerNode = NULL;
        return numberToReturn;
    }

    headerNode = headerNode->next;
    headerNode->prev = NULL;
    numberToReturn = temp->data;
    free(temp);
    return numberToReturn;
}

void displayNumbers()
{
    if(headerNode == NULL)
    {
        printf("There is no number to list.\n");
        return;
    }

    queuePtr *iter = headerNode;
    while(iter != NULL)
    {
        printf("%d->", iter->data);
        iter = iter->next;
    }
    printf("NULL\n");
}

void displayReverse()
{
    if(headerNode == NULL)
    {
        printf("There is no number to list.\n");
        return;
    }

    queuePtr *iter = lastNode;
    while(iter != NULL)
    {
        printf("%d->", iter->data);
        iter = iter->prev;
    }
    printf("NULL\n");
}

int main()
{
    int i;
    for(i = 0; i < 50; i++)
    {
        enqueue(i);
    }
    displayNumbers();
    displayReverse();
    printf("%d dequeued.\n", dequeue());
    printf("%d dequeued.\n", dequeue());
    printf("%d dequeued.\n", dequeue());
    printf("%d dequeued.\n", dequeue());
    displayNumbers();
    displayReverse();
    return 0;
}
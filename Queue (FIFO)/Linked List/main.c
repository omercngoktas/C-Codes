#include <stdio.h>
#include <stdlib.h>

typedef struct Numbers Numbers;

struct Numbers
{
    int data;
    Numbers *next;
};

Numbers *root = NULL;
Numbers *last = NULL;
int numberOfData = 0;

void enque(int numberToAdd)
{
    if(root == NULL)
    {
        root = (Numbers *) malloc(sizeof(Numbers));
        root->data = numberToAdd;
        root->next = NULL;
        last = root;
        numberOfData++;
        return;
    }
    last->next = (Numbers *) malloc(sizeof(Numbers));
    last = last->next;
    last->data = numberToAdd;
    last->next = NULL;
    numberOfData++;
    return;
}

int deque()
{
    if(root == NULL)
    {
        printf("There is no number to pop.\n");
        return -1;
    }
    int intToReturn = root->data;
    Numbers* temp = root;
    root = root->next;
    free(temp);
    numberOfData--;

    return intToReturn;
}

void displayNumbers()
{
    if(root == NULL)
    {
        printf("There is no number to display.\n");
        return;
    }
    Numbers *iter = root;
    while(iter != NULL)
    {
        printf("%d ", iter->data);
        iter = iter->next;
    }
    printf("\n");
}


int main()
{
    displayNumbers();
    printf("%d \n", deque());
    int i;
    for(i = 0; i < 50000000; i++)
    {
        enque(i);
    }
    //displayNumbers();
    printf("%d popped.\n", deque());
    printf("%d popped.\n", deque());
    //displayNumbers();
    printf("\nNumber of data: %d\n", numberOfData);

    getchar();
    return 0;
}
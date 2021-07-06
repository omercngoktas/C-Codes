// Omercan Goktas 150119671

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct stuck
{
    int data;
    struct stuck *next;
};

typedef struct stuck stuck;
typedef stuck Node;
Node *topRoot = NULL;

void push(int numberToAdd)
{
    Node *temp = (Node *) malloc(sizeof(Node));
    temp->data = numberToAdd;
    temp->next = NULL;
    if(topRoot != NULL)
    {
        temp->next = topRoot;
    }
    topRoot = temp;
}

void pop()
{
    if(topRoot == NULL)
    {
        printf("There is no number to pop.\n");
        return;
    }
    Node *temp = topRoot;
    int poppedNumber = topRoot->data;
    topRoot = topRoot->next;
    free(temp);
    printf("%d has successfully popped.\n", poppedNumber);
}

void displayStack()
{
    Node *iter = topRoot;
    if(topRoot == NULL)
    {
        printf("There is no number to list.\n");
        return;
    }
    while(iter != NULL)
    {
        printf("%d -> ", iter->data);
        iter = iter->next;
    }
    printf("NULL\n");
}

int main()
{
    int choice, numberToAdd;
    while(true)
    {
        printf("\n1- Push a number to the list\n2- Pop a number from the list\n3- Display the list\n");
        printf("What is your choice?: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter a number to push: ");
            scanf("%d", &numberToAdd);
            push(numberToAdd);
            break;
        case 2:
            pop();
            break;
        case 3:
            displayStack();
            break;
        }
    }
    return 0;
}
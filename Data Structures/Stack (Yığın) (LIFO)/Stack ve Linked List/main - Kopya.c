#include <stdio.h>
#include <stdlib.h>

typedef struct Numbers Numbers;

struct Numbers
{
    int data;
    Numbers *next;
};

Numbers *push(Numbers *root, int numberToAdd)
{
    if(root == NULL)
    {
        root = (Numbers *) malloc(sizeof(Numbers));
        root->data = numberToAdd;
        root->next = NULL;
        return root;
    }
    Numbers *iter = root;
    while(iter->next != NULL)
    {
        iter = iter->next;
    }
    Numbers *temp = (Numbers *) malloc(sizeof(Numbers));
    temp->data = numberToAdd;
    temp->next = NULL;
    iter->next = temp;
    return root;
}

int pop(Numbers *root)
{
    if(root == NULL)
    {
        printf("There is no number to pop.\n");
        return -1;
    }
    Numbers *iter = root;
    Numbers *temp;
    int numberToReturn;
    if(root->next == NULL)
    {
        numberToReturn = root->data;
        free(root);
        root == NULL;
        return numberToReturn;
    }
    while(iter->next->next != NULL)
    {
        iter = iter->next;
    }
    temp = iter->next;
    numberToReturn = temp->data;
    iter->next = NULL;
    free(temp);
    return numberToReturn;
}

void displayNumbers(Numbers *root)
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
    Numbers *node = NULL;
    node = push(node, 15);
    node = push(node, 72);
    node = push(node, 54);
    node = push(node, 1234);
    node = push(node, 49);
    displayNumbers(node);
    pop(node);
    displayNumbers(node);
    pop(node);
    displayNumbers(node);
    pop(node);
    displayNumbers(node);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct Numbers Numbers;

struct Numbers
{
    int number;
    Numbers *prev;
    Numbers *next;
};

Numbers *addNumber(Numbers *root, int numberToAdd)
{
    if(root == NULL)
    {
        root = (Numbers *) malloc(sizeof(Numbers));
        root->number = numberToAdd;
        root->next = NULL;
        root->prev = NULL;
        return root;
    }
    Numbers *iter = root;
    Numbers *temp;
    if(root->number > numberToAdd)
    {
        temp = (Numbers *) malloc(sizeof(Numbers));
        temp->number = numberToAdd;
        temp->prev = NULL;
        temp->next = root;
        root->prev = temp;
        return temp;
    }
    while(iter->next->number < numberToAdd && iter->next != NULL)
    {
        iter = iter->next;
    }
    temp = (Numbers *) malloc(sizeof(Numbers));
    temp->number = numberToAdd;
    temp->next = iter->next;
    temp->prev = iter;
    iter->next = temp;
    if(temp->next == NULL) temp->next->prev = temp;
    return root;
}

void displayNumbers(Numbers *root)
{
    Numbers *iter = root;
    printf("%d ", iter->number);
    while(iter->next != NULL)
    {
        iter = iter->next;
        printf("%d ", iter->number);
    }
}

int main()
{
    Numbers *node;
    node = addNumber(node, 5);
    node = addNumber(node, 50);
    node = addNumber(node, 25);
    node = addNumber(node, 19);
    node = addNumber(node, 1);
    node = addNumber(node, 65);
    displayNumbers(node);

    

    return 0;
}
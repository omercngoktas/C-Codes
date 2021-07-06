#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int number;
    struct Node *next;
};

void displayNode(struct Node *r)
{
    while(r != NULL)
    {
        printf("%d ", r->number);
        r = r->next;
    }
}

struct Node *addNode(struct Node *r, int x)
{
    if(r == NULL) // checking if root is empty.
    {
        r = (struct Node*) malloc(sizeof(struct Node)); // allocating memory.
        r->number = x; // assigning x value to root.
        r->next = NULL; // assigning NULL value to root->next;
        return r;
    }
    if(r->number > x)
    {
        struct Node *temp = (struct Node*) malloc(sizeof(struct Node));
        temp->number = x;
        temp->next = r;
        return temp;
    }
    struct Node *iter = r;
    while(iter->next != NULL && iter->next->number < x)
    {
        iter = iter->next;
    }
    struct Node *temp = (struct Node*) malloc(sizeof(struct Node));
    temp->number = x;
    temp->next = iter->next;
    iter->next = temp;
    return r;
}


int main()
{
    printf("girdi\n");
    struct Node *root;
    root = NULL;

    int numbers[] = {1, 34, 23, 67, 12, 26, 78, 3}, i;
    for(i = 0; i < 8; i++)
    {
        root = addNode(root, numbers[i]);
    }
        
    displayNode(root);
    return 0;    
}
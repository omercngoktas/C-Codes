#include <stdio.h>
#include <stdlib.h>

struct Numbers
{
    int number;
    struct Numbers *next;
};

typedef struct Numbers Node;

Node *addNumber(Node *root, int numberToAdd)
{
    if(root == NULL)
    {
        root = (Node *) malloc(sizeof(Node));
        root->number = numberToAdd;
        root->next = root;
        return root;
    }
    Node *iter = root;
    Node *temp;
    if(root->number > numberToAdd)
    {
        temp = (Node *) malloc(sizeof(Node));
        temp->number = numberToAdd;
        temp->next = root;
        while(iter->next != root)
        {
            iter = iter->next;
        }
        iter->next = temp;
        return temp;
    }
    while(iter->next->number < numberToAdd && iter->next != root)
    {
        iter = iter->next;
    }
    temp = (Node *) malloc(sizeof(Node));
    temp->next = iter->next;
    iter->next = temp;
    temp->number = numberToAdd;
    return root;
}

Node *deleteNumber(Node *root, int numberToDelete)
{
    if(root == NULL)
    {
        printf("There is no number to delete.\n");
        return root;
    }
    Node *iter = root;
    Node *temp;
    if(root->number == numberToDelete)
    {
        while(iter->next != root)
        {
            iter = iter->next;
        }
        iter->next = root->next;
        free(root);
        return iter->next;
    }
    while(iter->next->number != numberToDelete && iter->next != root)
    {
        iter = iter->next;
    }
    if(iter->next == root)
    {
        printf("Number could not find to delete.\n");
        return root;
    }
    temp = iter->next;
    iter->next = iter->next->next;
    free(temp);
    return root;

}

void displayNumbers(Node *root)
{
    if(root == NULL)
    {
        printf("There is no number to display.\n");
        return;
    }
    Node *iter = root;
    printf("%d ", root->number);
    while(iter->next != root)
    {
        iter = iter->next;
        printf("%d ", iter->number);
    }
    printf("\n");
}

int main()
{
    Node *root;
    root = NULL;
    int i;
    for(i = 100; i > 0; i--)
    {
        root = addNumber(root, i);
    }
    displayNumbers(root);
    root = deleteNumber(root, 15);
    root = deleteNumber(root, 150);
    root = deleteNumber(root, 1);
    root = deleteNumber(root, 0);

    displayNumbers(root);
    return 0;
}
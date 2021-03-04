#include <stdio.h>
#include <stdlib.h>

struct Numbers
{
    int number;
    struct Numbers *next;
};

typedef struct Numbers Node;
int numberOfNodes = 0;

Node *addNode(Node *root, int numberToAdd)
{
    if(root == NULL)
    {
        root = (Node *) malloc(sizeof(Node));
        root->number = numberToAdd;
        root->next = NULL;
        numberOfNodes += 1;
        return root;
    }
    Node *iter = root;
    Node *temp;
    while(iter->next != NULL)
    {
        iter = iter->next;
    }
    temp = (Node *) malloc(sizeof(Node));
    temp->number = numberToAdd;
    temp->next = NULL;
    iter->next = temp;
    numberOfNodes += 1;
    return root;
}

Node *delNode(Node *root, int numberToDelete)
{
    if(root == NULL) //checking if root is NULL.
    {
        printf("There is no number to delete.\n");
        return root;
    }
    Node *iter = root;
    Node *temp;
    if(root->number == numberToDelete) //checking if the first element of the linked list equals to number to delete.
    {
        temp = root;
        root = root->next;
        numberOfNodes -= 1;
        printf("%d popped. %d number(s) have(s) left.\n", temp->number, numberOfNodes);
        free(temp);
        return root;
    }
    while(iter->next != NULL && iter->next->number != numberToDelete) //searching number to delete on iter which was created from root.
    {
        iter = iter->next;
    }
    if(iter->next == NULL) //after searching number, if iter->next is NULL, that means number could not find.
    {
        printf("%d is not in the linked list.\n", numberToDelete);
        return root;
    }
    temp = iter->next;
    iter->next = iter->next->next;
    numberOfNodes -= 1;
    printf("%d popped. %d number(s) have(s) left.\n", temp->number, numberOfNodes);
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
    while(root != NULL)
    {
        printf("%d ", root->number);
        root = root->next;
    }
    printf("\n%d number was listed.\n", numberOfNodes);
}

Node *sortNumbers(Node *root)
{
    if(root == NULL)
    {
        printf("There is no number to delete.\n");
        return root;
    }
    int i, j, tempNumber;
    Node *iter = root;
    for(i = 0; i < numberOfNodes; i++)
    {   
        for(j = 0; j < numberOfNodes - 1 - i; j++)
        {
            if(iter->number > iter->next->number)
            {
                tempNumber = iter->number;
                iter->number = iter->next->number;
                iter->next->number = tempNumber;
            }
            iter = iter->next;
        }
        iter = root;
    }
    return root;
}

int main()
{
    Node *node = NULL;
    int i;
    for(i = 100; i > 0; i--)
    {
        node = addNode(node, i);
    }
    displayNumbers(node);
    for(i = 5; i < 15; i++)
    {
        node = delNode(node, i);
    }
    displayNumbers(node);
    node = delNode(node, 213416534);
    node = delNode(node, 1);
    node = sortNumbers(node);
    displayNumbers(node);
    return 0;
}
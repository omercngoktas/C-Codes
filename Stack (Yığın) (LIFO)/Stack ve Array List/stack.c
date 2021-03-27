#include <stdio.h>
#include <stdlib.h>

struct stuck
{
    int data;
    struct stuck *next;
};

typedef struct stuck stuck;
typedef stuck Node;

Node *push(Node *root, int numberToAdd)
{
    if(root == NULL)
    {
        root = (Node *) malloc(sizeof(Node));
        root->data = numberToAdd;
        root->next = NULL;
        printf("%d added to list.\n", numberToAdd);
        return root;
    }
    Node *iter = root;
    while(iter->next != NULL)
        iter = iter->next;
    iter->next = (Node *) malloc(sizeof(Node));
    iter->next->data = numberToAdd;
    iter->next->next = NULL;
    printf("%d added to list.\n", numberToAdd);
    return root;
}

int pop(Node *root)
{
    if(root == NULL)
    {
        printf("There is no number to pop.\n");
        return -1;
    }
    if(root->next == NULL)
    {
        int poppedNumber = root->data;
        root = NULL;
        return poppedNumber;
    }
    Node *iter = root;
    while(iter->next->next != NULL)
        iter = iter->next;
    int poppedNumber = iter->next->data;
    Node *temp = iter->next;
    free(temp);
    iter->next = NULL;
    return poppedNumber;
}

void displayStuck(Node *root)
{
    if(root == NULL)
    {
        printf("There is no number to list.\n");
        return;
    }
    Node *iter = root;
    printf("List: ");
    while(iter != NULL)
    {
        printf("%d ", iter->data);
        iter = iter->next;
    }
    printf("\n");
    return;
}

int main()
{
    Node *root = NULL;
    /*int i;
    for(i = 0; i < 100; i++)
    {
        root = push(root, i);
    }
    displayStuck(root);
    printf("Popped number: %d\n", pop(root));
    displayStuck(root);*/
    root = push(root, 5);
    displayStuck(root);
    root = push(root, 50);
    displayStuck(root);
    printf("%d popped.\n", pop(root));
    displayStuck(root);
    printf("%d popped.\n", pop(root));
    displayStuck(root);
    printf("%d popped.\n", pop(root));
    displayStuck(root);
    root = push(root, 540);
    displayStuck(root);

    return 0;
}
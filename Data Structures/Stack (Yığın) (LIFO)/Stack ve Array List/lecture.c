#include <stdio.h>
#include <stdlib.h>

struct stack
{
    int data;
    struct stack *next;
};

typedef struct stack stack;
typedef stack Node;

void push(Node *root, Node *top, int numberToAdd)
{
    root = (Node *) malloc(sizeof(Node));
    root->data = numberToAdd;
    root->next = top;
    top = root;
}

void pop(Node *top)
{
    Node *temp;
    temp = top;
    printf("%d popped.\n", top->data);
    top = top->next;
    free(temp);
}

void displayStack(Node *root)
{
    while(root != NULL)
    {
        printf("%d ", root->data);
        root = root->next;
    }
    printf("\n");
}

int main()
{
    Node *root, *top;
    push(root, top, 5);
    displayStack(root);
    return 0;
}
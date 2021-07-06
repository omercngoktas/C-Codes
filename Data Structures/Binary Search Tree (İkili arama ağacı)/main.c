#include <stdio.h>
#include <stdlib.h>

struct Numbers
{
    int data;
    struct Numbers *left;
    struct Numbers *right;
};
typedef struct Numbers node;

node *addNumber(node *root, int numberToAdd)
{
    if(root == NULL)
    {
        root = (node *) malloc(sizeof(node));
        root->data = numberToAdd;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    if(root->data < numberToAdd)
    {
        root->right = addNumber(root->right, numberToAdd);
        return root;
    }
    if(root->data > numberToAdd)
    {
        root->left = addNumber(root->left, numberToAdd);
        return root;
    }
}

int findNumber(node *root, int numberToFind)
{
    if(root == NULL)
    {
        return -1;
    }
    if(root->data == numberToFind)
    {
        return 1;
    }
    if(findNumber(root->right, numberToFind) == 1)
    {
        return 1;
    }
    if(findNumber(root->left, numberToFind) == 1)
    {
        return 1;
    }
}

int findMax(node *root)
{
    while(root->right != NULL)
    {
        root = root->right;
    }
    return root->data;
}

int findMin(node *root)
{
    while(root->left != NULL)
    {
        root = root->left;
    }
    return root->data;
}

node *deleteNumber(node *root, int numberToDelete)
{
    if(root == NULL)
    {
        return NULL;
    }

    if(root->data == numberToDelete)
    {
        if(root->left == NULL && root->right == NULL)
        {
            return NULL;
        }

        if(root->right != NULL)
        {
            root->data = findMin(root->right);
            root->right = deleteNumber(root->right, numberToDelete);
            return root;
        }

        if(root->left != NULL)
        {
            root->data = findMax(root->left);
            root->left = deleteNumber(root->left, numberToDelete);
            return root;
        }
    }

    if(root->data < numberToDelete)
    {
        root->right = deleteNumber(root->right, numberToDelete);
        return root;
    }

    if(root->data > numberToDelete)
    {
        root->left = deleteNumber(root->left, numberToDelete);
        return root;
    }
}

void displayNumbers(node *root)
{
    if(root == NULL)
    {
        return;
    }
    
    displayNumbers(root->left);
    printf("%d ", root->data);
    displayNumbers(root->right);
}

int main()
{
    node *root = NULL;
    root = addNumber(root, 26);
    root = addNumber(root, 32);
    root = addNumber(root, 21);
    root = addNumber(root, 13);
    displayNumbers(root);
    printf("\nMax: %d, Min: %d\n", findMax(root), findMin(root));
    if(findNumber(root, 22) == 1)
    {
        printf("Number is in binary tree.\n");
    }
    else
    {
        printf("Number is not in binary tree.\n");
    }

    return 0;
}
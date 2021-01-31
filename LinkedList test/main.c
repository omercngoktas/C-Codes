#include <stdio.h>
#include <stdlib.h>

struct linkedNumbers
{
    int number;
    struct linkedNumbers *next;
};

struct linkedNumbers *addNumber(struct linkedNumbers *root, int numberToAdd)
{
    if(root == NULL)
    {
        root = (struct linkedNumbers *) malloc(sizeof(struct linkedNumbers));
        root->number = numberToAdd;
    }
}
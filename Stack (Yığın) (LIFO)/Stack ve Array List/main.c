#include <stdio.h>
#include <stdlib.h>

int *numberList = NULL;
int size = 2;
int top = 0;

void push(int numberToAdd)
{
    if(numberList == NULL)
    {
        numberList = (int *) malloc(sizeof(int) * size);
    }
    if(top >= size)
    {
        size *= 2;
        int *numberList2 = (int *) malloc(sizeof(int) * size);
        int i;
        for(i = 0; i < size; i++)
        {
            numberList2[i] = numberList[i];
        }
        free(numberList);
        numberList = numberList2;
    }
    numberList[top] = numberToAdd;
    top++;
}

int pop()
{
    if(numberList == NULL)
    {
        printf("There is no number to pop.\n");
        return -1;
    }
    top--;
    return numberList[top];
}

void displayNumberList()
{
    if(numberList == NULL)
    {
        printf("There is no number to list.\n");
        return;
    }
    int i;
    for(i = 0; i < top; i++)
    {
        printf("%d ", numberList[i]);
    }
    printf("\nThe size of list: %d\n", size);
}

int main()
{
    int i;
    for(i = 0; i < 1024; i++)
    {
        push(i);
    }
    displayNumberList();
    return 0;
}
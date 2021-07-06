#include <stdio.h>
#include <stdlib.h>

int *numberList = NULL;
int que = 0, startQue = 0, size = 2;

void enque(int numberToAdd)
{
    if(numberList == NULL)
    {
        numberList = (int *) malloc(sizeof(int) * size);
    }
    if(que >= size)
    {
        size *= 2;
        int *numberList2 = (int *) malloc(sizeof(int) * size);
        int i;
        for(i = 0; i < size / 2; i++)
        {
            numberList2[i] = numberList[i];
        }
        free(numberList);
        numberList = numberList2;
    }
    numberList[que] = numberToAdd;
    que++;
}

int deque()
{
    if(numberList == NULL || que == startQue)
    {
        printf("There is no number to pop.\n");
        return -1;
    }
    if(que - startQue <= size / 4)
    {
        size /= 2;
        int *numberList2 = (int *) malloc(sizeof(int) * size);
        int i;
        for(i = 0; i < que - startQue; i++)
        {
            numberList2[i] = numberList[i + startQue];
        }
        que -= startQue;
        startQue = 0;
        free(numberList);
        numberList = numberList2;
    }
    return numberList[startQue++];
}

void displayNumbers()
{
    if(numberList == NULL)
    {
        printf("There is no number to list.\n");
        return;
    }
    int i;
    for(i = 0; i < que - startQue; i++)
    {
        printf("%d ", numberList[i + startQue]);
    }
    printf("\nSize: %d\n", size);
}

int main()
{
    int i;
    for(i = 0; i < 50; i++)
    {
        enque(i);
    }
    displayNumbers();
    for(i = 0; i < 49; i++)
    {
        printf("%d has popped.\n", deque());
    }
    displayNumbers();
    return 0;
}
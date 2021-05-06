#include <stdio.h>
#include <stdlib.h>

struct number
{
    int data;
    struct number *next;
};

typedef struct number number;
typedef number numberptr;
numberptr *numbernode = NULL;


int main()
{
    numbernode = (numberptr *) malloc(sizeof(numbernode));
    numbernode->next = NULL;
    numbernode->data = 5;
    numbernode->next = (numberptr *) malloc(sizeof(numbernode));
    numbernode->next->next = NULL;
    numbernode->next->data = 50;
    numbernode->next->next = (numberptr *) malloc(sizeof(numbernode));
    numbernode->next->next->next = NULL;
    numbernode->next->next->data = 500;
    numbernode->next->next->next = (numberptr *) malloc(sizeof(numbernode));
    numbernode->next->next->next->next = NULL;
    numbernode->next->next->next->data = 55;
    
    numberptr *iter = numbernode;
    numberptr *temp = iter->next;
    iter->next = iter->next->next;
    free(temp);
    printf("%d %d\n", numbernode->data, numbernode->next->data);

    
    

    return 0;
}
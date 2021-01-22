#include <stdio.h>
#include <stdlib.h>

struct List
{
    int number;
    struct List *next;
};

struct List *addNumber(struct List *root, int currentNumber)
{
    struct List *r = root;
    struct List *r2 = root;
    if(root == NULL) // checking if struct has created.
    {
        printf("%d burada ilk if\n", currentNumber);
        root = (struct List *) malloc(sizeof(struct List));
        root->number = currentNumber;
        root->next = NULL;
        r2=root;
        while(r2 != NULL)
        {
            printf("**%d**", r2->number);
            r2 = r2->next;
        }printf("\n");
        while(r2 != NULL)
        {
            printf("**%d**", r2->number);
            r2 = r2->next;
        }printf("\n");
        return root;
    }
    if(root->number > currentNumber)
    {

        r2=root;
        while(r2 != NULL)
        {
            printf("**%d**", r2->number);
            r2 = r2->next;
        }printf("\n");
        printf("%d burada ikinci if\n", currentNumber);
        root->number = currentNumber;
        root->next = NULL;
        return r;
    }
    if(root->number < currentNumber)
    {
        r2=root;
        while(r2 != NULL)
        {
            printf("**%d**", r2->number);
            r2 = r2->next;
        }printf("\n");
        printf("%d burada ucuncu if\n", currentNumber);
        if(root->next == NULL)
        {
            r2=root;
        while(r2 != NULL)
        {
            printf("**%d**", r2->number);
            r2 = r2->next;
        }printf("\n");
            printf("%d burada dorduncu if\n", currentNumber);
            root->next = (struct List *) malloc(sizeof(struct List));
            root->next->number = currentNumber;
            root->next->next = NULL;
            return r;
        }
        while(root->number < currentNumber && root->next != NULL)
        {
            r2=root;
        while(r2 != NULL)
        {
            printf("**%d**", r2->number);
            r2 = r2->next;
        }printf("\n");
            printf("%d burada while dongusu\n", currentNumber);
            root = root->next;
            if(root->next == NULL)
            {
                r2=root;
        while(r2 != NULL)
        {
            printf("**%d**", r2->number);
            r2 = r2->next;
        }printf("\n");
                printf("%d\n", root->number);
                printf("%d burada while ilk if\n", currentNumber);
                root->next = (struct List *) malloc(sizeof(struct List));
                root->next->number = currentNumber;
                root->next->next = NULL;
                return r;
            }
            if(root->next->number > currentNumber)
            {
                r2=root;
        while(r2 != NULL)
        {
            printf("**%d**", r2->number);
            r2 = r2->next;
        }printf("\n");
                printf("%d burada while ikinci if\n", currentNumber);
                root = root->next;
                root->number = currentNumber;
                root->next = NULL;
                return r;
            }
        }
        if(root->next == NULL)
        {
            r2=root;
        while(r2 != NULL)
        {
            printf("**%d**", r2->number);
            r2 = r2->next;
        }printf("\n");
            root->next = (struct List *) malloc(sizeof(struct List));
            root->next->number = currentNumber;
            root->next->next = NULL;
            return r;
        }
    }
}

void displayLinkedList(struct List *r)
{
    while(r != NULL)
    {
        printf("%d ", r->number);
        r = r->next;
    }
}

int main()
{
    struct List *root;
    root = NULL;
    int numberList[][10] = {1204,1515,1001,1441,1980,1345,24566,17895};
    int i, j, temp;
    //root = addNumber(root, numberList[0][0]);

    /*for(i = 0; i < 8; i++)
    {
        printf("%d ", numberList[0][i]);
    }
    printf("\n");

    for(i = 0; i < 8; i++)
    {
        for(j = i + 1; j < 8; j++)
        {
            if(numberList[0][i] > numberList[0][j])
            {
                temp = numberList[0][i];
                numberList[0][i] = numberList[0][j];
                numberList[0][j] = temp;
            }
        }
    }
    for(i = 0; i < 8; i++)
    {
        printf("%d ", numberList[0][i]);
    }*/

    /*for(i = 0; i < 8; i++)
    {
        for(j = i + 1; j < 8; j++)
        {
            addNumber(root, numberList[0][j]);
        }
    }*/
    /*root = addNumber(root, 1204);
    //displayLinkedList(root);
    root = addNumber(root, 1505);
    //displayLinkedList(root);
    root = addNumber(root, 1705);
    root = addNumber(root, 2000);
    root = addNumber(root, 2001);
    root = addNumber(root, 176);
    root = addNumber(root, 1705);
    root = addNumber(root, 2000);
    root = addNumber(root, 2001);
    root = addNumber(root, 1800);*/

    for(i = 0; i < 8; i++)
    {
        for(j = i; j < 8; j++)
        {
            root = addNumber(root, numberList[0][j]);
        }
    }

    
    displayLinkedList(root);

    return 0;
}
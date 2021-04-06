#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 50

struct customer
{
    int id;
    char name[SIZE];
    char surname[SIZE];
    struct basket *basketList;
    struct customer *next;
};

struct product
{
    int id;
    int price;
    char name[SIZE];
    char category[SIZE];
    struct product *next;
};

struct basket
{
    int id;
    int amount;
    struct product *productList;
    struct basket *next;
};

typedef struct customer customer;
typedef customer customerPtr;
customerPtr *customerNode = NULL;

typedef struct product product;
typedef product productPtr;
productPtr *productNode = NULL;

typedef struct basket basket;
typedef basket basketPtr;

int main()
{
    /*customerNode = (customerPtr *) malloc(sizeof(customerPtr));
    customerNode->next = NULL;
    customerNode->id = 1;
    strcpy(customerNode->name, "Omercan");
    strcpy(customerNode->surname, "Goktas");
    customerNode->basketList = NULL;
    if(customerNode->basketList == NULL)
    {
        customerNode->basketList = (basketPtr *) malloc(sizeof(basketPtr));
        customerNode->basketList->next = NULL;
        customerNode->basketList->productList = NULL;
    }*/
    if(customerNode == NULL)
    {
        customerNode->basketList = NULL;
        printf("test\n");
    }
    printf("selam");

    return 0;
}
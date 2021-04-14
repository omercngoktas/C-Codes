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

void linkProducts(int productID, char productName[], char category[], int price);
void productText();

void productText()
{
    char productName[SIZE], productCategory[SIZE];
    int productId, productPrice;

    FILE *productText = fopen("product.txt", "r");
    if(productText == NULL)
    {
        printf("product.txt doesn't exist. Check the file.\n");
        return;
    }
    while(!feof(productText))
    {
        fscanf(productText, "%d %s %s %d", &productId, productName, productCategory, &productPrice);
        if(feof(productText))
        {
            break;
        }
        linkProducts(productId, productName, productCategory, productPrice);
    }
}

void linkProducts(int productID, char productName[], char category[], int price)
{
    if(productNode == NULL)
    {
        productNode = (productPtr *) malloc(sizeof(productPtr));
        productNode->id = productID;
        productNode->price = price;
        strcpy(productNode->name, productName);
        strcpy(productNode->category, category);
        productNode->next = NULL;
        return;
    }

    productPtr *iter = productNode;

    if(strcmp(productName, productNode->name) < 0)
    {
        printf("%s < %s\n", productName, iter->name);
        productPtr *temp = (productPtr *) malloc(sizeof(productPtr));
        temp->id = productID;
        temp->price = price;
        strcpy(temp->name, productName);
        strcpy(temp->category, category);
        temp->next = productNode;
        productNode = temp;
        return;
    }

    while(strcmp(iter->next->name, productName) < 0 && iter->next != NULL)
    {
        iter = iter->next;
        if(iter->next == NULL) break;
    }

    if(iter->next == NULL)
    {
        printf("iter.next == NULL, %s added.\n", productName);
        iter->next = (productPtr *) malloc(sizeof(productPtr)),
        iter->next->id = productID;
        strcpy(iter->next->category, category);
        strcpy(iter->next->name, productName);
        iter->next->price = price;
        iter->next->next = NULL;
        return;
    }
    printf("iter->name: %s, productName: %s\n", iter->next->name, productName);

    productPtr *temp = (productPtr *) malloc(sizeof(productPtr));
    temp->id = productID;
    temp->price = price;
    strcpy(temp->name, productName);
    strcpy(temp->category, category);
    temp->next = iter->next;
    iter->next = temp;
    //iter = temp;
    return;
}

void displayProducts()
{
    if(productNode == NULL)
    {
        printf("There is no product to display.\n");
        return;
    }

    productPtr *iter = productNode;

    while(iter != NULL)
    {
        printf("ID:%d\tProduct name: %s\tCategory: %s\tPrice: %d\n", iter->id, iter->name, iter->category, iter->price);
        iter = iter->next;
    }
}


int main()
{
    productText();
    displayProducts();

    return 0;
}
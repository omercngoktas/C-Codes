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

void linkCustomers(int id, char name[], char surname[]);
void linkProducts(int id, char name[], char category[], int price);
void linkBaskets(int customerID, int basketID, int productID);
int returnPrice(int productID);
void addProductToBasket(int customerID, int productID);
int addNewBasket(int customerID);

void customerText()
{
    char name[SIZE], surname[SIZE];
    int id;
    FILE *customerText = fopen("customer.txt", "r");
    if(customerText == NULL)
    {
        printf("customer.txt doesn't exist. Check the file.\n");
        return;
    }
    while(!feof(customerText))
    {
        fscanf(customerText,"%d %s %s", &id, name, surname);
        if(feof(customerText))
        {
            break;
        }
        linkCustomers(id, name, surname);
    }
}

void linkCustomers(int id, char name[], char surname[])
{
    if(customerNode == NULL)
    {
        customerNode = (customerPtr *) malloc(sizeof(customerPtr));
        customerNode->id = id;
        strcpy(customerNode->name, name);
        strcpy(customerNode->surname, surname);
        customerNode->next = NULL;
        return;
    }
    customerPtr *iter = customerNode;
    while(iter->next != NULL)
    {
        iter = iter->next;
    }
    iter->next = (customerPtr *) malloc(sizeof(customerPtr));
    iter = iter->next;
    iter->id = id;
    strcpy(iter->name, name);
    strcpy(iter->surname, surname);
    iter->basketList = NULL;
    iter->next = NULL;
}

void displayCustomers()
{
    if(customerNode == NULL)
    {
        printf("There is no customer to display.\n");
        return;
    }
    customerPtr *iter = customerNode;
    while(iter != NULL)
    {
        printf("ID: %d\tName: %s\tSurname: %s\n", iter->id, iter->name, iter->surname);
        iter = iter->next;
    }
}

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

void linkProducts(int id, char name[], char category[], int price)
{
    if(productNode == NULL)
    {
        productNode = (productPtr *) malloc(sizeof(productPtr));
        productNode->id = id;
        productNode->price = price;
        strcpy(productNode->name, name);
        strcpy(productNode->category, category);
        productNode->next = NULL;
        return;
    }
    productPtr *iter = productNode;
    while(iter->next != NULL)
    {
        iter = iter->next;
    }
    iter->next = (productPtr *) malloc(sizeof(productPtr));
    iter = iter->next;
    iter->id = id;
    iter->price = price;
    strcpy(iter->name, name);
    strcpy(iter->category, category);
    iter->next = NULL;
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

int returnPrice(int productID)
{
    productPtr *iter = productNode;
    if(productNode->id == productID)
    {
        return productNode->price;
    }
    while(iter->next != NULL)
    {
        if(iter->next->id == productID)
        {
            return iter->next->price;
        }
        iter = iter->next;
    }
    return -1;
}

void basketText()
{
    int customerID, productID, basketID;
    FILE *basketText = fopen("basket.txt", "r");
    if(basketText == NULL)
    {
        printf("dosya bulunamadi.\n");
        return;
    }
    while(!feof(basketText))
    {
        fscanf(basketText, "%d %d %d", &customerID, &basketID, &productID);
        if(feof(basketText))
        {
            break;
        }
        //linkBaskets(customerID, basketID, productID);
        //printf("%d %d %d\n", customerID, basketID, productID);
        //linkBaskets(customerID, basketID, productID);
    }
}

void linkBaskets(int customerID, int basketID, int productID)
{
    customerPtr *iter = customerNode;
    int productPrice = returnPrice(productID);

    while(iter != NULL && iter->id != customerID)
    {
        iter = iter->next;
    }

    if(iter == NULL)
    {
        printf("Please check the customer ID.\n");
        return;
    }

    if(iter->basketList == NULL)
    {
        iter->basketList = (basketPtr *) malloc(sizeof(basketPtr));
        iter->basketList->id = basketID;
        iter->basketList->productList = (productPtr *) malloc(sizeof(productPtr));
        iter->basketList->productList->id = productID;
        iter->basketList->amount = 0;
        iter->basketList->amount += productPrice;
        iter->basketList->productList->next = NULL;
        iter->basketList->next = NULL;
        return;         
    }

    while(iter->basketList->next != NULL && iter->basketList->id <= basketID)
    {
        iter->basketList = iter->basketList->next;
    }

    if(iter->basketList->next == NULL)
    {
        iter->basketList->next = (basketPtr *) malloc(sizeof(basketPtr));
        iter->basketList->next->next = NULL;
        iter->basketList = iter->basketList->next;
        iter->basketList->id = basketID;
        iter->basketList->amount = 0;
        iter->basketList->amount += productPrice;
        iter->basketList->productList = (productPtr *) malloc(sizeof(productPtr));
        iter->basketList->productList->next = NULL;
        iter->basketList->productList->id = productID;
        return;
    }

    if(iter->basketList->next->id == basketID)
    {
        iter->basketList = iter->basketList->next;
        if(iter->basketList->productList == NULL)
        {
            iter->basketList->productList = (productPtr *) malloc(sizeof(productPtr));
            iter->basketList->productList->next = NULL;
            iter->basketList->productList->id = productID;
            iter->basketList->amount += productPrice;
            return;
        }

        while(iter->basketList->productList->next != NULL)
        {
            iter->basketList->productList = iter->basketList->productList->next;
        }

        iter->basketList->productList->next = (productPtr *) malloc(sizeof(productPtr));
        iter->basketList->productList->next->next = NULL;
        iter->basketList->productList->next->id = productID;
        iter->basketList->next->amount += productPrice;
    }
}

int main()
{
    productText();
    customerText();
    basketText();
    linkBaskets(11, 2,2);
    return 0;
}
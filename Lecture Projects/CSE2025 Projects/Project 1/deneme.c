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

void linkBaskets(int customerID, int basketID, int productID)
{
    customerPtr *iterCustomer = customerNode;
	int productPrice = returnPrice(productID);
    printf("\n%d listeye eklenecek.\n", productID);
	
	while(iterCustomer->id != customerID) //searching for customer according to customerID.
	{
		iterCustomer = iterCustomer->next;
        if(iterCustomer == NULL) //means that requested customer is not in the linked list.
        {
            printf("Please check the customer id.\n");
            return;
        }
	}

    if(iterCustomer->basketList == NULL)
    {
        printf("%d. %s icin ilk basket olusturuldu.\n", iterCustomer->id, iterCustomer->name);
        iterCustomer->basketList = (basketPtr *) malloc(sizeof(basketPtr));
        iterCustomer->basketList->id = basketID;
        iterCustomer->basketList->amount = 0;
        iterCustomer->basketList->productList = (productPtr *) malloc(sizeof(productPtr));
        iterCustomer->basketList->productList->id = productID;     
        iterCustomer->basketList->amount += productPrice;
        iterCustomer->basketList->next = NULL;
        iterCustomer->basketList->productList->next = NULL;
        printf("%d.product, %d.baskete eklendi.\n", iterCustomer->basketList->productList->id, iterCustomer->basketList->id);
        printf("%d->NULL\n\n", iterCustomer->basketList->productList->id);
        return;
    }

    basketPtr *iterBasket = iterCustomer->basketList;
    printf("iterbasket->id: ");
    while(iterBasket->next != NULL)
    {
        printf("%d->", iterBasket->id);
        if(iterBasket->next->id == basketID)
        {
            printf("id'ler esit dongu kirildi.\n");
            iterBasket = iterBasket->next;
            break;
        }
        iterBasket = iterBasket->next;
    }

    if(iterBasket->id == basketID)
    {
        printf("basketID'ler esit.\n");
        printf("basketID: %d, productID: %d\n", basketID, productID);
        productPtr *iterProduct = iterBasket->productList;

        while(iterProduct->next != NULL)
        {
            printf("%d->", iterProduct->id);
            iterProduct = iterProduct->next;
        }
        printf("%d->", iterProduct->id);

        iterProduct->next = (productPtr *) malloc(sizeof(productPtr)),
        iterProduct->next->id = productID;
        iterProduct->next->next = NULL;
        iterBasket->amount += productPrice;
        printf("%d->NULL\n", iterProduct->next->id);
        return;
    }

    if(iterBasket->next == NULL)
    {
        printf("iterbasket nulldur.\n");
        printf("productID: %d, basketID: %d ortadaki if\n", productID, basketID);
        iterBasket->next = (basketPtr *) malloc(sizeof(basketPtr));
        iterBasket = iterBasket->next;
        iterBasket->id = basketID;
        iterBasket->amount = 0;
        iterBasket->productList = (productPtr *) malloc(sizeof(productPtr));
        iterBasket->productList->id = productID;
        iterBasket->amount += productPrice;
        iterBasket->next = NULL;
        iterBasket->productList->next = NULL;
        printf("%d->NULL\n\n", iterBasket->productList->id);
        return;
    }

    

    
}

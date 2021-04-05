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

void linkCustomers(int id, char name[], char surname[]);
void linkProducts(int id, char name[], char category[], int price);
void linkBaskets(int customerID, int basketID, int productID);

void basketText()
{
    char customerID, basketID, productID;
    FILE *basketText = fopen("basket.txt", "r");
    if(basketText == NULL)
    {
        printf("basket.txt doesn't exist. Check the file.\n");
        return;
    }
    while(!feof(basketText))
    {
        fscanf(basketText, "%d %d %d", &customerID, &basketID, &productID);
        if(feof(basketText))
        {
            break;
        }
        linkBaskets(customerID, basketID, productID);
    }
    
}

int returnPrice(int productID)
{
    productPtr *iter = productNode;
    while(iter->id != productID)
    {
        if(iter->next == NULL)
        {
            //printf("Please check the product ID.\n");
            return -1;
        }
        iter = iter->next;
    }
    return iter->price;
}

void linkBaskets(int customerID, int basketID, int productID)
{
    customerPtr *iter = customerNode;
    while(iter->id != customerID)
    {
        if(iter->next == NULL)
        {
            printf("Please check the customer ID.\n");
            return;
        }
        iter = iter->next;
    }
    if(iter->basketList == NULL)
    {
        if(returnPrice(productID) == -1)
        {
            printf("Please check the product ID.\n");
            return;
        }
        iter->basketList = (struct basket *) malloc(sizeof(struct basket));
        iter->basketList->next = NULL;
        iter->basketList->id = basketID;
        iter->basketList->amount = 0;
        iter->basketList->productList = (struct product *) malloc(sizeof(struct product));
        iter->basketList->productList->next = NULL;
        iter->basketList->productList->id = productID;
        iter->basketList->amount += returnPrice(productID);
        return;
    }
    if(iter->basketList->id > basketID)
    {
        while(iter->basketList->next != NULL || iter->basketList->next->id < basketID)
        {
            iter->basketList = iter->basketList->next;
        }
        if(iter->basketList->next == NULL)
        {
            iter->basketList->next = (struct basket *) malloc(sizeof(struct basket));
            iter->basketList = iter->basketList->next;
            iter->basketList->next = NULL;
            iter->basketList->amount = 0;
            if(iter->basketList->productList == NULL)
            {
                iter->basketList->productList = (struct product *) malloc(sizeof(struct product));
                iter->basketList->productList->next = NULL;
                iter->basketList->productList->id = productID;
                iter->basketList->amount += returnPrice(productID);
                return;
            }
            while(iter->basketList->productList->next != NULL)
            {
                iter->basketList->productList = iter->basketList->productList->next;
            }
            iter->basketList->productList->next = (struct product *) malloc(sizeof(struct product));
            iter->basketList->productList->next->next = NULL;
            iter->basketList->productList->next->id = productID;
            return;
            
        }
    }
    iter->basketList = (struct basket *) malloc(sizeof(struct basket));
    iter->basketList->id = basketID;
    iter->basketList->amount = 0;
    iter->basketList->next = NULL;
    printf("amount: %d\n", iter->basketList->amount);

}

void customerText()
{
    char name[SIZE], surname[SIZE];
    int id;
    FILE *customerText = fopen("customer1.txt", "r");
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

void addCustomer()
{
    char nameToAdd[SIZE], surnameToAdd[SIZE];
    int idToAdd;
    printf("\nEnter a new customer name: ");
    scanf("%s", nameToAdd);
    printf("Enter a new customer surname: ");
    scanf("%s", surnameToAdd);
    customerPtr *iter = customerNode;
    customerPtr *iter2 = customerNode;
    while(iter != NULL)
    {
        if(strcmp(iter->name, nameToAdd) == 0)
        {
            printf("%s has taken by another customer.\n", nameToAdd);
            return;
        }
        iter = iter->next;
    }
    while(iter2->next != NULL)
    {
        iter2 = iter2->next;
    }
    idToAdd = iter2->id + 1;
    linkCustomers(idToAdd, nameToAdd, surnameToAdd);
}

void removeCustomer()
{
    char nameToRemove[SIZE], surnameToRemove[SIZE];
    printf("Enter a customer name to remove: ");
    scanf("%s", nameToRemove);
    printf("Enter a customer surname to remove: ");
    scanf("%s", surnameToRemove);
    customerPtr *iter = customerNode;
    customerPtr *temp;
    if(strcmp(customerNode->name, nameToRemove) == 0)
    {
        if(strcmp(customerNode->surname, surnameToRemove) == 0)
        {
            temp = customerNode;
            customerNode = customerNode->next;
            free(temp);
            return;
        }
        printf("Check surname that you entered.\n");
        return;
    }
    while(strcmp(iter->next->name, nameToRemove) != 0)
    {
        iter = iter->next;
        if(iter->next == NULL)
        {
            printf("'%s %s' is not in the list.\n", nameToRemove, surnameToRemove);
            return;
        }
    }
    if(strcmp(iter->next->surname, surnameToRemove) != 0)
    {
        printf("Please check surname that you entered.\n");
        return;
    }
    if(strcmp(iter->next->name, nameToRemove) == 0)
    {
        if(strcmp(iter->next->surname, surnameToRemove) == 0)
        {
            temp = iter->next;
            iter->next = iter->next->next;
            free(temp);
        }
    }
}

void case2()
{
    int currentUserID;
    char choice;
    printf("2.a. List customers\n2.b. Select one of the customers\n");
    printf("2.c. List the products\n2.d. Add a product\n2.e. Complete shopping\n");
    printf("What is your choice? (Ex: a or b): ");
    scanf(" %c", &choice);
    switch (choice)
    {
    case 'a':
        displayCustomers();
        case2();
        break;

    case 'b':
        printf("Enter the ID of customer: ");
        scanf("%d", &currentUserID);
        customerPtr *iter = customerNode;
        while(iter->id != currentUserID)
        {
            iter = iter->next;
            if(iter == NULL)
            {
                printf("There is no customer that matches with ID that you chose.\n");
                return;
            }
        }
        printf("%d %s %s\n", iter->id, iter->name, iter->surname);
        case2();
        break;

    case 'c':
        displayProducts();
        case2();
        break;

    case 'd':
        break;

    case 'e':
        break;

    default:
        break;
    }
}

int main()
{
    int choice, choice2, currentUserID;
    customerText();
    productText();
    while(true)
    {
        printf("1- Add a customer\n2- Add basket\n3- Remove customer\n4- Exit\n");
        printf("What is your choice?: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            displayCustomers();
            addCustomer();
            displayCustomers();
            break;
        case 2:
            case2();
            break;
        case 3:
            displayCustomers();
            removeCustomer();
            displayCustomers();
            break;
        case 4:
            //linkBaskets(1, 15,15);
            printf("%d \n", returnPrice(28));
            return 0;
            break;
        default:
            break;
        }
        continue;
    }
    return 0;
}
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
        linkBaskets(customerID, basketID, productID);
        //printf("%d %d %d\n", customerID, basketID, productID);
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
        printf("productID: %d added to %s.\n", productID, iter->name);
        return;         
    }

    while(iter->basketList->next != NULL && iter->basketList->next->id <= basketID)
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
        printf("productID: %d added to %s.\n", productID, iter->name);
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
            printf("productID: %d added to %s.\n", productID, iter->name);
            return;
        }

        while(iter->basketList->productList->next != NULL)
        {
            iter->basketList->productList = iter->basketList->productList->next;
        }

        iter->basketList->productList->next = (productPtr *) malloc(sizeof(productPtr));
        iter->basketList->productList->next->next = NULL;
        iter->basketList->productList->next->id = productID;
        iter->basketList->amount += productPrice;
        printf("productID: %d added to %s.\n", productID, iter->name);
    }
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

void linkCustomers(int customerID, char customerName[], char customerSurname[])
{
    if(customerNode == NULL)
    {
        customerNode = (customerPtr *) malloc(sizeof(customerPtr));
        customerNode->id = customerID;
        strcpy(customerNode->name, customerName);
        strcpy(customerNode->surname, customerSurname);
        customerNode->next = NULL;
        customerNode->basketList = NULL;
        return;
    }

    customerPtr *iter = customerNode;

    while(iter->next != NULL)
    {
        iter = iter->next;
    }
    
    iter->next = (customerPtr *) malloc(sizeof(customerPtr));
    iter = iter->next;
    iter->id = customerID;
    strcpy(iter->name, customerName);
    strcpy(iter->surname, customerSurname);
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
    if(customerNode == NULL)
    {
        customerNode = (customerPtr *) malloc(sizeof(customerPtr));
        customerNode->next = NULL;
        customerNode->id = 1;
        strcpy(customerNode->name, nameToAdd);
        strcpy(customerNode->surname, surnameToAdd);
        customerNode->basketList = NULL;
        return;
    }
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

void addProductToBasket(int customerID, int productID)
{
    customerPtr *iter = customerNode;
    int basketListID, productPrice = returnPrice(productID);

    if(productPrice == -1) // checking product id if it exists.
    {
        printf("Please check the product ID.\n");
        return;
    }

    while(iter->id != customerID)
    {
        iter = iter->next;
    }

    if(iter == NULL)
    {
        printf("Please check the customer ID.\n");
        return;
    }

    while(iter->basketList->next != NULL)
    {
        iter->basketList = iter->basketList->next;
    }

    if(iter->basketList->productList == NULL)
    {
        iter->basketList->productList = (struct product *) malloc(sizeof(struct product));
        iter->basketList->productList->next = NULL;
        iter->basketList->productList->id = productID;
        iter->basketList->amount += productPrice;
        return;
    }

    while(iter->basketList->productList->next != NULL)
    {
        iter->basketList->productList = iter->basketList->productList->next;
    }

    iter->basketList->productList->next = (struct product *) malloc(sizeof(struct product));
    iter->basketList->productList = iter->basketList->productList->next;
    iter->basketList->productList->next = NULL;
    iter->basketList->productList->id = productID;
    iter->basketList->amount += productPrice;
}

int addNewBasket(int customerID)
{
    customerPtr *iter = customerNode;
    int basketID = 1;

    while(iter->id != customerID)
    {
        if(iter == NULL)
        {
            printf("Please check the customer ID.\n");
            return -1;
        }
        iter = iter->next;
    }

    if(iter->basketList == NULL)
    {
        iter->basketList = (struct basket *) malloc(sizeof(struct basket));
        iter->basketList->next = NULL;
        iter->basketList->productList = NULL;
        iter->basketList->amount = 0;
        iter->basketList->id = basketID;
        return 0;
    }

    while(iter->basketList->next != NULL)
    {
        iter->basketList = iter->basketList->next;
    }

    basketID = iter->basketList->id + 1;
    iter->basketList->next = (struct basket *) malloc(sizeof(struct basket));
    iter->basketList = iter->basketList->next;
    iter->basketList->next = NULL;
    iter->basketList->productList = NULL;
    iter->basketList->amount = 0;
    iter->basketList->id = basketID;
    return 0;
}

int returnBasketAmount(int customerID)
{
    customerPtr *iter = customerNode;

    while(iter->next != NULL)
    {
        iter = iter->next;
    }
    
    iter = iter->next;
    
    if(iter->basketList == NULL || iter->basketList->productList == NULL)
    {
        return -1; // it means there is no basket or product in basket for the current user. 
    }
    
    while(iter->basketList->next != NULL)
    {
        iter->basketList = iter->basketList->next;
    }

    if(iter->basketList->productList == NULL)
    {
        return -2;
    }

    return iter->basketList->amount;
}

void listSpecificProduct(int productID)
{
    productPtr *temp = productNode;
    customerPtr *iter = customerNode;
    int i = 1;

    if(temp == NULL)
    {
        printf("There is no product.\n");
        return;
    }

    if(iter == NULL)
    {
        printf("There is no customer.\n");
        return;
    }

    while(temp->next != NULL && temp->next->id != productID) temp = temp->next;

    if(temp->next == NULL)
    {
        printf("Product couldn't find.\n");
        return;
    }

    while(iter != NULL)
    {
        while(iter->basketList != NULL)
        {
            if(iter->basketList->productList == NULL)
            {
                iter->basketList = iter->basketList->next;
                continue;
            }
            while(iter->basketList->productList != NULL && iter->basketList->productList->id != productID)
            {
                iter->basketList->productList = iter->basketList->productList->next;
            }
            if(iter->basketList->productList == NULL)
            {
                break;
            }
            if(iter->basketList->productList->id == productID)
            {
                printf("%d. %s %s\n", i++, iter->name, iter->surname);
                break;
            }
        }
        iter = iter->next;
    }
}

void case2()
{
    int currentCustomerID = 0, productID, completeShopping, totalAmount, isNewBasketAdded;
    bool isCustomerSelected = false;
    char choice;
    while(true)
    {
        printf("2.a. List customers\n2.b. Select one of the customers\n");
        printf("2.c. List the products\n2.d. Add a product\n2.e. Complete shopping\n");
        printf("What is your choice? (Ex: a or b): ");
        scanf(" %c", &choice);
        
        switch (choice)
        {
        case 'a':
            displayCustomers();
            continue;

        case 'b':
            if(isCustomerSelected == true)
            {
                printf("You have already chose a customer.\n");
                continue;
            }
            printf("Enter the ID of customer: ");
            scanf("%d", &currentCustomerID);
            isNewBasketAdded = addNewBasket(currentCustomerID);
            if(isNewBasketAdded == -1)
            {
                return;
            }
            isCustomerSelected = true;
            continue;

        case 'c':
            displayProducts();
            continue;

        case 'd':
            if(isCustomerSelected == false)
            {
                printf("Please, select one of the customers to continue.\n");
                continue;
            }
            printf("Enter a product ID that will be added to the basket: ");
            scanf("%d", &productID);
            addProductToBasket(currentCustomerID, productID);
            continue;

        case 'e':
            if(isCustomerSelected == false)
            {
                printf("Please, select one of the customers to continue.\n");
                continue;
            }
            printf("If you want to complete shopping enter -1: ");
            scanf("%d", &completeShopping);
            totalAmount = returnBasketAmount(currentCustomerID);

            if(completeShopping != -1)
            {
                continue;
            }
            if(totalAmount == -1)
            {
                printf("You have never borrowed a basket or product to your basket.\n");
                return;
            }
            if(totalAmount == -2)
            {
                printf("You didn't borrow any product.");
                return;
            }
            printf("The total amount of basket: %d\n", totalAmount);
            return;

        default:
            break;
        }
    }
}
    
int main()
{
    int choice, choice2, currentUserID, specificProductID;
    customerText();
    productText();
    basketText();
    while(true)
    {
        printf("1- Add a customer\n2- Add basket\n3- Remove customer\n");
        printf("4- List the customers who boutght a specific product\n");
        printf("5- List the total shopping amounts of each customer\n6- Exit\n");
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
            displayProducts();
            printf("Enter ID of product: ");
            scanf("%d", &specificProductID);

            return 0;
            break;
        case 6:
            return 0;
        default:
            break;
        }
        continue;
    }
    return 0;
}
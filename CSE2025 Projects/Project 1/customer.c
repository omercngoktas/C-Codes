/*
Omercan Goktas 150119671
Berkan Korkmaz 150119623
Senanur Guvercinoglu 150119740
*/

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
int addNewBasket(int customerID);
void printBasketProducts();
void addProductToBasket(int customerID, int basketID, int productID);
void totalShoppingAmounts();

void basketText() //opens basket.txt and implements each basket and product to the valid customer.
{
    int customerID, productID, basketID;
    FILE *basketText = fopen("basket.txt", "r");

    if(basketText == NULL) //checking if file exists.
    {
        printf("basket.txt doesn't exist. Please check the file.\n");
        return;
    }

    while(!feof(basketText)) //going throw end of the file.
    {
        fscanf(basketText, "%d %d %d", &customerID, &basketID, &productID);
        if(feof(basketText))
        {
            break;
        }
        linkBaskets(customerID, basketID, productID);
    }
}

void linkBaskets(int customerID, int basketID, int productID) //takes information from basketText() function and implements properly.
{
    customerPtr *iterCustomer = customerNode; //it will hold valid customer.

	int productPrice = returnPrice(productID); //holds price of the valid product in order to calling function every time.
	
	while(iterCustomer->id != customerID) //searching for customer according to customerID.
	{
		iterCustomer = iterCustomer->next;

        if(iterCustomer == NULL) //means that requested customer is not in the linked list.
        {
            printf("Please check the customer id.\n");
            return;
        }
	}

    if(iterCustomer->basketList == NULL) //means there is no basket added for the valid customer before.
    {
        iterCustomer->basketList = (basketPtr *) malloc(sizeof(basketPtr));
        iterCustomer->basketList->id = basketID;
        iterCustomer->basketList->amount = 0;
        iterCustomer->basketList->productList = (productPtr *) malloc(sizeof(productPtr));
        iterCustomer->basketList->productList->id = productID;     
        iterCustomer->basketList->amount += productPrice;
        iterCustomer->basketList->next = NULL;
        iterCustomer->basketList->productList->next = NULL;
        return;
    }

    basketPtr *iterBasket = iterCustomer->basketList; //it will hold valid customer's basket list.

    while(iterBasket->next != NULL)
    {
        if(iterBasket->next->id == basketID)
        {
            iterBasket = iterBasket->next;
            break;
        }
        iterBasket = iterBasket->next;
    }

    if(iterBasket->id == basketID) //if basketID exists in basket's id list, implementing the process.
    {
        productPtr *iterProduct = iterBasket->productList;

        while(iterProduct->next != NULL)
        {
            iterProduct = iterProduct->next;
        }

        iterProduct->next = (productPtr *) malloc(sizeof(productPtr)),
        iterProduct->next->id = productID;
        iterProduct->next->next = NULL;
        iterBasket->amount += productPrice;
        return;
    }

    if(iterBasket->next == NULL) //adding end of the list.
    {
        iterBasket->next = (basketPtr *) malloc(sizeof(basketPtr));
        iterBasket = iterBasket->next;
        iterBasket->id = basketID;
        iterBasket->amount = 0;
        iterBasket->productList = (productPtr *) malloc(sizeof(productPtr));
        iterBasket->productList->id = productID;
        iterBasket->amount += productPrice;
        iterBasket->next = NULL;
        iterBasket->productList->next = NULL;
        return;
    }
}

void customerText() //opening customer.txt and sending informantion to linkCustomers().
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

void linkCustomers(int customerID, char customerName[], char customerSurname[]) //adding customers to the linked list which come from text.
{
    if(customerNode == NULL) //if there is no customer before.
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

void displayCustomers() //displays all of the customers.
{
    if(customerNode == NULL) //means there is no customer.
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

int returnPrice(int productID) //it returns the product price which is gonna adding to valid customer's basket.
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
    return -1; //means there is no product matches with productID.
}

void productText() //opening product.txt and sending informatin to linkProducts().
{
    char productName[SIZE], productCategory[SIZE];
    int productId, productPrice;

    FILE *productText = fopen("product.txt", "r");

    if(productText == NULL) //if file doesn't exist.
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

void linkProducts(int productID, char productName[], char category[], int price) //adding products which come frome text file, to linked list according to alphabetically.
{
    if(productNode == NULL) //if there is no product before.
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

    if(strcmp(productName, productNode->name) < 0) //if first product's name bigger than the productName alphabetically.
    {
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

    if(iter->next == NULL) //if productName is the biggest alphabetically.
    {
        iter->next = (productPtr *) malloc(sizeof(productPtr)),
        iter->next->id = productID;
        strcpy(iter->next->category, category);
        strcpy(iter->next->name, productName);
        iter->next->price = price;
        iter->next->next = NULL;
        return;
    }

    productPtr *temp = (productPtr *) malloc(sizeof(productPtr));
    temp->id = productID;
    temp->price = price;
    strcpy(temp->name, productName);
    strcpy(temp->category, category);
    temp->next = iter->next;
    iter->next = temp;
    return;
}

void displayProducts() //displays all of the products.
{
    if(productNode == NULL) //means there is no product in linked list.
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

void addCustomer() //adding a new customer, when selected from main menu.
{
    char nameToAdd[SIZE], surnameToAdd[SIZE];
    int idToAdd;

    printf("\nEnter a new customer name: "); //taking information.
    scanf("%s", nameToAdd);
    printf("Enter a new customer surname: ");
    scanf("%s", surnameToAdd);
    customerPtr *iter = customerNode;
    customerPtr *iter2 = customerNode;

    if(customerNode == NULL) //if there is no customer before in the linked list.
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
        if(strcmp(iter->name, nameToAdd) == 0) //checking if customer's name has taken before.
        {
            printf("%s has taken before.\n", nameToAdd);
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

void removeCustomer() //removes customer from linked list.
{
    char nameToRemove[SIZE], surnameToRemove[SIZE];

    printf("Enter a customer name to remove: "); //taking information.
    scanf("%s", nameToRemove);
    printf("Enter a customer surname to remove: ");
    scanf("%s", surnameToRemove);
    customerPtr *iter = customerNode;
    customerPtr *temp;

    if(strcmp(customerNode->name, nameToRemove) == 0) //if name matches with first node.
    {
        if(strcmp(customerNode->surname, surnameToRemove) == 0) // if surname matches with first node.
        {
            temp = customerNode;
            customerNode = customerNode->next;
            free(temp);
            return;
        }
        printf("Check surname that you entered.\n");
        return;
    }

    while(strcmp(iter->next->name, nameToRemove) != 0) //going throw linked list for valid customer.
    {
        iter = iter->next;
        if(iter->next == NULL) //customer is not in the linked list.
        {
            printf("'%s %s' is not in the list.\n", nameToRemove, surnameToRemove);
            return;
        }
    }

    if(strcmp(iter->next->surname, surnameToRemove) != 0) //surname doesn't match.
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

int addNewBasket(int customerID) //when customer selected, creating a new basket for him.
{
    customerPtr *iterCustomer = customerNode;
    int basketID = 1;

    while(iterCustomer->id != customerID)
    {
        if(iterCustomer == NULL) //customer id doesn't match with any customer.
        {
            printf("Please check the customer ID.\n");
            return -1;
        }
        iterCustomer = iterCustomer->next;
    }

    printf("You have selected:\n%d. %s %s\n\n", iterCustomer->id, iterCustomer->name, iterCustomer->surname); //printing valid customer's information.

    if(iterCustomer->basketList == NULL)
    {
        iterCustomer->basketList = (struct basket *) malloc(sizeof(struct basket));
        iterCustomer->basketList->next = NULL;
        iterCustomer->basketList->productList = NULL;
        iterCustomer->basketList->amount = 0;
        iterCustomer->basketList->id = basketID;
        return iterCustomer->basketList->id;
    }

    basketPtr *iterBasket = iterCustomer->basketList;

    while(iterBasket->next != NULL)
    {
        iterBasket = iterBasket->next;
    }

    iterBasket->next = (basketPtr *) malloc(sizeof(basketPtr));
    iterBasket->next->id = iterBasket->id + 1;
    iterBasket->next->productList = NULL;
    iterBasket->next->amount = 0;
    iterBasket->next->next = NULL;
    return iterBasket->next->id;
}

void searchSpecificProduct(int idProductToSearch) //searching for specific product who has taken before.
{
    customerPtr *iterCustomer = customerNode;
    basketPtr *iterBasket = customerNode->basketList;
    productPtr *iterProduct = iterBasket->productList;
    int howManyTaken = 0;
    
    if(returnPrice(idProductToSearch) == -1) //means product is not in the linked list.
    {
        printf("Please check the product ID. It is not in the list.\n");
        return;
    }

    while(iterCustomer != NULL)
    {
        if(iterCustomer->basketList == NULL)
        {
            iterCustomer = iterCustomer->next;
            continue;
        }
        iterBasket = iterCustomer->basketList;
        iterProduct = iterBasket->productList;

        while(iterBasket != NULL)
        {
            while(iterProduct != NULL)
            {
                if(iterProduct->id == idProductToSearch)
                {
                    printf("%d. %s %s's %d. basket\n", iterCustomer->id, iterCustomer->name, iterCustomer->surname, iterBasket->id);
                    howManyTaken++;
                    break;
                }
                iterProduct = iterProduct->next;
            }

            iterBasket = iterBasket->next;

            if(iterBasket == NULL)
            {
                break;
            }

            iterProduct = iterBasket->productList;
        }
        iterCustomer = iterCustomer->next;
    }
    
    if(howManyTaken == 0)
    {
        printf("There is no customer that has taken product %d.\n", idProductToSearch);
        return;
    }

    printf("These are the custuomers that have taken product %d.\n", idProductToSearch);  
}

int returnBasketAmount(int customerID, int basketID) //returns the basket amount for the valid customer.
{
    customerPtr *iterCustomer = customerNode;

    while(iterCustomer->id != customerID)
    {
        iterCustomer = iterCustomer->next;
        if(iterCustomer == NULL)
        {
            printf("Please check the customer ID.\n");
            return -1;
        }
    }

    basketPtr *iterBasket = iterCustomer->basketList;

    if(iterBasket != NULL)
    {
        while(iterBasket->id != basketID)
        {
            iterBasket = iterBasket->next;

            if(iterBasket == NULL)
            {
                printf("There is no basket with this ID for this customer.\n");
                return -1;
            }
        }
    }
    return iterBasket->amount;
}

void addProductToBasket(int customerID, int basketID, int productID) //adding product to valid customer's basket.
{
    customerPtr *iterCustomer = customerNode;
	int productPrice = returnPrice(productID);

    if(productPrice == -1) //product is not in the linked list.
    {
        printf("There is no product which matches with this id.\n");
        return;
    }
	
	while(iterCustomer->id != customerID) //searching for customer according to customerID.
	{
		iterCustomer = iterCustomer->next;
        if(iterCustomer == NULL) //means that requested customer is not in the linked list.
        {
            printf("Please check the customer id.\n");
            return;
        }
	}

    if(iterCustomer->basketList == NULL) //means there is no basket before.
    {   
        iterCustomer->basketList = (basketPtr *) malloc(sizeof(basketPtr));
        iterCustomer->basketList->id = basketID;
        iterCustomer->basketList->amount = 0;
        iterCustomer->basketList->productList = (productPtr *) malloc(sizeof(productPtr));
        iterCustomer->basketList->productList->id = productID;     
        iterCustomer->basketList->amount += productPrice;
        iterCustomer->basketList->next = NULL;
        iterCustomer->basketList->productList->next = NULL;
        return;
    }
    
    basketPtr *iterBasket = iterCustomer->basketList;

    while(iterBasket->next != NULL)
    {
        if(iterBasket->next->id == basketID)
        {
            iterBasket = iterBasket->next;
            break;
        }
        iterBasket = iterBasket->next;
    }

    if(iterBasket->id == basketID) //if basket has created before.
    {
        if(iterBasket->productList == NULL)
        {
            iterBasket->productList = (productPtr *) malloc(sizeof(productPtr));
            iterBasket->productList->id = productID;
            iterBasket->productList->next = NULL;
            iterBasket->amount += productPrice;
            return;
        }

        productPtr *iterProduct = iterBasket->productList;

        while(iterProduct->next != NULL)
        {
            iterProduct = iterProduct->next;
        }

        iterProduct->next = (productPtr *) malloc(sizeof(productPtr)),
        iterProduct->next->id = productID;
        iterProduct->next->next = NULL;
        iterBasket->amount += productPrice;
        return;
    }

    if(iterBasket->next == NULL) //creating basket and adding product.
    {
        iterBasket->next = (basketPtr *) malloc(sizeof(basketPtr));
        iterBasket = iterBasket->next;
        iterBasket->id = basketID;
        iterBasket->amount = 0;
        iterBasket->productList = (productPtr *) malloc(sizeof(productPtr));
        iterBasket->productList->id = productID;
        iterBasket->amount += productPrice;
        iterBasket->next = NULL;
        iterBasket->productList->next = NULL;
        return;
    }
}

void totalShoppingAmounts() //displays all of the total shopping amounts for each customer if they took any product before.
{
    customerPtr *iterCustomer = customerNode;
    if(customerNode == NULL)
    {
        printf("There is no customer to show total shopping amount.\n");
        return;
    }

    int totalAmount = 0;
    basketPtr *iterBasket = iterCustomer->basketList;

    while(iterCustomer != NULL)
    {
        while(iterBasket != NULL)
        {
            totalAmount += iterBasket->amount;
            iterBasket = iterBasket->next;
        }

        if(totalAmount != 0)
        {
            printf("%d. %s %s's total shopping amount: %d\n", iterCustomer->id, iterCustomer->name, iterCustomer->surname, totalAmount);
            totalAmount = 0;
        }

        iterCustomer = iterCustomer->next;

        if(iterCustomer == NULL)
        {
            break;
        }
        iterBasket = iterCustomer->basketList;
    }
}

void case2() //contains all of the process for menu 2.
{
    int customerID = 0, productID, completeShopping, totalAmount = 0, isNewBasketAdded;
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
            scanf("%d", &customerID);
            isNewBasketAdded = addNewBasket(customerID);
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
            addProductToBasket(customerID, isNewBasketAdded, productID);
            totalAmount = returnBasketAmount(customerID, isNewBasketAdded);
            continue;

        case 'e':
            if(isCustomerSelected == false)
            {
                printf("Please, select one of the customers to continue.\n");
                break;
            }

            printf("If you want to complete shopping enter -1: ");
            scanf("%d", &completeShopping);

            if(completeShopping != -1)
            {
                continue;
            }

            if(totalAmount == 0)
            {
                printf("You didn't add any product to your basket.\n");
                return;
            }

            if(isCustomerSelected == false || isNewBasketAdded == -1)
            {
                printf("You didn't add any basket.\n");
                return;
            }

            printf("The total amount of basket: %d\n\n", totalAmount);
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
            continue;
            
        case 2:
            case2();
            continue;

        case 3:
            displayCustomers();
            removeCustomer();
            displayCustomers();
            continue;

        case 4:
            displayProducts();
            printf("Enter ID of product to search who has taken: ");
            scanf("%d", &specificProductID);
            searchSpecificProduct(specificProductID);
            continue;

        case 5:
            totalShoppingAmounts();
            continue;

        case 6:
            return 0;

        default:
            break;
        }
        continue;
    }
    return 0;
}
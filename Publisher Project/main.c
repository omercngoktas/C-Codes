#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define SIZE 50

struct books
{
    char name[SIZE];
    char author[SIZE];
    char publisher[SIZE];
    int id;
    int price;
    int amount;
    int pageNumber;
    struct books *next;
};

struct soldBooks
{
    int idCustomer;
    int idSoldBook;
    struct soldBooks *next;
};

struct personel
{
    char name[SIZE];
    char surname[SIZE];
    int id;
    struct soldBooks *soldBooksList;
    struct personel *next;
};

struct customer
{
    char name[SIZE];
    char surname[SIZE];
    int budget;
    int id;
    struct customer *next;
};

typedef struct books books;
typedef books booksPtr;
booksPtr *booksNode = NULL;

typedef struct personel personel;
typedef personel personelPtr;
personelPtr *personelNode = NULL;

typedef struct customer customer;
typedef customer customerPtr;
customerPtr *customerNode = NULL;

typedef struct soldBooks soldBooks;
typedef soldBooks soldBooksPtr;

void booksText();
void linkBooks(int id, char name[], char author[], char publisher[], int price, int amount, int pageNumber);
void displayBooks();
void customerText();
void linkCustomers(int id, char name[], char surname[], int budget);
void displayCustomers();
void personelText();
void linkPersonels(int id, char name[], char surname[]);
void soldBooksText();
void linkSoldBooks(int idPersonel, int idCustomer, int idSoldBook);
void displaySoldBooks();

void booksText() //books.txt dosyasindan kitap bilgileri okunur ve linkBooks() fonksiyonuna gonderilir.
{
    int id, price, amount, pageNumber;
    char name[SIZE], author[SIZE], publisher[SIZE];
    FILE *booksText = fopen("books.txt", "r");
    booksPtr *iter = booksNode;
    
    if(booksText == NULL) //books.txt'nin bos oldugunu belirtir.
    {
        printf("booksText.txt dosyasinda herhangi bir kitap bulunamadi.\n");
        return;
    }

    while(!feof(booksText)) //dosyanin sonuna kadar gerekli bilgileri alir.
    {
        fscanf(booksText, "%d %s %s %s %d %d %d", &id, name, author, publisher, &price, &amount, &pageNumber);
        linkBooks(id, name, author, publisher, price, amount, pageNumber);
    }
}

void linkBooks(int id, char name[], char author[], char publisher[], int price, int amount, int pageNumber)
{
    //booksNode olusturur ve kitaplari birbirine baglar.
    if(booksNode == NULL) //daha once kitap eklenip eklenmedigini kontrol eder.
    {
        booksNode = (booksPtr *) malloc(sizeof(booksPtr));
        booksNode->id = id;
        strcpy(booksNode->name, name);
        strcpy(booksNode->author, author);
        strcpy(booksNode->publisher, publisher);
        booksNode->price = price;
        booksNode->amount = amount;
        booksNode->pageNumber = pageNumber;
        booksNode->next = NULL;
        return;
    }

    booksPtr *iter = booksNode;

    while(iter->next != NULL) //iter node'un sonunu gosterir ve gecerli kitap node'un en sonuna eklenir.
        iter = iter->next;
    
    iter->next = (booksPtr *) malloc(sizeof(booksPtr));
    iter = iter->next;
    iter->id = id;
    strcpy(iter->name, name);
    strcpy(iter->author, author);
    strcpy(iter->publisher, publisher);
    iter->price = price;
    iter->amount = amount;
    iter->pageNumber = pageNumber;
    iter->next = NULL;
}

void displayBooks()
{
    if(booksNode == NULL) //kitap olup olmadigini kontrol eder.
    {
        printf("Listelenecek herhangi bir kitap bulunamadi.");
        return;
    }

    booksPtr *iter = booksNode;

    while(iter != NULL)
    {
        printf("%d %s %s %s %d %d %d\n", iter->id, iter->name, iter->author, iter->publisher, iter->price, iter->amount, iter->pageNumber);
        iter = iter->next;
        if(iter->next == NULL)
            break;
    }
}

void customerText() //customer.txt dosyasini okuyup gecerli musteriyi linkCustomers()'a gonderir.
{
    int id, budget;
    char name[SIZE], surname[SIZE];
    FILE *customerText = fopen("customer.txt", "r");

    if(customerText == NULL) //customer.txt dosyasinin olup olmadigini kontrol eder.
    {
        printf("customer.txt dosyasi bulunamadi.\n");
        return;
    }

    while(!feof(customerText))
    {
        fscanf(customerText, "%d %s %s %d", &id, name, surname, &budget);
        if(feof(customerText))
            break;
        linkCustomers(id, name, surname, budget); //gecerli kullanicinin node'a eklenmesi icin fonksiyona gonderilir.
    }
}

void linkCustomers(int id, char name[], char surname[], int budget) //gecerli musteriyi node'a ekler.
{
   if(customerNode == NULL) //daha once node'a musteri eklenip eklenmedigini kontrol eder.
    {
        customerNode = (customerPtr *) malloc(sizeof(customerPtr));
        customerNode->id = id;
        strcpy(customerNode->name, name);
        strcpy(customerNode->surname, surname);
        customerNode->budget = budget;
        customerNode->next = NULL;
        return;
    }

    customerPtr *iter = customerNode;

    while(iter->next != NULL)
        iter = iter->next;
    
    iter->next = (customerPtr *) malloc(sizeof(customerPtr));
    iter = iter->next;
    iter->id = id;
    strcpy(iter->name, name);
    strcpy(iter->surname, surname);
    iter->budget = budget;
    iter->next = NULL;
    return;
}

void displayCustomers() //musterileri listeler.
{
    if(customerNode == NULL) //musteri node'unun bos olup olmadigini kontrol eder.
    {
        printf("Listelenecek herhangi bir kullanici bulunamadi.\n");
        return;
    }

    customerPtr *iter = customerNode;

    while(iter->next != NULL) //musteri node'unun sonuna kadar giderek musterilerin bilgilerini bastirir.
    {
        printf("ID: %d, Ad-soyad: %s %s, Bakiye: %d\n", iter->id, iter->name, iter->surname, iter->budget);
        iter = iter->next;
        if(iter->next == NULL)
            break;
    }
}

void personelText() //personelleri personel.txt'den okuyup linkPersonels() fonksiyonuna gonderir.
{
    FILE *personelText = fopen("personel.txt", "r");
    char name[SIZE], surname[SIZE];
    int id;

    if(personelText == NULL) //personel.txt'nin olup olmadigini kontrol eder.
    {
        printf("personel.txt bulunamadi.\n");
        return;
    }

    while(!feof(personelText))
    {
        fscanf(personelText, "%d %s %s", &id, name, surname);
        if(feof(personelText))
            break;
        linkPersonels(id, name, surname);
    }
}

void linkPersonels(int id, char name[], char surname[]) //gelen personel bilgilerini personel node'a ekler.
{
    if(personelNode == NULL) //daha once node'da personel olup olmadigini kontrol eder.
    {
        personelNode = (personelPtr *) malloc(sizeof(personelPtr));
        personelNode->id = id;
        strcpy(personelNode->name, name);
        strcpy(personelNode->surname, surname);
        personelNode->soldBooksList = NULL;
        personelNode->next = NULL;
        return;
    }

    personelPtr *iter = personelNode;

    while(iter->next != NULL)
        iter = iter->next;
    
    iter->next = (personelPtr *) malloc(sizeof(personelPtr));
    iter = iter->next;
    iter->id = id;
    strcpy(iter->name, name);
    strcpy(iter->surname, surname);
    iter->soldBooksList = NULL;
    iter->next = NULL;
    return;
}

void displayPersonels() //personelleri listeler.
{
    if(personelNode == NULL) //node'da personel olup olmadigini kontrol eder.
    {
        printf("Listelenecek herhangi bir personel bulunamadi.\n");
        return;
    }

    personelPtr *iter = personelNode;

    while(iter != NULL)
    {
        printf("ID: %d, Ad-Soyad: %s %s\n", iter->id, iter->name, iter->surname);
        iter = iter->next;
    }
}

void soldBooksText()
{
    FILE *soldBooksText = fopen("soldBooks.txt", "r");
    int idPersonel, idCustomer, idSoldBook;

    if(soldBooksText == NULL)
    {
        FILE *soldBooksText = fopen("soldBooks.txt", "w");
        fclose(soldBooksText);
        return;
    }

    while(!feof(soldBooksText))
    {
        fscanf(soldBooksText, "%d %d %d", &idPersonel, &idCustomer, &idSoldBook);
        if(feof(soldBooksText))
            break;
        linkSoldBooks(idPersonel, idCustomer, idSoldBook);
    }
}

void linkSoldBooks(int idPersonel, int idCustomer, int idSoldBook)
{
    personelPtr *iterPersonel = personelNode;
    customerPtr *iterCustomer = customerNode;

    while(iterPersonel->next != NULL && iterPersonel->id != idPersonel)
        iterPersonel = iterPersonel->next;

    if(iterPersonel->id != idPersonel)
    {
        printf("Personelin id'si herhangi bir personelle eslesmedi.\n");
        return;
    }

    while(iterCustomer->next != NULL && iterCustomer->id != idCustomer)
        iterCustomer = iterCustomer->next;

    if(iterCustomer->id != idCustomer)
    {
        printf("Musterinin id'si herhangi bir musteriyle eslesmedi.\n");
        return;
    }

    if(iterCustomer->id == idCustomer && iterPersonel->id == idPersonel)
    {
        soldBooksPtr *iter = iterPersonel->soldBooksList;

        if(iterPersonel->soldBooksList == NULL)
        {
            iterPersonel->soldBooksList = (soldBooksPtr *) malloc(sizeof(soldBooksPtr));
            iterPersonel->soldBooksList->idCustomer = idCustomer;
            iterPersonel->soldBooksList->idSoldBook = idSoldBook;
            iterPersonel->soldBooksList->next = NULL;
            return;
        }

        while(iter->next != NULL)
            iter = iter->next;
        
        iter->next = (soldBooksPtr *) malloc(sizeof(soldBooksPtr));
        iter = iter->next;
        iter->idCustomer = idCustomer;
        iter->idSoldBook = idSoldBook;
        iter->next = NULL;
        return;
    }
}

void displaySoldBooks()
{
    setlocale(LC_ALL, "turkish");
    personelPtr *iterPersonel = personelNode;
    customerPtr *iterCustomer = customerNode;
    booksPtr *iterBooks = booksNode;
    
    while(iterPersonel != NULL)
    {
        soldBooksPtr *iterSoldBooks = iterPersonel->soldBooksList;
        /*iterCustomer = customerNode;
        iterBooks = booksNode;*/

        if(iterSoldBooks != NULL)
        {
            printf("ID'si %d olan personel %s %s tarafindan satilan kitaplar:\n", iterPersonel->id, iterPersonel->name, iterPersonel->surname);
            while(iterSoldBooks != NULL)
            {
                while(iterCustomer->id != iterSoldBooks->idCustomer)
                    iterCustomer = iterCustomer->next;
                
                while(iterBooks->id != iterSoldBooks->idSoldBook)
                    iterBooks = iterBooks->next;
                
                printf("\t->Kitap adı: %s, %s isimli müşteriye satıldı.\n", iterBooks->name, iterCustomer->name);

                iterSoldBooks = iterSoldBooks->next;
                iterCustomer = customerNode;
                iterBooks = booksNode;
            }
            printf("\n");
        }
        iterPersonel = iterPersonel->next;
    }
}

int main()
{
    setlocale(LC_ALL, "Turkish");
    booksText();
    displayBooks();
    printf("\n");
    customerText();
    displayCustomers();
    printf("\n");
    personelText();
    displayPersonels();
    soldBooksText();
    displaySoldBooks();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
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

void printCustomer(customerPtr *root) //gelen ogrencinin bilgilerini bastirir.
{
    printf("ID: %d,\tIsim: %s,\tSoyisim: %s,\tBakiye: %d\n", root->id, root->name, root->surname, root->budget);
}

void printBook(booksPtr *root) //gelen kitabin bilgilerini bastirir.
{
    printf("ID: %d,\tKitap adi: %s,\tYazar adi: %s,\tYayin evi: %s,\tFiyat: %d,\tMiktar: %d,\tSayfa sayisi: %d\n", root->id, root->name, root->author, root->publisher, root->price, root->amount, root->pageNumber);
}

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
        if(feof(booksText))
            break;
        linkBooks(id, name, author, publisher, price, amount, pageNumber);
    }
    fclose(booksText);
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
    fclose(customerText);
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
    fclose(personelText);
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

void soldBooksText() //soldBooks.txt dosyasini okuyup linkSoldBooks() fonksiyonunu cagirir.
{
    FILE *soldBooksText = fopen("soldBooks.txt", "r");
    int idPersonel, idCustomer, idSoldBook;

    if(soldBooksText == NULL) //soldBooks.txt'nin olup olmadigini kontrol eder.
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

void linkSoldBooks(int idPersonel, int idCustomer, int idSoldBook) //gelen bilgileri uygun personele ekler.
{
    personelPtr *iterPersonel = personelNode;
    customerPtr *iterCustomer = customerNode;

    while(iterPersonel->next != NULL && iterPersonel->id != idPersonel)
        iterPersonel = iterPersonel->next;

    if(iterPersonel->id != idPersonel) //personelin olup olmadigini kontrol eder.
    {
        printf("Personelin ID'si herhangi bir personelle eslesmedi.\n");
        return;
    }

    while(iterCustomer->next != NULL && iterCustomer->id != idCustomer)
        iterCustomer = iterCustomer->next;

    if(iterCustomer->id != idCustomer) //musterinin olup olmadigini kontrol eder.
    {
        printf("Musterinin ID'si herhangi bir musteriyle eslesmedi.\n");
        return;
    }

    if(iterCustomer->id == idCustomer && iterPersonel->id == idPersonel)
    {
        soldBooksPtr *iter = iterPersonel->soldBooksList;

        if(iterPersonel->soldBooksList == NULL) //gecerli personelin daha once kitap satip satmadigini kontrol eder.
        {
            iterPersonel->soldBooksList = (soldBooksPtr *) malloc(sizeof(soldBooksPtr));
            iterPersonel->soldBooksList->idCustomer = idCustomer;
            iterPersonel->soldBooksList->idSoldBook = idSoldBook;
            iterPersonel->soldBooksList->next = NULL;
            return;
        }

        while(iter->next != NULL) //gecerli personelin sattigi kitaplarin bulundugu listenin sonuna gider.
            iter = iter->next;
        
        iter->next = (soldBooksPtr *) malloc(sizeof(soldBooksPtr));
        iter = iter->next;
        iter->idCustomer = idCustomer;
        iter->idSoldBook = idSoldBook;
        iter->next = NULL;
        return;
    }
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
        printBook(iter);
        iter = iter->next;
    }
}

void displayCustomers() //musterileri listeler.
{
    if(customerNode == NULL) //musteri node'unun bos olup olmadigini kontrol eder.
    {
        printf("Listelenecek herhangi bir kullanici bulunamadi.\n");
        return;
    }

    customerPtr *iter = customerNode;

    while(iter != NULL) //musteri node'unun sonuna kadar giderek musterilerin bilgilerini bastirir.
    {
        printCustomer(iter);
        iter = iter->next;
    }
}

void displaySoldBooks() //personellerin hangi kitabi kime sattigini listeler.
{
    personelPtr *iterPersonel = personelNode;
    customerPtr *iterCustomer = customerNode;
    booksPtr *iterBooks = booksNode;
    
    while(iterPersonel != NULL) //personellerin bulundugu linked list'in sonuna kadar gider.
    {
        soldBooksPtr *iterSoldBooks = iterPersonel->soldBooksList;

        if(iterSoldBooks != NULL) //personelin kitap satip satmadigini kontrol eder.
        {
            printf("ID'si %d olan personel %s %s tarafindan satilan kitaplar:\n", iterPersonel->id, iterPersonel->name, iterPersonel->surname);
            while(iterSoldBooks != NULL) //personelin sattigi kitaplarin linked list'inde sona kadar gider.
            {
                while(iterCustomer->id != iterSoldBooks->idCustomer)
                    iterCustomer = iterCustomer->next;
                
                while(iterBooks->id != iterSoldBooks->idSoldBook)
                    iterBooks = iterBooks->next;
                
                printf("-> Kitap adi: %s, %s isimli musteriye satildi.\n", iterBooks->name, iterCustomer->name);

                iterSoldBooks = iterSoldBooks->next;
                iterCustomer = customerNode;
                iterBooks = booksNode;
            }
            printf("\n");
        }
        iterPersonel = iterPersonel->next;
    }
}

int isPersonelValid(int idCurrentPersonel) //personelin id'sini kontrol ederek olup olmadigina dair deger dondurur.
{
    personelPtr *iter = personelNode;

    while(iter->id != idCurrentPersonel)
    {
        iter = iter->next;

        if(iter == NULL) //personel bulunmadigindan '0' dondurur.
            return 0;
    }

    return 1; //personelin bulundugunu belirtir ve '1' dondurur.
}

customerPtr *isCustomerValid(int idCurrentCustomer) //musterinin id'sini kontrol ederek olup olmadigina dair deger dondurur.
{
    customerPtr *iter = customerNode;

    while(iter->id != idCurrentCustomer)
    {
        iter = iter->next;
        
        if(iter == NULL) //musteri bulunmadigindan '0' dondurur.
            return NULL;
    }

    return iter; //musterinin bulundugunu belirtir ve '1' dondurur.
}

booksPtr *isBookValid(int idCurrentBook) //kitabin id'sini kontrol ederek olup olmadigina dair deger dondurur.
{
    booksPtr *iter = booksNode;

    while(iter->id != idCurrentBook)
    {
        iter = iter->next;

        if(iter == NULL) //kitap bulunmadigindan '0' dondurur.
            return NULL;
    }

    return iter; //kitabin bulundugunu belirtir ve '1' dondurur.
}
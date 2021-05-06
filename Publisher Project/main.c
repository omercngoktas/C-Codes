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

void printCustomer(customerPtr *root);
void printBook(booksPtr *root);
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
int isPersonelValid(int idCurrentPersonel);
customerPtr *isCustomerValid(int idCurrentCustomer);
booksPtr *isBookValid(int idCurrentBook);
void sellBook(int idCurrentPersonel);
void addBook();
void addCustomer();
void displayCustomersBooks();
void updateBookData();
void updateCustomerData();
void searchForBookName();
void searchForBookID();
bool isBookTakenByCustomer(customerPtr *iterCustomer, booksPtr *iterBook);
void bookAcceptReturn();


void printCustomer(customerPtr *root) //gelen ogrencinin bilgilerini bastirir.
{
    printf("ID: %d,\tİsim: %s,\tSoyisim: %s,\tBakiye: %d\n", root->id, root->name, root->surname, root->budget);
}

void printBook(booksPtr *root) //gelen kitabin bilgilerini bastirir.
{
    printf("ID: %d,\tKitap adı: %s,\tYazar adı: %s,\tYayın evi: %s,\tFiyat: %d,\tMiktar: %d,\tSayfa sayısı: %d\n", root->id, root->name, root->author, root->publisher, root->price, root->amount, root->pageNumber);
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
        printBook(iter);
        iter = iter->next;
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

    while(iter != NULL) //musteri node'unun sonuna kadar giderek musterilerin bilgilerini bastirir.
    {
        printCustomer(iter);
        iter = iter->next;
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
        printf("Personelin id'si herhangi bir personelle eslesmedi.\n");
        return;
    }

    while(iterCustomer->next != NULL && iterCustomer->id != idCustomer)
        iterCustomer = iterCustomer->next;

    if(iterCustomer->id != idCustomer) //musterinin olup olmadigini kontrol eder.
    {
        printf("Musterinin id'si herhangi bir musteriyle eslesmedi.\n");
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
            printf("ID'si %d olan personel %s %s tarafından satılan kitaplar:\n", iterPersonel->id, iterPersonel->name, iterPersonel->surname);
            while(iterSoldBooks != NULL) //personelin sattigi kitaplarin linked list'inde sona kadar gider.
            {
                while(iterCustomer->id != iterSoldBooks->idCustomer)
                    iterCustomer = iterCustomer->next;
                
                while(iterBooks->id != iterSoldBooks->idSoldBook)
                    iterBooks = iterBooks->next;
                
                printf("-> Kitap adı: %s, %s isimli müşteriye satıldı.\n", iterBooks->name, iterCustomer->name);

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

void sellBook(int idCurrentPersonel)
{
    int idCurrentCustomer, idCurrentBook, choice, paymentChoice, moneyAmount, choice2;

    displayCustomers(); //tum musteriler ekranda gosterilir.

    printf("Listelenen müşterilerden hangisine satış yapılacak? ID giriniz. Ana menü için 0'a basınız: ");
    scanf("%d", &idCurrentCustomer);
    if(idCurrentCustomer == 0)
    {
        printf("Ana menüye dönülüyor.\n\n");
        return;
    }

    customerPtr *iterCustomer = customerNode;
    while(iterCustomer->id != idCurrentCustomer)
    {
        iterCustomer = iterCustomer->next;
        
        if(iterCustomer == NULL) //musteri listede bulunmadigindan menuden cikilir.
        {
            printf("ID herhangi bir müşteri ile eşleşmedi. Tekrar deneyin.\n\n");
            sellBook(idCurrentPersonel);
        }
    }

    displayBooks();

    printf("ID'si %d olan %s %s isimli müşterinin almak istediği kitabın ID'sini giriniz: ", iterCustomer->id, iterCustomer->name, iterCustomer->surname);
    scanf("%d", &idCurrentBook);
    
    booksPtr *iterBook = booksNode;
    while(iterBook->id != idCurrentBook)
    {
        iterBook = iterBook->next;
        if(iterBook == NULL) //kitap listede bulunamadigindan menuden cikilir.
        {
            printf("Kitap listede bulunamadığı için menüden çıkılıyor.\n");
            return;
        }
    }

    printf("Yazarı %s olan %s isimli kitap %d lira ile %s %s isimli müşteriye satılacak.\n", iterBook->author, iterBook->name, iterBook->price, iterCustomer->name, iterCustomer->surname);
    printf("Onaylamak için 1, menüden çıkmak için 0'a basınız: ");
    scanf("%d", &choice);
    
    if(choice == 1) //kitabi id'si girilen musteriye satmak icin diger adimlara gecer.
    {
        printf("Müşteri ödemeyi nasıl gerçekleştirecek?\n");
        printf("Bakiyedenen ödenecekse 0, elden ödenecekse 1'e basınız: ");
        scanf("%d", &paymentChoice);

        if(paymentChoice == 0) //odemenin musterinin bakiyesinden dusulecegini belirtir.
        {
            if(iterCustomer->budget < iterBook->price) //musterinin bakiyesinin kitap icin yetersiz oldugunu gosterir.
            {
                printf("Müşterinin bakiyesi yetersiz. Ana menüye dönülüyor.\n");
                return;
            }

            iterCustomer->budget -= iterBook->price; //kitabin fiyatı musterinin bakiyesinden dusulur.
            iterBook->amount--;
            printf("Kitap başarıyla satılmıştır.\n");
            linkSoldBooks(idCurrentPersonel,iterCustomer->id, iterBook->id); //kitap personelin satisina eklenir.
        }

        if(paymentChoice == 1) //odeme elden yapilacagi icin diger adimlara gecer.
        {
            printf("Kasaya giren para miktarı: ");
            scanf("%d", &moneyAmount);

            if(moneyAmount < iterBook->amount) //musterinin verdigi miktarin yetersiz oldugunu belirtir.
            {
                printf("Kasaya giren miktar kitabın değerinden daha az.\n");
                printf("Geri kalan miktar bakiyeden düşülecekse 1'e, ana menüye dönmek için 0'a basanız: ");
                scanf("%d", &choice2);
                //musteriden alinan miktar yetersiz olsa dahi geri kalan miktarin musterinin bakiyesinden dusulebilir.

                if(choice2 == 1) //geri kalan miktar bakiyeden dusulecektir.
                {
                    moneyAmount -= iterBook->price;
                    moneyAmount *= -1;

                    if(iterCustomer->budget < moneyAmount) //bakiye geri kalan miktar icin yetersizdir.
                    {
                        printf("Bakiye yetersiz. Ana menüye dönülüyor.\n");
                        return;
                    }

                    iterCustomer->budget -= moneyAmount; //musterinin bakiyesi guncellenir.
                    iterBook->amount--;
                    printf("Kitap başarıyla satılmıştır.\n");
                    linkSoldBooks(idCurrentPersonel,iterCustomer->id, iterBook->id); //kitap personelin satisina eklenir.
                }
            }

            if(moneyAmount > iterBook->amount) //musterinin verdigi miktar yeterli oldugundan para ustu odenir ve satis tamamlanir.
            {
                printf("Kitap başarıyla satılmıştır.\n");
                iterBook->amount--;
                linkSoldBooks(idCurrentPersonel,iterCustomer->id, iterBook->id); //kitap personelin satisina eklenir.
                printf("Para üstü %d lira ödenmiştir.\n", moneyAmount-iterBook->price);
            }
        }
    }
    printf("Ana menüye dönülüyor.\n");
}

void addBook() //kitapların bulunduğu linked list'e kitap ekler.
{
    int id, price, amount, pageNumber;
    char name[SIZE], author[SIZE], publisher[SIZE];
    printf("Lütfen aşağıdaki bilgileri doldurunuz.\n");
    printf("Kitap adı (boşluksuz giriniz): ");
    scanf("%s", name);
    printf("Yazar adı (boşluksuz giriniz): ");
    scanf("%s", author);
    printf("Yayın evi (boşluksuz giriniz): ");
    scanf("%s", publisher);
    printf("Kitap fiyatı: ");
    scanf("%d", &price);
    printf("Kitap adedi: ");
    scanf("%d", &amount);
    printf("Sayfa sayısı: ");
    scanf("%d", &pageNumber);

    booksPtr *iter = booksNode;
    while(iter->next != NULL) //kitaplarin bulundugu listenin sonuna gider.
        iter = iter->next;
    
    id = iter->id + 1; //son kitabın id'sini 1 arttirarak eklenecek kitabin id'sine ekler.

    linkBooks(id, name, author, publisher, price, amount, pageNumber); //linked list'e kitabi ekleme kismi.
    printf("Kitap başarıyla eklenmiştir.\n");
}

void addCustomer() //musterilerin bulundugu linked list'e yeni bir müsteri ekler.
{
    char name[SIZE], surname[SIZE];
    int id, budget;

    printf("Müşteri adı (boşluksuz giriniz): ");
    scanf("%s", name);
    printf("Müşteri soyadı (boşluksuz giriniz): ");
    scanf("%s", surname);
    printf("Müşteri bakiyesi: ");
    scanf("%d", &budget);

    customerPtr *iter = customerNode;
    
    while(iter->next != NULL) //musterilerin bulundugu linked list'in sonuna gider.
        iter = iter->next;

    id = iter->id + 1; //son musterinin id'sini 1 arttirarak eklenecek olan musterinin id'sine ekler.

    linkCustomers(id, name, surname, budget); //musteriyi linked list'e ekler.
    printf("Müşteri başarıyla eklenmiştir.\n");
}

void displayCustomersBooks() //girilecek musterinin id'sinden aldigi tum kitaplari listeler.
{
    int id;
    bool isWritten = false;
    displayCustomers();
    printf("Hangi müşterinin aldığı kitapları listelemek istiyorsunuz? (çıkmak için 0'a basınız)\n");
    printf("ID: ");
    scanf("%d", &id);

    if(id == 0) return;

    customerPtr *iterCustomer = customerNode;

    iterCustomer = isCustomerValid(id);

    if(iterCustomer == NULL) //girilmis olan musterinin olmadigini soyler ve ana menuye doner.
    {
        printf("Girmiş olduğunuz müşteri ID'si hatalıdır.\n");
        return;
    }

    personelPtr *iterPersonel = personelNode;
    booksPtr *iterBook;

    while(iterPersonel != NULL) //her personeli tarayarak hangisinin bu musteriye satis yaptigindan kitaplar kontrol edilir.
    {
        soldBooksPtr *iterSoldBook = iterPersonel->soldBooksList;
        if(iterSoldBook != NULL)
        {
            while(iterSoldBook != NULL)
            {
                if(iterSoldBook->idCustomer == iterCustomer->id)
                {
                    if(isWritten == false) //egerki musteri kitap almissa 1 defaya mahsus calisir ve basligi yazdirir.
                    {
                        printf("%s %s tarafından alınan kitaplar:\n", iterCustomer->name, iterCustomer->surname);
                        isWritten = true;
                    }
                    iterBook = isBookValid(iterSoldBook->idSoldBook); //alinmis kitabin id'si fonksiyona gonderilerek kitabin tum bilgileri node seklinde dondurulur.
                    printf("ID: %d, Kitap adı: %s, Yazar adı: %s, Yayın evi: %s, Fiyat: %d, Sayfa sayısı: %d\n", iterBook->id, iterBook->name, iterBook->author, iterBook->publisher, iterBook->price, iterBook->pageNumber);
                }
                iterSoldBook = iterSoldBook->next;
            }
        }
        iterPersonel = iterPersonel->next;
    }

    if(isWritten == false) //daha once yazdirilip true degere dondurulmediginden musterinin herhangi bir kitap almadigi anlasilir.
    {
        printf("%s %s herhangi bir kitap almamıştır.\n", iterCustomer->name, iterCustomer->surname);
    }
}

void updateBookData() //kitap bilgilerinin guncellenecegi fonksiyon.
{
    int idBook, changeChoice, price, amount, pageNumber;
    char choice, name[SIZE], author[SIZE], publisher[SIZE];

    displayBooks();
    printf("Bilgilerini güncellemek istediğiniz kitabın bilgilerini giriniz: ");
    scanf("%d", &idBook);

    booksPtr *iterBook;

    iterBook = isBookValid(idBook);

    if(iterBook == NULL)
    {
        printf("Girmiş olduğunuz kitabın ID'sini kontrol ediniz.\n");
        return;
    }

    while(1)
    {
        printf("\nGüncellenecek kitabın bilgileri:\nID: %d, Kitap adı: %s, Yazar adı: %s, Yayın evi: %s, Fiyat: %d, Miktar: %d, Sayfa sayısı: %d\n", iterBook->id, iterBook->name, iterBook->author, iterBook->publisher, iterBook->price, iterBook->amount, iterBook->pageNumber);
        printf("a. Kitap adını güncelle\nb. Yazar adını güncelle\nc. Yayını evi güncelle\nd. Fiyatı güncelle\ne. Miktarı güncelle\nf. Sayfa sayısını güncelle\nq. Ana menüye dön\n");
        printf("Yapmak istediğiniz işlem: ");
        scanf(" %c", &choice);

        switch (choice)
        {
            case 'a': //kitap adi degistirme
                printf("Yeni kitap adı giriniz (boşluk bırakmadan): ");
                scanf("%s", name);
                printf("%s isimli kitabın yeni ismi %s olarak güncellenecek.\nOnaylıyor musunuz? (evet için 1, hayır için 0): ", iterBook->name, name);
                scanf("%d", &changeChoice);
                if(changeChoice == 0)
                    continue;

                strcpy(iterBook->name, name);
                printf("Kitap adı başarıyla '%s' olarak güncellendi.\n", iterBook->name);
                continue;
            
            case 'b': //kitap yazari degistirme
                printf("Kitabın yeni yazar adını giriniz (boşluk bırakmadan): ");
                scanf("%s", author);
                printf("Yazarı %s olan %s isimli kitabın yeni yazarı %s olarak güncellenecek.\n Onaylıyor musunuz? (evet için 1, hayır için 0): ", iterBook->author, iterBook->name, author);
                scanf("%d", &changeChoice);
                if(changeChoice == 0)
                    continue;
                
                strcpy(iterBook->author, author);
                printf("%s isimli kitabın yeni yazarı '%s' olarak güncellendi.\n", iterBook->name, iterBook->author);
                continue;
            
            case 'c': //kitabin yayin evini degistirme
                printf("Kitabın yeni yayın evini giriniz (boşluk bırakmadan): ");
                scanf("%s", publisher);
                printf("Yayın evi %s olan %s isimli kitabın yeni yayın evi %s olarak güncellenecek.\n Onaylıyor musunuz? (evet için 1, hayır için 0): ", iterBook->publisher, iterBook->name, author);
                scanf("%d", &changeChoice);
                if(changeChoice == 0)
                    continue;
                
                strcpy(iterBook->publisher, publisher);
                printf("%s isimli kitabın yeni yayın evi '%s' olarak güncellendi.\n", iterBook->name, iterBook->publisher);
                continue;
            
            case 'd': //kitabin fiyatini degistirme
                printf("Kitabın yeni fiyatını giriniz: ");
                scanf("%d", &price);
                printf("Fiyatı %d olan %s isimli kitabın yeni fiyatı %d olarak güncellenecek.\n Onaylıyor musunuz? (evet için 1, hayır için 0): ", iterBook->price, iterBook->name, price);
                scanf("%d", &changeChoice);
                if(changeChoice == 0)
                    continue;
                
                iterBook->price = price;
                printf("%s isimli kitabın yeni fiyatı '%d' olarak güncellendi.\n", iterBook->name, iterBook->price);
                continue;
            
            case 'e': //kitap adedini degistirme
                printf("Kitabın yeni adedini giriniz: ");
                scanf("%d", &amount);
                printf("Adedi %d olan %s isimli kitabın yeni adedi %d olarak güncellenecek.\n Onaylıyor musunuz? (evet için 1, hayır için 0): ", iterBook->amount, iterBook->name, amount);
                scanf("%d", &changeChoice);
                if(changeChoice == 0)
                    continue;
                
                iterBook->amount = amount;
                printf("%s isimli kitabın yeni adedi '%d' olarak güncellendi.\n", iterBook->name, iterBook->amount);
                continue;

            case 'f': //kitabin sayfa sayisini degistirme
                printf("Kitabın yeni sayfa sayısını giriniz: ");
                scanf("%d", &pageNumber);
                printf("Sayfa sayısı %d olan %s isimli kitabın yeni sayfa sayısı %d olarak güncellenecek.\n Onaylıyor musunuz? (evet için 1, hayır için 0): ", iterBook->pageNumber, iterBook->name, pageNumber);
                scanf("%d", &changeChoice);
                if(changeChoice == 0)
                    continue;
                
                iterBook->pageNumber = pageNumber;
                printf("%s isimli kitabın yeni sayfa sayısı '%d' olarak güncellendi.\n", iterBook->name, iterBook->pageNumber);
                continue;
            
            case 'q': //ana menuye donus
                continue;
            
            default:
                break;
        }
    }
}

void updateCustomerData() //musterilerin bilgilerini gunceller.
{
    int id, budget, changeChoice;
    char choice, name[SIZE], surname[SIZE];

    displayCustomers();
    printf("Bilgilerini güncellemek istediğiniz kitabın bilgilerini giriniz: ");
    scanf("%d", &id);
    customerPtr *iter;
    
    iter = isCustomerValid(id);
    if(iter == NULL) //girilen id'ye ait musteri olmadigini belirtir.
    {
        printf("Girmiş olduğunuz müşterinin ID'sini kontrol ediniz.\n");
        return;
    }

    while(1)
    {
        printf("Güncellemek istediğiniz müşterinin bilgileri:\n");
        printCustomer(iter);
        printf("a. İsim güncelle\nb. Soyisim güncelle\nc. Bakiyeyi güncelle\nq. Ana menüye dön\nYapmak istediğiniz işlemi giriniz: ");
        scanf(" %c", &choice);
        switch (choice)
        {
        case 'a': //musterinin ismini degistirir.
            printf("Yeni isim giriniz (boşluk bırakmadan): ");
            scanf("%s", name);
            printf("%s isimli kullanıcını yeni ismi %s olarak güncellenecek.\nOnaylıyor musunuz? (evet için 1, hayır için 0): ", iter->name, name);
            scanf("%d", &changeChoice);
            if(changeChoice == 0)
                continue;

            strcpy(iter->name, name);
            printf("Müşterinin ismi başarıyla '%s' olarak güncellendi.\n", iter->name);
            continue;
        
        case 'b': //musterinin soyadini degistirir.
            printf("Yeni soyisim giriniz (boşluk bırakmadan): ");
            scanf("%s", surname);
            printf("%s soyisimli müşterinin yeni soyismi %s olarak güncellenecek.\nOnaylıyor musunuz? (evet için 1, hayır için 0): ", iter->surname, surname);
            scanf("%d", &changeChoice);
            if(changeChoice == 0)
                continue;

            strcpy(iter->surname, surname);
            printf("Müşterinin soyismi başarıyla '%s' olarak güncellendi.\n", iter->surname);
            continue;
        
        case 'c': //musterinin bakiyesini degistirir.
            printf("Yeni bakiye giriniz (boşluk bırakmadan): ");
            scanf("%d", &budget);
            printf("%d bakiyesi olan %s isimli müşterinin yeni bakiyesi %d olarak güncellenecek.\nOnaylıyor musunuz? (evet için 1, hayır için 0): ", iter->budget, iter->name, budget);
            scanf("%d", &changeChoice);
            if(changeChoice == 0)
                continue;

            iter->budget = budget;
            printf("%s isimli müşterinin yeni bakiyesi başarıyla '%d' olarak güncellendi.\n", iter->name, iter->budget);
            continue;
        
        case 'q': //ana menuye donus.
            return;
        
        default:
            break;
        }
    }
}

void searchForBookName() //girilen kitap ismine gore arama yapar ve bilgileri bastirir.
{
    char bookName[SIZE];
    printf("Arama yapmak istediğiniz kitabın adını giriniz (boşluk olmadan): ");
    scanf("%s", bookName);
    booksPtr *iterBook = booksNode;

    while(strcmp(iterBook->name, bookName) != 0)
    {
        iterBook = iterBook->next;
        if(iterBook == NULL) //girilen isme ait kitap bulunmadigini belirtir.
        {
            printf("Girmiş olduğunuz '%s' isimli kitap bulunamadı.\n", bookName);
            return;
        }
    }

    printf("Kitap listede bulundu.\n");
    printBook(iterBook); //kitabin bilgilerini bastirir.
}

void searchForBookID() //girilen kitabin id'sine gore arama yapar.
{
    int idBook;
    printf("Arama yapmak istediğiniz kitabın ID'sini giriniz: ");
    scanf("%d", &idBook);
    booksPtr *iterBook = booksNode;

    while(iterBook->id != idBook)
    {
        iterBook = iterBook->next;
        if(iterBook == NULL) //girilen id'ye ait bir kitap bulunamadigini belirtir.
        {
            printf("ID'si '%d' olan kitap bulunamadı.\n", idBook);
            return;
        }
    }

    printf("Kitap listede bulundu.\n");
    printBook(iterBook); //kitabin bilgilerini bastirir.
}

bool isBookTakenByCustomer(customerPtr *iterCustomer, booksPtr *iterBook) //kitabin musteri tarafindan alinip alinmadigini kontrol eder.
{
    personelPtr *iterPersonel = personelNode;
    soldBooksPtr *iterSoldBooks;

    while(iterPersonel != NULL) //tum personellerin satisini kontrol eder.
    {
        soldBooksPtr *iterSoldBooks = iterPersonel->soldBooksList;

        if(iterSoldBooks != NULL) //personelin satislarina bakar.
        {
            while(iterSoldBooks != NULL) //tum kitap satislarini gezer.
            {
                if(iterSoldBooks->idCustomer == iterCustomer->id && iterSoldBooks->idSoldBook == iterBook->id)
                { //satilan kitap musteri id'si ile uyusuyordur, true deger dondurulur.
                    soldBooksPtr *temp = iterSoldBooks;
                    iterSoldBooks = iterSoldBooks->next;
                    free(temp);
                    return true;
                }
                if(iterSoldBooks->next->idCustomer == iterCustomer->id && iterSoldBooks->next->idSoldBook == iterBook->id)
                {
                    soldBooksPtr *temp = iterSoldBooks->next;
                    iterSoldBooks->next = iterSoldBooks->next->next;
                    free(temp);
                    return true;
                }
                iterSoldBooks = iterSoldBooks->next;
            }
        }
        iterPersonel = iterPersonel->next;
    }
    return false; //kitap musteriye satilmadigi icin false deger dondurulur.
}

void bookAcceptReturn() //kitap iadesi alir.
{
    int idCustomer, idBook;

    customerPtr *iterCustomer = customerNode;
    booksPtr *iterBook = booksNode;

    printf("Kitap iade edecek müşterinin ID'sini giriniz: ");
    scanf("%d", &idCustomer);

    iterCustomer = isCustomerValid(idCustomer); //musterinin database'de olup olmadigini kontrol eder. musteri varsa iterCustomer'a o musterinin bilgileri dondurulur.
    if(iterCustomer == NULL)
    {
        printf("Girmiş olduğunuz ID'ye ait herhangi bir müşteri bulunamadı.\n");
        return;
    }

    printf("Kitabı iade edecek müşterinin bilgileri:\n");
    printCustomer(iterCustomer); //musteri bilgileri bastirilir.

    printf("İade edilecek kitabın ID'sini giriniz:");
    scanf("%d", &idBook);

    iterBook = isBookValid(idBook); //kitabin olup olmadigini kontrol eder, yoksa NULL deger atanir, varsa bilgiler iterBook'a atanir.
    if(iterBook == NULL)
    {
        printf("Girmiş olduğunuz ID'ye ait herhangi bir kitap bulunamadı.\n");
        return;
    }
    
    if(isBookTakenByCustomer(iterCustomer, iterBook) == false)
    {
        printf("Girilen bilgiler uyuşmuyor. '%s %s' isimli müşteri '%s' isimli kitabı almamıştır.\n", iterCustomer->name, iterCustomer->surname, iterBook->name);
        return;
    }

    printf("Girmiş olduğunuz ID'ye ait kitap bilgileri:\n");
    printBook(iterBook); //kitap bilgileri bastirilir.
    printf("'%s' isimli kitap iade alınmıştır. İade ücreti olan '%d' lira müşterinin bakiyesine eklenmiştir.\n", iterBook->name, iterBook->price);
    printf("Bakiye güncellenmeden önceki durum: '%d' lira\n", iterCustomer->budget);
    iterCustomer->budget += iterBook->price; //iade ucreti musterinin bakiyesine yansitilir.
    iterBook->amount++; //kitap iade alindigindan kitabin adedi 1 arttirilir.
    printf("Bakiye güncellendikten sonraki durum: '%d' lira\n", iterCustomer->budget);
    printf("İade işlemi tamamlanmıştır.\nAna menüye dönülüyor.\n");
}

int main()
{
    int idPersonel, choice, choice2, changeChoice, adminOrPersonel;

    setlocale(LC_ALL, "Turkish");
    booksText();
    customerText();
    personelText();
    soldBooksText();

    printf("Kitap satış sistemine hoşgeldiniz.\n");
    printf("1- Yönetici olarak giriş yap\n2- Personel olarak giriş yap\n");
    printf("İşlem: ");
    scanf("%d", &adminOrPersonel);

    switch (adminOrPersonel)
    {
        case 1:
            printf("1- Müşteri ekle\n2- Müşteri bilgilerini güncelle\n3- Kitap ekle\n4- Kitap bilgilerini güncelle\n");
            printf("5- Personellerin satışlarını listele\n");
            printf("İşlem: ");
            scanf("%d", &choice2);
            switch (choice2)
            {
                case 1:
                    addCustomer();
                    break;

                case 2:
                    updateCustomerData();
                    break;

                case 3:
                    addBook();
                    break;

                case 4:
                    updateBookData();
                    break;

                case 5:
                    displaySoldBooks();
                    break;

                default:
                    break;
            }
        break;

        case 2:
            displayPersonels();
            printf("Yukarıda listelenen personellerden hangisi ile işlem yapacasınız?\n");
            printf("Personel ID: ");
            scanf("%d", &idPersonel);

            while(isPersonelValid(idPersonel) == 1)
            {
                printf("\n1- Müşterileri listele\n2- Kitapları listele\n3- Personelleri listele\n");
                printf("4- Kitap satışı yap\n");
                printf("5- Müşterinin aldığı kitapları listele\n");
                printf("6- İsme göre kitap ara\n7- ID'ye göre kitap ara\n8- Kitap iadesi al\n");
                printf("Yapmak istediğiniz işlem: ");
                scanf("%d", &choice);

                switch (choice)
                {
                    case 1:
                        displayCustomers();
                        break;

                    case 2:
                        displayBooks();
                        break;

                    case 3:
                        displayPersonels();
                        break;
                    
                    case 4:
                        sellBook(idPersonel);
                        break;
                    
                    case 5:
                        displayCustomersBooks();
                        break;
                    
                    case 6:
                        searchForBookName();
                        break;
                    
                    case 7:
                        searchForBookID();
                        break;
                    
                    case 8:
                        bookAcceptReturn();
                        break;

                    default:
                        break;
                }
            }
            break;
    }
    return 0;
}
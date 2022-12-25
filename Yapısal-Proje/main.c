#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define GUN_AY_YIL_TARIH "25.12.2022"

struct Ogrenci { char ogrID[9]; char ad[30]; char soyad[30]; int puan; struct Ogrenci *next; struct Ogrenci *prev; };
struct Yazar { int yazarID; char yazarAd[30]; char yazarSoyad[30]; struct Yazar *next; };
struct Kitap { char kitapAdi[30]; char ISBN[13]; int adet; struct Kitap *next; struct KitapOrnek *head; };
struct KitapOrnek { char EtiketNo[20]; char Durum[9]; struct KitapOrnek *next; };
struct KitapYazar { char ISBN[13]; int YazarID; };
struct Tarih { unsigned int gun:5; unsigned int ay:4; unsigned int yil:12; };
struct KitapOdunc { char EtiketNo[20]; char ogrID[9]; unsigned int islemTipi:1; struct Tarih islemTarihi; struct KitapOdunc *next; };

/* aldığı öğrenciler listesinin tamamını listeler */
void ogrencileriListele(struct Ogrenci* ogrenciler) {
    struct Ogrenci* iter = ogrenciler;
    printf("Ogrenci ID: %s\tOgrenci adi: %s\tOgrenci soyadi: %s\tPuani: %d\n", iter->ogrID, iter->ad, iter->soyad, iter->puan);
    while(iter->next != NULL) {
        iter = iter->next;
        printf("Ogrenci ID: %s\tOgrenci adi: %s\tOgrenci soyadi: %s\tPuani: %d\n", iter->ogrID, iter->ad, iter->soyad, iter->puan);
    }
}

/* aldığı yazarlar listesinin tamamını listeler */
void yazarlariListele(struct Yazar* yazarlar) {
    struct Yazar* iter = yazarlar;
    printf("Yazar ID: %d\tYazar adi: %s\tYazar soyadi: %s\n", iter->yazarID, iter->yazarAd, iter->yazarSoyad);
    while(iter->next != NULL) {
        iter = iter->next;
        printf("Yazar ID: %d\tYazar adi: %s\tYazar soyadi: %s\n", iter->yazarID, iter->yazarAd, iter->yazarSoyad);
    }
}

/* aldığı kitaplar listesinin tamamını listeler */
void kitaplariListele(struct Kitap* kitaplar) {
    struct Kitap* iter = kitaplar;
    printf("Kitap adi: %s\tISBN: %s\tKitap adedi: %d\n", iter->kitapAdi, iter->ISBN, iter->adet);
    while(iter->next != NULL) {
        iter = iter->next;
        printf("Kitap adi: %s\tISBN: %s\tKitap adedi: %d\n", iter->kitapAdi, iter->ISBN, iter->adet);
    }
}

/* aldığı parametrelerle listeye yeni bir öğrenci ekler */
struct Ogrenci* ogrenciEkle(struct Ogrenci* ogrenciler, char ogrenciID[], char ogrenciAd[], char ogrenciSoyad[], int ogrenciPuan) {
    struct Ogrenci* temp;
    struct Ogrenci* yeniOgrenci;
    yeniOgrenci = (struct Ogrenci*) malloc(sizeof(struct Ogrenci));
    if(yeniOgrenci == NULL) { perror("OVERFLOW\n"); exit(1); }

    strcpy(yeniOgrenci->ogrID, ogrenciID);
    strcpy(yeniOgrenci->ad, ogrenciAd);
    strcpy(yeniOgrenci->soyad, ogrenciSoyad);
    yeniOgrenci->puan = ogrenciPuan;
    if(ogrenciler == NULL) {
        yeniOgrenci->next = NULL;
        yeniOgrenci->prev = NULL;
        ogrenciler = yeniOgrenci;
        return ogrenciler;
    }
    temp = ogrenciler;
    while(temp->next != NULL) { temp = temp->next; }
    temp->next = yeniOgrenci;
    yeniOgrenci->prev = temp;
    yeniOgrenci->next = NULL;
    return ogrenciler;
}

/* aldığı parametrelerle listeye yeni bir yazar ekler */
struct Yazar* yazarEkle(struct Yazar* yazarlar, int yazarID, char yazarAd[], char yazarSoyad[]) {
    struct Yazar *yeniYazar, *temp;
    yeniYazar = (struct Yazar*) malloc(sizeof(struct Yazar));
    yeniYazar->yazarID = yazarID;
    strcpy(yeniYazar->yazarAd, yazarAd);
    strcpy(yeniYazar->yazarSoyad, yazarSoyad);
    if(yazarlar == NULL) {
        yeniYazar->next = NULL;
        return yeniYazar;
    }
    temp = yazarlar;
    while(temp->next != NULL && temp->next->yazarID < yazarID) { temp = temp->next; }
    yeniYazar->next = temp->next;
    temp->next = yeniYazar;
    return yazarlar;
}

/* aldığı parametrelerle listeye yeni bir kitap örneği ekler ekler */
struct KitapOrnek* kitapOrnegiEkle(char ISBN[], int adet) {
    struct KitapOrnek* yeniKitapOrnekleri = (struct KitapOrnek*) malloc(sizeof(struct KitapOrnek));
    struct KitapOrnek* iter = yeniKitapOrnekleri;
    int i = 1;
    char tempISBN[20];
    strcpy(tempISBN, ISBN);
    int yeniEtiket = i;
    char yeniEtiketChar[20];
    sprintf(yeniEtiketChar, "%d", yeniEtiket);
    strcat(tempISBN, "_");
    strcat(tempISBN, yeniEtiketChar);
    strcpy(iter->EtiketNo, tempISBN);
    strcpy(iter->Durum, "RAFTA");
    iter->next = NULL;

    for(i = 2; i < adet+1; i++) {
        char tempISBN[20];
        strcpy(tempISBN, ISBN);
        struct KitapOrnek* yeniKitapOrnegi = (struct KitapOrnek*) malloc(sizeof(struct KitapOrnek));
        yeniKitapOrnegi->next = NULL;
        int yeniEtiket = i;
        char yeniEtiketChar[20];
        sprintf(yeniEtiketChar, "%d", yeniEtiket);
        strcat(tempISBN, "_");
        strcat(tempISBN, yeniEtiketChar);
        strcpy(yeniKitapOrnegi->EtiketNo, tempISBN);
        strcpy(yeniKitapOrnegi->Durum, "RAFTA");
        iter->next = yeniKitapOrnegi;
        iter = iter->next;
    }
    return yeniKitapOrnekleri;
}

/* aldığı parametrelerle listeye yeni bir kitap ekler */
struct Kitap* kitapEkle(struct Kitap* kitaplar, char kitapAdi[], char ISBN[], int kitapAdedi) {
    struct Kitap *yeniKitap, *temp;
    yeniKitap = (struct Kitap*) malloc(sizeof(struct Kitap));
    strcpy(yeniKitap->kitapAdi, kitapAdi);
    strcpy(yeniKitap->ISBN, ISBN);
    yeniKitap->adet = kitapAdedi;
    if(kitaplar == NULL) {
        yeniKitap->next = NULL;
        yeniKitap->head = kitapOrnegiEkle(ISBN, kitapAdedi);
        return yeniKitap;
    }
    temp = kitaplar;
    while(temp->next != NULL) { temp = temp->next; }
    yeniKitap->next = NULL;
    yeniKitap->head = kitapOrnegiEkle(ISBN, kitapAdedi);;
    temp->next = yeniKitap;
    return kitaplar;
}

/* aldığı parametrelerle kitapYazarlar listesine yeni bir obje ekler */
struct KitapYazar kitapYazarEkle(char ISBN[], int yazarId) {
    struct KitapYazar yeniKitapYazar;
    strcpy(yeniKitapYazar.ISBN, ISBN);
    yeniKitapYazar.YazarID = yazarId;
    return yeniKitapYazar;
}

/* aldığı tarih bilgileriyle yeni bir tarih return eder */
struct Tarih tarihEkle(unsigned int gun, unsigned int ay, unsigned int yil) {
    struct Tarih yeniTarih;
    yeniTarih.gun = gun;
    yeniTarih.ay = ay;
    yeniTarih.yil = yil;
    return yeniTarih;
}

/* aldığı tarih char arrayini ayrıştırarak tarihEkle fonksiyonuna gönderir ve yeniTarih'i return eder */
struct Tarih tarihOlustur(char tarih[]) {
    unsigned int gun, ay, yil;
    char* sp;

    sp = strtok(tarih, ".");
    gun = atoi(sp);
    sp = strtok(NULL, ".");
    ay = atoi(sp);
    sp = strtok(NULL, ".");
    yil = atoi(sp);
    yil = yil%2000;
    
    struct Tarih yeniTarih = tarihEkle(gun, ay, yil);
    return yeniTarih;
}

/* aldığı parametrelerle birlikte listeye ödünç alınmış kitabın bilgilerini ekler */
struct KitapOdunc* kitapOduncEkle(struct KitapOdunc* kitapOduncler, char EtiketNo[], char ogrID[], int islemTipi, char tarih[]) {
    struct KitapOdunc* temp = kitapOduncler;
    struct KitapOdunc* yeniKitapOdunc = (struct KitapOdunc*) malloc(sizeof(struct KitapOdunc));
    strcpy(yeniKitapOdunc->EtiketNo, EtiketNo);
    strcpy(yeniKitapOdunc->ogrID, ogrID);
    yeniKitapOdunc->islemTipi = islemTipi;
    
    char geciciTarih[30];
    strcpy(geciciTarih, tarih);
    geciciTarih[10] = '\0';

    yeniKitapOdunc->islemTarihi = tarihOlustur(geciciTarih);
    if(kitapOduncler == NULL) {
        yeniKitapOdunc->next = NULL;
        return yeniKitapOdunc;
    }
    while(temp->next != NULL) { temp = temp->next; }
    yeniKitapOdunc->next = NULL;
    temp->next = yeniKitapOdunc;
    return kitapOduncler;
}

/* .csv dosyasından öğrenci bilgilerini çekerek linked list return eder */
struct Ogrenci* dosyadanOgrenciEkle(struct Ogrenci* ogrenciler) {
    FILE* fp = fopen("Ogrenciler.csv", "r");
    if(!fp) { perror("Ogrenciler.csv dosyasi bulunamadi"); exit(0); }
    char ogrenciID[9];
    char ogrenciAd[30];
    char ogrenciSoyad[30];
    int ogrenciPuan;
    char line[100];
    char* sp;
    
    while(fgets(line, 100, fp) != NULL) {
        sp = strtok(line, ",");
        strcpy(ogrenciID, sp);
        sp = strtok(NULL, ",");
        strcpy(ogrenciAd, sp);
        sp = strtok(NULL, ",");
        strcpy(ogrenciSoyad, sp);
        sp = strtok(NULL, ",");
        ogrenciPuan = atoi(sp);
        ogrenciler = ogrenciEkle(ogrenciler, ogrenciID, ogrenciAd, ogrenciSoyad, ogrenciPuan);
    }
    return ogrenciler;
}

/* .csv dosyasından yazar bilgilerini çekerek linked list return eder */
struct Yazar* dosyadanYazarEkle(struct Yazar* yazarlar) {
    FILE* fp = fopen("Yazarlar.csv", "r");
    if(!fp) { perror("Yazarlar.csv dosyasi bulunamadi"); exit(0); }
    int yazarID;
    char yazarAd[30];
    char yazarSoyad[30];
    char line[100];
    char* sp;

    while(fgets(line, 100, fp) != NULL) {
        sp = strtok(line, ",");
        yazarID = atoi(sp);
        sp = strtok(NULL, ",");
        strcpy(yazarAd, sp);
        sp = strtok(NULL, ",");
        strcpy(yazarSoyad, sp);
        int i;
        for(i = 0; i < 30; i++) if(yazarSoyad[i] == '\n') yazarSoyad[i] = '\0';
        yazarlar = yazarEkle(yazarlar, yazarID, yazarAd, yazarSoyad);
    }
    return yazarlar;
}

/* .csv dosyasından kitap bilgilerini çekerek linked list return eder */
struct Kitap* dosyadanKitapEkle(struct Kitap* kitaplar) {
    FILE* fp = fopen("Kitaplar.csv", "r");
    if(!fp) { perror("Kitaplar.csv dosyasi bulunamadi"); exit(0); }
    char ISBN[14];
    char kitapAdi[30];
    int kitapAdedi;
    char line[100];
    char* sp;

    while(fgets(line, 100, fp) != NULL) {
        sp = strtok(line, ",");
        strcpy(kitapAdi, sp);
        sp = strtok(NULL, ",");
        strcpy(ISBN, sp);
        sp = strtok(NULL, ",");
        kitapAdedi = atoi(sp);
        kitaplar = kitapEkle(kitaplar, kitapAdi, ISBN, kitapAdedi);
    }
    return kitaplar;
}

/* .csv dosyasından kitapYazar bilgilerini çekerek linked list return eder */
struct KitapYazar dosyadanKitapYazarEkle(int index) {
    FILE* fp = fopen("KitapYazar.csv", "r");
    if(!fp) { perror("KitapYazar.csv dosyasi bulunamadi"); exit(0); }
    int yazarID;
    char ISBN[14];
    char line[100];
    char* sp;
    int counter = 0;
    while(fgets(line, 100, fp) != NULL) {
        sp = strtok(line, ",");
        strcpy(ISBN, sp);
        sp = strtok(NULL, ",");
        yazarID = atoi(sp);
        if(counter == index) return kitapYazarEkle(ISBN, yazarID);
        counter++;
    }
}

/* .csv dosyasından kitapOdunc bilgilerini çekerek linked list return eder */
struct KitapOdunc* dosyadanKitapOduncEkle(struct KitapOdunc* kitapOduncler) {
    FILE* fp = fopen("KitapOdunc.csv", "r");
    if(!fp) { perror("KitapOduncs.csv dosyasi bulunamadi"); exit(0); }
    char ogrenciID[9];
    char etiketNo[30];
    char tarih[30];
    unsigned int islemTipi;
    char line[100];
    char* sp;
    
    while(fgets(line, 100, fp) != NULL) {
        sp = strtok(line, ",");
        strcpy(etiketNo, sp);
        sp = strtok(NULL, ",");
        strcpy(ogrenciID, sp);
        sp = strtok(NULL, ",");
        islemTipi = atoi(sp);
        sp = strtok(NULL, ",");
        strcpy(tarih, sp);
        tarih[10] = '\0';
        kitapOduncler = kitapOduncEkle(kitapOduncler, etiketNo, ogrenciID, islemTipi, tarih);
    }
    return kitapOduncler;
}

/* bu fonksiyonla beraber KitapYazar.csv dosyasında yer alan satır sayısını döndürüyoruz */
int getNumberOfLineFromCSV() {
    FILE* myfile = fopen("KitapYazar.csv", "r");
    int ch, counter = 0;
    do {
        ch = fgetc(myfile);
        if(ch == '\n')
            counter++;
    } while (ch != EOF);
    if(ch != '\n' && counter != 0) { counter++; }
    fclose(myfile);
    return counter;
}

/* kullanıcıya eklemek istediği kitap bilgileri sorularak kitap eklenir */
struct Kitap* yeniKitapEkle(struct Kitap* kitaplar) {
    char yeniKitapISBN[14];
    char yeniKitapAdi[30];
    int yeniKitapAdedi;
    printf("Eklemek istediginiz kitabin adini giriniz (30 karakterden fazla girmeyiniz): ");
    scanf (" %[^\n]%*c", yeniKitapAdi);
    printf("Kitabin ISBN numarasini giriniz (13 karakterden fazla girmeyiniz): ");
    scanf ("%[^\n]%*c", yeniKitapISBN);
    struct Kitap* tempKitaplar = kitaplar;
    while(tempKitaplar != NULL) {
        if(strcmp(tempKitaplar->ISBN, yeniKitapISBN) == 0) {
            printf("Eklemek istediginiz kitabin ISBN numarasi baska bir kitaba ait. Lutfen baska kitaba ait olmayan bir ISBN numarasi giriniz.\n");
            return kitaplar;
        }
        tempKitaplar = tempKitaplar->next;
    }
    printf("Kitabin adedini giriniz: ");
    scanf("%d", &yeniKitapAdedi);
    yeniKitapISBN[13] = '\0';
    kitaplar = kitapEkle(kitaplar, yeniKitapAdi, yeniKitapISBN, yeniKitapAdedi);
    return kitaplar;
}

/* kullanıcıya eklemek istediği yazar bilgileri sorularak yazar eklenir */
struct Yazar* yeniYazarEkle(struct Yazar* yazarlar) {
    int yazarID;
    char yeniYazarAdi[30];
    char yeniYazarSoyadi[30];

    printf("Eklemek istediginiz yazarin adini giriniz (30 karakterden fazla girmeyiniz): ");
    scanf (" %[^\n]%*c", yeniYazarAdi);
    printf("Yazarin soyadini giriniz (30 karakterden fazla girmeyiniz): ");
    scanf ("%[^\n]%*c", yeniYazarSoyadi);
    struct Yazar* iter = yazarlar;
    while(iter->next != NULL) iter = iter->next;
    int sonYazarID = iter->yazarID;
    yazarlar = yazarEkle(yazarlar, sonYazarID+1, yeniYazarAdi, yeniYazarSoyadi);
    return yazarlar;
}

/* kullanıcıya eklemek istediği öğrenci bilgileri sorularak öğrenci eklenir */
struct Ogrenci* yeniOgrenciEkle(struct Ogrenci* ogrenciler) {
    char yeniOgrenciNo[9];
    char yeniOgrenciAdi[30];
    char yeniOgrenciSoyadi[30];
    printf("Eklemek istediginiz ogrencinin numarasini giriniz (8 karakterden fazla girmeyiniz): ");
    scanf (" %[^\n]%*c", yeniOgrenciNo);
    struct Ogrenci* tempOgrenciler = ogrenciler;
    while(tempOgrenciler != NULL) {
        if(strcmp(tempOgrenciler->ogrID, yeniOgrenciNo) == 0) {
            printf("Ogrenci numarasi baska bir ogrenciyle eslesmistir. Lutfen baskasina ait olmayan bir ogrenci numarasi giriniz.\n");
            return ogrenciler;
        }
        tempOgrenciler = tempOgrenciler->next;
    }
    printf("Ogrencinin adini giriniz (30 karakterden fazla girmeyiniz): ");
    scanf ("%[^\n]%*c", yeniOgrenciAdi);
    printf("Ogrencinin soyadini giriniz (30 karakterden fazla girmeyiniz): ");
    scanf ("%[^\n]%*c", yeniOgrenciSoyadi);
    ogrenciler = ogrenciEkle(ogrenciler, yeniOgrenciNo, yeniOgrenciAdi, yeniOgrenciSoyadi, 100);
    return ogrenciler;
}

/* kullanıcıdan silmek istediği öğrencinin bilgileri sorularak listeden silinir */
struct Ogrenci* ogrenciSil(struct Ogrenci* ogrenciler) {
    ogrencileriListele(ogrenciler);
    char silinecekOgrenciID[9];
    printf("Silmek istediginiz ogrencinin ID'sini giriniz: ");
    scanf (" %[^\n]%*c", silinecekOgrenciID);
    struct Ogrenci* iter = ogrenciler;
    struct Ogrenci* silinecekOgrenci;
    if(strcmp(iter->ogrID, silinecekOgrenciID) == 0) {
        printf("'%s %s' isimli ogrenci silinmistir.\n", iter->ad, iter->soyad);
        silinecekOgrenci = iter;
        iter = iter->next;
        free(silinecekOgrenci);
        return iter;
    }
    while(iter->next->next != NULL && strcmp(iter->next->ogrID, silinecekOgrenciID) != 0) { iter = iter->next; }
    if(strcmp(iter->next->ogrID, silinecekOgrenciID) != 0) { 
        printf("Silmek istediginiz ogrenci bulunamadi. Lutfen kontrol edin.\n");
        return ogrenciler;
    }
    silinecekOgrenci = iter->next;
    printf("'%s %s' isimli ogrenci silinmistir.\n", silinecekOgrenci->ad, silinecekOgrenci->soyad);
    iter->next = iter->next->next;
    free(silinecekOgrenci);
    return ogrenciler;    
}

/* kullanıcıdan silmek istediği kitabın bilgileri sorularak listeden silinir */
struct Kitap* kitapSil(struct Kitap* kitaplar) {
    kitaplariListele(kitaplar);
    char silinecekKitapISBN[14];
    printf("Silmek istediginiz kitabin ISBN numarasini giriniz: ");
    scanf (" %[^\n]%*c", silinecekKitapISBN);
    struct Kitap* iter = kitaplar;
    struct Kitap* silinecekKitap;
    if(strcmp(iter->ISBN, silinecekKitapISBN) == 0) {
        printf("'%s' listeden silinmistir.\n", iter->kitapAdi);
        silinecekKitap = iter;
        iter = iter->next;
        free(silinecekKitap);
        return iter;
    }
    while(iter->next->next != NULL && strcmp(iter->next->ISBN, silinecekKitapISBN) != 0) { iter = iter->next; }
    if(strcmp(iter->next->ISBN, silinecekKitapISBN) != 0) { 
        printf("Silmek istediginiz kitap bulunamadi. Lutfen kontrol edin.\n");
        return kitaplar;
    }  
    silinecekKitap = iter->next;
    printf("'%s' listeden silinmistir.\n", silinecekKitap->kitapAdi);
    iter->next = iter->next->next;
    free(silinecekKitap);
    return kitaplar;    
}

/* kullanıcıdan silmek istediği yazarın bilgileri sorularak listeden silinir */
struct Yazar* yazarSil(struct Yazar* yazarlar) {
    yazarlariListele(yazarlar);
    int silinecekYazarID;
    printf("Silmek istediginiz yazarin ID'sini giriniz: ");
    scanf ("%d", &silinecekYazarID);
    struct Yazar* iter = yazarlar;
    struct Yazar* silinecekYazar;
    if(iter->yazarID == silinecekYazarID) {
        printf("'%s %s' isimli yazar silinmistir\n", iter->yazarAd, iter->yazarSoyad);
        silinecekYazar = iter;
        iter = iter->next;
        free(silinecekYazar);
        return iter;
    }
    while(iter->next->next != NULL && iter->next->yazarID != silinecekYazarID) { iter = iter->next; }
    if(iter->next->yazarID != silinecekYazarID) { 
        printf("Silmek istediginiz yazar bulunamadi. Lutfen kontrol edin.\n");
        return yazarlar;
    }
    silinecekYazar = iter->next;
    printf("'%s %s' isimli yazar silinmistir\n", silinecekYazar->yazarAd, silinecekYazar->yazarSoyad);
    iter->next = iter->next->next;
    free(silinecekYazar);
    return yazarlar; 
}

/* aldığı tarih objesinin bilgilerini ekrana bastırır*/
void tarihBilgisiGoruntule(struct Tarih tarihBilgisi) {
    printf("%d-%d-%d\n", tarihBilgisi.gun, tarihBilgisi.ay, tarihBilgisi.yil);
}

/* aldığı öğrenci bilgisini ekrana bastırır ve ödünç aldığı kitap varsa yine bunları da ekrana bastırır */
void ogrenciBilgileriniGoruntule(struct Ogrenci* ogrenci, struct KitapOdunc* kitapOduncler) {
    printf("ID: %s\tAd: %s\tSoyad: %s\tPuan: %d\n", ogrenci->ogrID, ogrenci->ad, ogrenci->soyad, ogrenci->puan);
    struct KitapOdunc* tempKitapOdunc = kitapOduncler;
    while(tempKitapOdunc != NULL) {
        if(strcmp(tempKitapOdunc->ogrID, ogrenci->ogrID) == 0) {
            printf("Alinan kitabin etiket numarasi: %s\tYapilan islem tipi: %d\tIslem tarihi: ", tempKitapOdunc->EtiketNo, tempKitapOdunc->islemTipi);
            tarihBilgisiGoruntule(tempKitapOdunc->islemTarihi);
        }
        tempKitapOdunc = tempKitapOdunc->next;
    }
}

/*
    kullanıcıya id veya ad-soyad tarama seçenekleri sorulur ve alınan bilgiler doğruysa öğrenci
    ekrana ödünç aldığı da kitaplar varsa bunlarla birlikte bastırılır
*/
void ogrenciBilgisiGoruntule(struct Ogrenci* ogrenciler, struct KitapOdunc* kitapOduncler) {
    int choice;
    char aranacakOgrenciID[9];
    char aranacakOgrenciAd[30];
    char aranacakOgrenciSoyad[30];
    struct Ogrenci* aranacakOgrenci = ogrenciler;
    printf("1- ID bilgisi ile goruntule\n2- Ad-Soyad bilgileri ile goruntule\nSeciminiz: ");
    scanf (" %d", &choice);
    switch (choice)
    {
        case 1:
            printf("Bilgileri goruntulenecek ogrencinin ID bilgisini giriniz: ");
            scanf (" %[^\n]%*c", aranacakOgrenciID);
            if(strcmp(aranacakOgrenci->ogrID, aranacakOgrenciID) == 0) {
                ogrenciBilgileriniGoruntule(aranacakOgrenci, kitapOduncler);
                return;
            }
            while(aranacakOgrenci->next != NULL && strcmp(aranacakOgrenci->ogrID, aranacakOgrenciID) != 0) { aranacakOgrenci = aranacakOgrenci->next; }
            if(strcmp(aranacakOgrenci->ogrID, aranacakOgrenciID) != 0) {
                printf("Girmis oldugunuz ID ile ogrenci bulunamamistir. Lutfen kontrol edin.\n");
                return;
            }
            ogrenciBilgileriniGoruntule(aranacakOgrenci, kitapOduncler);
            return;
        case 2:
            printf("Bilgileri goruntulenecek ogrencinin adini giriniz: ");
            scanf (" %[^\n]%*c", aranacakOgrenciAd);
            printf("Ogrencinin soyadini giriniz: ");
            scanf (" %[^\n]%*c", aranacakOgrenciSoyad);
            if(strcmp(aranacakOgrenci->ad, aranacakOgrenciAd) == 0 && strcmp(aranacakOgrenci->soyad, aranacakOgrenciSoyad) == 0) {
                ogrenciBilgileriniGoruntule(aranacakOgrenci, kitapOduncler);
                return;
            }
            while(aranacakOgrenci->next != NULL && strcmp(aranacakOgrenci->ad, aranacakOgrenciAd) != 0 && strcmp(aranacakOgrenci->soyad, aranacakOgrenciSoyad) != 0) { aranacakOgrenci = aranacakOgrenci->next; }
            if(strcmp(aranacakOgrenci->ad, aranacakOgrenciAd) != 0 && strcmp(aranacakOgrenci->soyad, aranacakOgrenciSoyad) != 0) {
                printf("Girmis oldugunuz isim ve soyisim ile ogrenci bulunamamistir. Lutfen kontrol edin.\n");
                return;
            }
            ogrenciBilgileriniGoruntule(aranacakOgrenci, kitapOduncler);
            return;
        default:
            printf("Yanlis islem girdiniz. Lutfen kontrol edin.\n");
            return;
    }
}

/* rafta kalan kitaplari listeler */
void raftakiKitaplariListele(struct Kitap* kitaplar) {
    while(kitaplar != NULL) {
        while(kitaplar->head != NULL) {
            if(strcmp(kitaplar->head->Durum, "RAFTA") == 0) {
                printf("Etiket No: %s\tDurum: %s\n", kitaplar->head->EtiketNo, kitaplar->head->Durum);
            }
            kitaplar->head = kitaplar->head->next;
        }
        kitaplar = kitaplar->next;
    }
}

struct Kitap* kitapBilgileriGuncelle(struct Kitap* kitaplar, struct KitapYazar *kitapYazarlar, int numberOfLines) {
    struct Kitap* temp = kitaplar;
    char guncellenecekISBN[14];
    char yeniKitapAdi[31];
    char yeniKitapISBN[14];

    int secim;
    printf("Guncelleme yapmak istediginiz kitabin ISBN numarasini giriniz (en fazla 13 hane): ");
    scanf (" %[^\n]%*c", guncellenecekISBN);
    while(temp != NULL) {
        if(strcmp(temp->ISBN, guncellenecekISBN) == 0) {
            printf("Guncellenecek kitabin bilgileri -> ISBN: %s\tKitap Adi: %s\n", temp->ISBN, temp->kitapAdi);
            printf("1- Kitap Adi Guncelle\n2- Menuden Cik\nSecim: ");
            scanf("%d", &secim);
            switch (secim)
            {
                case 1:
                    printf("Yeni kitap adi giriniz: ");
                    scanf(" %[^\n]%*c", yeniKitapAdi);
                    strcpy(temp->kitapAdi, yeniKitapAdi);
                    return kitaplar;

                case 2:
                    printf("Menuden cikiliyor.\n");
                    return kitaplar;

                default:
                    printf("Girmis oldugunuz islemi kontrol ediniz.\n");
                    return kitaplar;
            }
        }
        temp = temp->next;
    }
    printf("Girmis oldugunuz ISBN numarasi ile eslesen kitap bulunamamistir.\n");
    return kitaplar;
}

/* ödünç almış olduğu kitabı teslim etmeyen öğrencilerin ID'lerini görüntüler */
void kitapTeslimEtmeyenOgrencileriListele(struct KitapOdunc* kitapOduncler) {
    struct KitapOdunc *tempKitapOdunc = kitapOduncler;
    printf("Kitap teslim etmemis ogrencilerin listesi: \n");
    while(tempKitapOdunc != NULL) {
        if(tempKitapOdunc->islemTipi == 0) {
            printf("Ogrenci ID: %s\tAlinma Tarihi: ", tempKitapOdunc->ogrID);
            tarihBilgisiGoruntule(tempKitapOdunc->islemTarihi);
        }
        tempKitapOdunc = tempKitapOdunc->next;
    }
}

struct Yazar* yazarBilgileriGuncelle(struct Yazar* yazarlar) {
    struct Yazar* temp = yazarlar;
    int guncellenecekYazarID;
    char yeniYazarAdi[31];
    char yeniYazarSoyadi[31];
    int secim;
    printf("Guncelleme yapmak istediginiz yazarin ID numarasini giriniz: ");
    scanf("%d", &guncellenecekYazarID);
    while(temp != NULL) {
        if(temp->yazarID == guncellenecekYazarID) {
            printf("Yazar adi: %s\t Soyadi: %s\n", temp->yazarAd, temp->yazarSoyad);
            printf("1- Yazarin adini soyadini guncelle\n2- Menuden Cik\nSecim: ");
            scanf("%d", &secim);
            switch (secim)
            {
            case 1:
                printf("Yazarin adini giriniz: ");
                scanf(" %[^\n]%*c", yeniYazarAdi);
                strcpy(temp->yazarAd, yeniYazarAdi);
                printf("Yazarin soyadini giriniz: ");
                scanf (" %[^\n]%*c", yeniYazarSoyadi);
                strcpy(temp->yazarSoyad, yeniYazarSoyadi);
                return yazarlar;

            case 2:
                printf("Menuden Cikiliyor.\n");
                return yazarlar;

            default:
                printf("Girmis oldugunuz islemi kontrol ediniz.\n");
                return yazarlar;
            }
        }
        temp = temp->next;
    }
    printf("Girmis oldugunuz yazar ID numarasi ile eslesen yazar bulunamamistir.\n");
    return yazarlar;
}

struct Ogrenci* ogrenciBilgileriniGuncelle(struct Ogrenci* ogrenciler) {
    struct Ogrenci* temp = ogrenciler;
    char guncellenecekOgrenciID[9];
    char yeniOgrenciAdi[31];
    char yeniOgrenciSoyadi[31];
    char yeniOgrenciID[9];

    int secim;
    printf("Guncelleme yapmak istediginiz ogrencinin ID numarasini giriniz (en fazla 8 karakter): ");
    scanf (" %[^\n]%*c", guncellenecekOgrenciID);
    while(temp != NULL) {
        if(strcmp(temp->ogrID, guncellenecekOgrenciID)) {
            printf("Ogrencinin adi: %s\t Soyadi: %s\n", temp->ad, temp->soyad);
            printf("1- Ogrencinin adini soyadini guncelle\n2- Menuden Cik\nSecim: ");
            scanf("%d", &secim);
            switch (secim)
            {
            case 1:
                printf("Ogrencinin adini giriniz: ");
                scanf(" %[^\n]%*c", yeniOgrenciAdi);
                strcpy(temp->ad, yeniOgrenciAdi);
                printf("Ogrencinin soyadini giriniz: ");
                scanf (" %[^\n]%*c", yeniOgrenciSoyadi);
                strcpy(temp->soyad, yeniOgrenciSoyadi);
                return ogrenciler;

            case 2:
                printf("Iptal ediliyor.\n");
                return ogrenciler;

            default:
                printf("Girmis oldugunuz islemi kontrol ediniz.\n");
                return ogrenciler;
            }
        }
        temp = temp->next;
    }
    printf("Girmis oldugunuz Ogrenci ID numarasi ile eslesen ogrenci bulunamamistir.\n");
    return ogrenciler;
}

/* almış olduğu kitabın bilgisini ve örneklerini görüntüler */
void kitapBilgileriGoruntule(struct Kitap* kitap) {
    struct KitapOrnek *tempKitapOrnek = kitap->head;
    printf("Kitap adi: %s\tKitap ISBN: %s\t Kitap adedi: %d\n", kitap->kitapAdi, kitap->ISBN, kitap->adet);
    while(tempKitapOrnek != NULL) {
        printf("Etiket no: %s\tDurum: %s\n", tempKitapOrnek->EtiketNo, tempKitapOrnek->Durum);
        tempKitapOrnek = tempKitapOrnek->next;
    }
}

/* kullanıcıdan alacağı kitap adıyla kitabı kitapBilgileriGoruntule fonksiyonuna gönderir */
void kitapBilgileriniListele(struct Kitap* kitaplar) {
    char aranacakKitapAdi[30];
    struct Kitap* tempKitaplar = kitaplar;
    printf("Bilgilerini goruntulemek istediginiz kitabin adini giriniz: ");
    scanf(" %[^\n]%*c", aranacakKitapAdi);
    while(tempKitaplar != NULL) {
        if(strcmp(tempKitaplar->kitapAdi, aranacakKitapAdi) == 0) {
            kitapBilgileriGoruntule(tempKitaplar);
            return;
        }
        tempKitaplar = tempKitaplar->next;
    }
}

/* almış olduğu yazarın bilgilerini ve kitaplarını görüntüler */
void yazarBilgileriniGoruntule(struct Yazar* yazar, struct Kitap* kitaplar, struct KitapYazar kitapYazarlar[], int numberOfKitapYazarlar) {
    printf("%d. Yazar adi ve soyadi: %s %s\n", yazar->yazarID, yazar->yazarAd, yazar->yazarSoyad);
    int i;
    struct Kitap* tempKitaplar;
    for(int i = 0; i < numberOfKitapYazarlar - 1; i++) {
        tempKitaplar = kitaplar;
        if(kitapYazarlar[i].YazarID == yazar->yazarID) {
            while(tempKitaplar != NULL) {
                if(strcmp(tempKitaplar->ISBN, kitapYazarlar[i].ISBN) == 0) {
                    printf("Kitap adi: %s\tKitap ISBN: %s\t Kitap adedi: %d\n", tempKitaplar->kitapAdi, tempKitaplar->ISBN, tempKitaplar->adet);
                }
                tempKitaplar = tempKitaplar->next;
            }
        }
    }
}

/* kullanıcıdan yazarın adını alarak varsa yazarın bilgilerini görüntüleyecek fonksiyona yazarı gönderir */
void yazarBilgileriniListele(struct Yazar* yazarlar, struct Kitap* kitaplar, struct KitapYazar kitapYazarlar[], int numberOfKitapYazarlar) {
    char aranacakYazarAdi[30];
    struct Yazar *tempYazarlar = yazarlar;
    printf("Bilgilerini goruntulemek istediginiz yazarin adini giriniz: ");
    scanf(" %[^\n]%*c", aranacakYazarAdi);
    while(tempYazarlar != NULL) {
        if(strcmp(tempYazarlar->yazarAd, aranacakYazarAdi) == 0) {
            yazarBilgileriniGoruntule(tempYazarlar, kitaplar, kitapYazarlar, numberOfKitapYazarlar);
        }
        tempYazarlar = tempYazarlar->next;
    }
}

void degisiklikleriDosyalaraKaydet(
    struct Ogrenci *ogrenciler,
    struct Yazar *yazarlar,
    struct KitapOrnek *kitapOrnekler,
    struct Kitap *kitaplar,
    struct KitapYazar kitapYazarlar[], int numberOfLines,
    struct Tarih *tarihler,
    struct KitapOdunc *kitapOduncler) {
        FILE *filePtr;
        filePtr = fopen("Ogrenciler.csv", "w");
        while(ogrenciler != NULL) {
            fprintf(filePtr, "%s,%s,%s,%d\n", ogrenciler->ogrID, ogrenciler->ad, ogrenciler->soyad, ogrenciler->puan);
            ogrenciler = ogrenciler->next;
        }
        fclose(filePtr);
        filePtr = fopen("Yazarlar.csv", "w");
        while(yazarlar != NULL) {
            fprintf(filePtr, "%d,%s,%s\n", yazarlar->yazarID, yazarlar->yazarAd, yazarlar->yazarSoyad);
            yazarlar = yazarlar->next;
        }
        fclose(filePtr);
        filePtr = fopen("Kitaplar.csv", "w");
        while(kitaplar != NULL) {
            fprintf(filePtr, "%s,%s,%d\n", kitaplar->kitapAdi, kitaplar->ISBN, kitaplar->adet);
            kitaplar = kitaplar->next;
        }
        fclose(filePtr);
        filePtr = fopen("KitapYazar.csv", "w");
        int i;
        for(i = 0; i < numberOfLines-1; i++) {
            fprintf(filePtr, "%s,%d\n", kitapYazarlar[i].ISBN, kitapYazarlar[i].YazarID);
        }
        fclose(filePtr);
        filePtr = fopen("KitapOdunc.csv", "w");
        while(kitapOduncler != NULL) {
            fprintf(filePtr, "%s,%s,%d,%d.%d.%d.%d\n", kitapOduncler->EtiketNo, kitapOduncler->ogrID, kitapOduncler->islemTipi, kitapOduncler->islemTarihi.gun, kitapOduncler->islemTarihi.ay, 20, kitapOduncler->islemTarihi.yil);
            kitapOduncler = kitapOduncler->next;
        }
        fclose(filePtr);
}

struct KitapOdunc* kitapOduncAl(struct Ogrenci *ogrenciler, struct Kitap* kitaplar, struct KitapOdunc *kitapOduncler) {
    char oduncAlinacakKitapISBN[14];
    char ogrenciID[9];
    // char oduncAlinacakKitapISBN[] = "1234567891011";
    // char ogrenciID[] = "17011015";
    printf("Kitap hangi ogrenci tarafindan odunc alinacak? ID numarasi giriniz: ");
    scanf (" %[^\n]%*c", ogrenciID);
    struct Ogrenci* tempOgrenciler = ogrenciler;
    int ogrenciBulunduMu = 0, kitapOrnegiVarMi = 0;
    while(tempOgrenciler != NULL) {
        if(strcmp(tempOgrenciler->ogrID, ogrenciID) == 0) {
            ogrenciBulunduMu = 1;
            if(tempOgrenciler->puan < 0) {
                printf("Ogrencinin yeterli puani bulunmadigindan kitap almasi mumkun degildir.\n");
                return kitapOduncler;
            }
            break;
        }
        tempOgrenciler = tempOgrenciler->next;
    }
    printf("Odunc alinacak kitabin ISBN numarasini giriniz: ");
    scanf ("%[^\n]%*c", oduncAlinacakKitapISBN);
    struct Kitap* tempKitaplar = kitaplar;
    while(tempKitaplar != NULL) {
        if(strcmp(tempKitaplar->ISBN, oduncAlinacakKitapISBN) == 0) {
            kitapOrnegiVarMi = 1;
            struct KitapOrnek* kitapOrnekleri = tempKitaplar->head;
            while(kitapOrnekleri != NULL) {
                if(strcmp(kitapOrnekleri->Durum, "RAFTA") == 0) {
                    strcpy(kitapOrnekleri->Durum, tempOgrenciler->ogrID);
                    printf("Kitap durumu : %s\n", kitapOrnekleri->Durum);
                    char tarih[] = "25.11.2022";
                    kitapOduncler = kitapOduncEkle(kitapOduncler, kitapOrnekleri->EtiketNo, tempOgrenciler->ogrID, 0, tarih);
                    printf("Kitap basariyla odunc alinmistir.\n");
                    return kitapOduncler;
                }
                kitapOrnekleri = kitapOrnekleri->next;
            }
        }
        tempKitaplar = tempKitaplar->next;
    }
    printf("Kitap ornegi kalmamistir. Baska kitap almayi deneyin.\n");
}

int gunFarki(struct Tarih alinmaTarihi) {
    char *sp;
    unsigned int gun, ay, yil;
    char gunAyYil[11];
    strcpy(gunAyYil, GUN_AY_YIL_TARIH);
    sp = strtok(gunAyYil, ".");
    gun = atoi(sp);
    sp = strtok(NULL, ".");
    ay = atoi(sp);
    sp = strtok(NULL, ".");
    yil = atoi(sp);
    yil = yil %2000;
    /* aynı gün teslim ediliyor */
    if((yil - alinmaTarihi.yil == 0) && (ay - alinmaTarihi.ay == 0) && (gun - alinmaTarihi.gun == 0)) { return 0; }
    /* teslim edilme tarihinden bu yana 1 yıldan fazla geçmiş */
    if(yil - alinmaTarihi.yil > 0) { return 365; }
    /* teslim alma tarihinden bu güne kadar 1 aydan fazla geçmiş */
    if(ay - alinmaTarihi.ay > 1) { return 30; }
    /* aynı ay içinde geri veriliyor */
    if(ay - alinmaTarihi.ay == 0) { return gun - alinmaTarihi.gun; }
    int tarihFarki;
    tarihFarki = 30 - alinmaTarihi.gun + gun;
    return tarihFarki;
}

/* almış olduğu kitap bilgilerini kıyaslayarak etiket no ve kitap uyuşuyor mu kontrol eder */
int kitapVarMi(char etiketNo[], char ISBN[]) {
    bool isPresent = false;
    for (int i = 0; etiketNo[i] != '\0'; i++) {
        isPresent = false;
        for (int j = 0; ISBN[j] != '\0'; j++) {
            if (etiketNo[i + j] != ISBN[j]) {
                isPresent = false;
                break;
            }
            isPresent = true;
        }
        if (isPresent) {
            break;
        }
    }
    if (isPresent) {
        return 1;
    } else {
        return 0;
    }
    return 0;
}

void kitapTeslimEt(struct Ogrenci *ogrenciler, struct Kitap* kitaplar, struct KitapOdunc *kitapOduncler) {
    char ogrenciID[9];
    char kitapEtiketNo[14];
    // char kitapEtiketNo[] = "1234567891011";
    // char ogrenciID[] = "17011015";
    printf("Kitap teslim edecek ogrenicinin ID numarasini giriniz: ");
    scanf (" %[^\n]%*c", ogrenciID);
    printf("Teslim edilecek kitabin ISBN numarasini giriniz: ");
    scanf ("%[^\n]%*c", kitapEtiketNo);
    struct Ogrenci *tempOgrenciler = ogrenciler;
    struct KitapOdunc *tempKitapOduncler = kitapOduncler;
    struct Kitap *tempKitaplar = kitaplar;
    while (tempKitaplar != NULL) {
        if(strcmp(tempKitaplar->ISBN, kitapEtiketNo) == 0) { break; }
        tempKitaplar = tempKitaplar->next;
        if (tempKitaplar == NULL ) { printf("Kitap bulunamamistir.\n"); return; }
    }
    
    while(tempOgrenciler != NULL) {
        if(strcmp(tempOgrenciler->ogrID, ogrenciID) == 0) { break; }
        tempOgrenciler = tempOgrenciler->next;
        if(tempOgrenciler == NULL) { printf("Ogrenci bulunamamistir.\n"); return; }
    }
    while(tempKitapOduncler != NULL) {
        /* girilen ogrencinin ID numarasi ve kitap etiket numarasi eslesti */
        if((strcmp(tempKitapOduncler->ogrID, ogrenciID) == 0) && (kitapVarMi(tempKitapOduncler->EtiketNo, kitapEtiketNo) == 1)) {
            /* kitap teslim edilmemis */
            if(tempKitapOduncler->islemTipi == 0) {
                if(gunFarki(tempKitapOduncler->islemTarihi) > 15) {
                    printf("Kitap teslim tarihi 15 gunden fazla oldugu icin ogrenciden 10 puan dusulecektir.\n");
                    tempOgrenciler->puan -= 10;
                }
                tempKitapOduncler->islemTipi = 1; /* kitabın teslim edildiği bilgisi değiştirilmiştir */
                struct KitapOrnek* tempKitapOrnekler = tempKitaplar->head;
                while(tempKitapOrnekler != NULL) {
                    if(strcmp(tempKitapOrnekler->EtiketNo, tempKitapOduncler->EtiketNo) == 0) {
                        strcpy(tempKitapOrnekler->Durum, "RAFTA");
                        printf("Kitap basariyla teslim edilmistir.\n");
                        return;
                    }
                    tempKitapOrnekler = tempKitapOrnekler->next;
                }
                return;
            } else {
                printf("Kitap zaten daha once teslim edilmistir.");
                return;
            }
        }
        tempKitapOduncler = tempKitapOduncler->next;
    }
}

void cezaliOgrencileriListele(struct Ogrenci* ogrenciler) {
    struct Ogrenci *tempOgrenciler = ogrenciler;
    int yazildiMi = 0;
    while(tempOgrenciler != NULL) {
        if(tempOgrenciler->puan < 0) {
            if(yazildiMi == 0) {
                printf("CEZALI DURUMDAKI OGRENCILER:\n");
                yazildiMi = 1;
            }
            printf("ID: %s\tAd: %s\tSoyad: %s\n", tempOgrenciler->ogrID, tempOgrenciler->ad, tempOgrenciler->soyad);
        }
        tempOgrenciler = tempOgrenciler->next;
    }
}

void zamanindaTeslimEdilmeyenKitaplariListele(struct Kitap *kitaplar, struct KitapOdunc *kitapOduncler) {
    struct Kitap *tempKitaplar = kitaplar;
    struct KitapOrnek *tempKitapOrnekleri;
    struct KitapOdunc *tempKitapOduncler = kitapOduncler;
    while(tempKitapOduncler != NULL) {
        if(gunFarki(tempKitapOduncler->islemTarihi) > 10) {
            tempKitaplar = kitaplar;
            while(tempKitaplar != NULL) {
                if(kitapVarMi(tempKitapOduncler->EtiketNo, tempKitaplar->ISBN) == 1) {
                    printf("ISBN: %s\tKitap Adi: %s\tKitap Etiket Numarasi: %s\n", tempKitaplar->ISBN, tempKitaplar->kitapAdi, tempKitapOduncler->EtiketNo);
                }
                tempKitaplar = tempKitaplar->next;
            }
        }
        tempKitapOduncler = tempKitapOduncler->next;
    }
}

void kitapYazarEslestir(struct Kitap *kitaplar, struct Yazar *yazarlar, struct KitapYazar *kitapYazarlar, int numberOfLines) {
    struct Kitap *tempKitaplar = kitaplar;
    struct Yazar *tempYazarlar = yazarlar;
    struct KitapYazar *tempKitapYazarlar = kitapYazarlar;
    char yazarAdi[30];
    int yazarID;
    char kitapAdi[30];
    char kitapISBN[30];
    printf("Kitap-Yazar eslestirmesi yapmak istediginiz yazarin adini giriniz: ");
    scanf (" %[^\n]%*c", yazarAdi);
    while(tempYazarlar != NULL) {
        if(strcmp(tempYazarlar->yazarAd, yazarAdi) == 0) {
            printf("ID: %d\t Yazar Adi: %s\tYazar Soyadi: %s\n", tempYazarlar->yazarID, tempYazarlar->yazarAd, tempYazarlar->yazarSoyad);
        }
        tempYazarlar = tempYazarlar->next;
    }
    tempYazarlar = yazarlar;
    printf("Listelenen yazarin ID numarasini giriniz: ");
    scanf("%d", &yazarID);
    int yazarVarMi = 0;
    while(tempYazarlar != NULL) {
        if(tempYazarlar->yazarID == yazarID) yazarVarMi = 1;
        tempYazarlar = tempYazarlar->next;
    }
    if(yazarVarMi == 0) {
        printf("Yazar sistemde bulunamamistir.\n");
        return;
    }
    printf("Kitap-Yazar eslestirmesi yapilacak kitabin adini giriniz: ");
    scanf (" %[^\n]%*c", kitapAdi);
    while(tempKitaplar != NULL) {
        if(strcmp(tempKitaplar->kitapAdi, kitapAdi) == 0) {
            printf("ISBN: %s\tKitap Adi: %s\n", tempKitaplar->ISBN, tempKitaplar->kitapAdi);
        }
        tempKitaplar = tempKitaplar->next;
    }
    tempKitaplar = kitaplar;
    printf("Listelenen kitabin ISBN numarasini giriniz: ");
    scanf ("%[^\n]%*c", kitapISBN);
    FILE *filePtr;
    filePtr = fopen("KitapYazar.csv", "w");
    int i;
    for(i = 0; i < numberOfLines-1; i++) {
        fprintf(filePtr, "%s,%d\n", kitapYazarlar[i].ISBN, kitapYazarlar[i].YazarID);
    }
    fprintf(filePtr, "%s,%d\n", kitapISBN, yazarID);
    fclose(filePtr);
}

void kitabinYazariniGuncelle(struct Kitap *kitaplar, struct Yazar *yazarlar, struct KitapYazar *kitapYazarlar, int numberOfLines) {
    struct Kitap *tempKitaplar = kitaplar;
    struct Yazar *tempYazarlar = yazarlar;
    struct KitapYazar *tempKitapYazarlar = kitapYazarlar;
    char kitapISBN[14];
    int yazarID;
    printf("Yazarini guncellemek istediginiz kitabin ISBN numarasini giriniz: ");
    scanf (" %[^\n]%*c", kitapISBN);
    int kitapVarMi = 0;
    while(tempKitaplar != NULL) {
        if(strcmp(tempKitaplar->ISBN, kitapISBN) == 0) { kitapVarMi = 1; }
        tempKitaplar = tempKitaplar->next;
    }
    if(kitapVarMi == 0) {
        printf("Kitap sistemde bulunamamistir.\n");
        return;
    }
    int index, baslikYaz = 0;
    for(index = 0; index < numberOfLines - 1; index++) {
        if(strcmp(kitapYazarlar[index].ISBN, kitapISBN) == 0) {
            if(baslikYaz == 0) { printf("Kitabin yazarlari:\n"); baslikYaz = 1; }
            printf("Kitap ISBN: %s\tKitap Yazari: %d\n", kitapYazarlar[index].ISBN, kitapYazarlar[index].YazarID);
        }
    }
    if(baslikYaz == 0) {
        printf("Kitabin yazar bilgileri daha once sisteme girilmemis. Lutfen once kitaba yazar ekleyin.\n");
        return;
    }
    int eskiYazarId, yeniYazarID, yazarVarMi = 0;
    printf("Guncellemek istediginiz yazarin ID numarasini giriniz: ");
    scanf("%d", &eskiYazarId);
    printf("Yeni yazarin ID numarasini giriniz: ");
    scanf("%d", &yeniYazarID);
    while(tempYazarlar != NULL) {
        if(tempYazarlar->yazarID == yeniYazarID) { yazarVarMi = 1; break; }
        tempYazarlar = tempYazarlar->next;
    }
    if(yazarVarMi == 0) {
        printf("Guncellenecek yeni yazarin ID numarasi bulunamamistir.\n");
        return;
    }
    for(index = 0; index < numberOfLines; index++) {
        if(kitapYazarlar[index].YazarID == eskiYazarId) {
            kitapYazarlar[index].YazarID = yeniYazarID;
            FILE *filePtr;
            filePtr = fopen("KitapYazar.csv", "w");
            int i;
            printf("number of lines: %d\n", numberOfLines);
            for(i = 0; i < numberOfLines-1; i++) {
                fprintf(filePtr, "%s,%d\n", kitapYazarlar[i].ISBN, kitapYazarlar[i].YazarID);
            }
            fclose(filePtr);
            return;
        }
    }
    printf("Guncellenecek eski yazarin ID numarasi bulunamamistir.\n");
}

int main() {
    struct KitapOdunc *KitapOduncler = NULL;

    struct Ogrenci *Ogrenciler = NULL;
    struct Yazar *Yazarlar = NULL;
    struct KitapOrnek *KitapOrnekler = NULL;
    struct Kitap *Kitaplar = NULL;
    
    struct Tarih *Tarihler = NULL;
    
    Ogrenciler = dosyadanOgrenciEkle(Ogrenciler);
    Yazarlar = dosyadanYazarEkle(Yazarlar);
    Kitaplar = dosyadanKitapEkle(Kitaplar);
    // KitapOduncler = dosyadanKitapOduncEkle(KitapOduncler);

    int menuSecimi = 0, icMenuSecimi = 0;
    while(menuSecimi != 4) {
        int numberOfLines = getNumberOfLineFromCSV();
        struct KitapYazar KitapYazarlar[numberOfLines];
        int i;
        for(i = 0; i < numberOfLines; i++) {
            KitapYazarlar[i] = dosyadanKitapYazarEkle(i);
        }

        icMenuSecimi = 0;
        printf("\n1- Ogrenci Islemleri\n");
        printf("2- Kitap Islemleri\n");
        printf("3- Yazar Islemleri\n");
        printf("4- Cikis yap\n");
        printf("Seciminizi giriniz (1-4): ");
        scanf(" %d%*c", &menuSecimi);
        switch (menuSecimi)
        {  
            /* ogrenci islemlerinin yapilacagi menu */
            case 1:
                while(icMenuSecimi != 10) {
                    printf("\nOGRENCI ISLEMLERI:\n");
                    printf("1- Ogrenci Ekle\n");/**/
                    printf("2- Ogrenci Sil\n");/**/
                    printf("3- Ogrenci Guncelle\n");/**/
                    printf("4- Ogrenci Bilgisi Goruntuleme\n");/**/
                    printf("5- Kitap Teslim Etmemis Ogrencileri Listele\n");/**/
                    printf("6- Cezali Ogrencileri Listele\n");
                    printf("7- Tum Ogrencileri Listele\n");/**/
                    printf("8- Kitap Odunc Al\n");
                    printf("9- Kitap Teslim Et\n");
                    printf("10- Ana Menuye Don\n");/**/
                    printf("Seciminizi giriniz (1-10): ");
                    scanf(" %d", &icMenuSecimi);
                    switch (icMenuSecimi)
                    {
                        case 1:
                            Ogrenciler = yeniOgrenciEkle(Ogrenciler);
                            break;
                        case 2:
                            Ogrenciler = ogrenciSil(Ogrenciler);
                            break;
                        case 3:
                            Ogrenciler = ogrenciBilgileriniGuncelle(Ogrenciler);
                            break;
                        case 4:
                            ogrenciBilgisiGoruntule(Ogrenciler, KitapOduncler);
                            break;
                        case 5:
                            kitapTeslimEtmeyenOgrencileriListele(KitapOduncler);
                            break;
                        case 6:
                            cezaliOgrencileriListele(Ogrenciler);
                            break;
                        case 7:
                            ogrencileriListele(Ogrenciler);
                            break;
                        case 8:
                            KitapOduncler = kitapOduncAl(Ogrenciler, Kitaplar, KitapOduncler);
                            break;
                        case 9:
                            kitapTeslimEt(Ogrenciler, Kitaplar, KitapOduncler);
                            break;
                        case 10:
                            printf("Ana menuye donuluyor.\n");
                            break;
                        default:
                            printf("Hatali islem yaptiniz. Lutfen tekrar deneyin.\n");
                            break;
                    }
                    break;
                }
                break;
            
            /* kitap islemlerinin yapilacagi menu */
            case 2:
                while(icMenuSecimi != 9) {
                    printf("\nKITAP ISLEMLERI:\n");
                    printf("1- Kitap Ekle\n");/**/
                    printf("2- Kitap Sil\n");/**/
                    printf("3- Kitap Guncelle\n");/**/
                    printf("4- Kitap Bilgisi Goruntuleme\n");/**/
                    printf("5- Raftaki Kitaplari Listele\n");/**/
                    printf("6- Zamaninda Teslim Edilmeyen Kitaplari Listele\n");
                    printf("7- Kitap-Yazar Eslestir\n");
                    printf("8- Kitabin Yazarini Guncelle\n");
                    printf("9- Ana Menuye Don\n");/**/
                    printf("Seciminizi giriniz (1-9): ");
                    scanf(" %d", &icMenuSecimi);
                    switch (icMenuSecimi)
                    {
                        case 1:
                            Kitaplar = yeniKitapEkle(Kitaplar);
                            break;
                        case 2:
                            Kitaplar = kitapSil(Kitaplar);
                            break;
                        case 3:
                            Kitaplar = kitapBilgileriGuncelle(Kitaplar, KitapYazarlar, numberOfLines);
                            break;
                        case 4:
                            kitapBilgileriniListele(Kitaplar);
                            break;
                        case 5:
                            raftakiKitaplariListele(Kitaplar);
                            break;
                        case 6:
                            zamanindaTeslimEdilmeyenKitaplariListele(Kitaplar, KitapOduncler);
                            break;
                        case 7:
                            kitapYazarEslestir(Kitaplar, Yazarlar, KitapYazarlar, numberOfLines);
                            break;
                        case 8:
                            kitabinYazariniGuncelle(Kitaplar, Yazarlar, KitapYazarlar, numberOfLines);
                            break;
                        case 9:
                            printf("Ana menuye donuluyor.\n");
                            break;

                        default:
                            printf("Hatali islem yaptiniz. Lutfen tekrar deneyin.\n");
                            break;
                    }
                    break;
                }
                break;
            
            /* yazar islemlerinin yapilacagi menu */
            case 3:
                while(icMenuSecimi != 5) {
                    printf("\nYAZAR ISLEMLERI:\n");
                    printf("1- Yazar Ekle\n");/**/
                    printf("2- Yazar Sil\n");/**/
                    printf("3- Yazar Guncelle\n");/**/
                    printf("4- Yazar Bilgisi Goruntuleme\n");/**/
                    printf("5- Ana Menuye Don\n");
                    printf("Seciminizi giriniz (1-5): ");
                    scanf(" %d", &icMenuSecimi);
                    switch (icMenuSecimi)
                    {
                        case 1:
                            Yazarlar = yeniYazarEkle(Yazarlar);
                            break;
                        case 2:
                            Yazarlar = yazarSil(Yazarlar);
                            break;
                        case 3:
                            Yazarlar = yazarBilgileriGuncelle(Yazarlar);
                            break;
                        case 4:
                            yazarBilgileriniListele(Yazarlar, Kitaplar, KitapYazarlar, numberOfLines);
                            break;
                        case 5:
                            printf("Ana menuye donuluyor.\n");
                            break;

                        default:
                            printf("Hatali islem yaptiniz. Lutfen tekrar deneyin.\n");
                            break;
                    }
                    break;
                }
                break;

            /* çıkış */
            case 4:
                printf("Cikis yapiliyor.\n");
                degisiklikleriDosyalaraKaydet(Ogrenciler, Yazarlar, KitapOrnekler, Kitaplar, KitapYazarlar, numberOfLines, Tarihler, KitapOduncler);
                return 0;

            /* hatalı giriş */
            default:
                printf("Hatali islem yaptiniz. Lutfen tekrar deneyin.\n");
                break;
        }
    }

    return 0;
}
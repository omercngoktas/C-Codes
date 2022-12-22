#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Ogrenci { char ogrID[8]; char ad[30]; char soyad[30]; int puan; struct Ogrenci *next; struct Ogrenci *prev; };
struct Yazar { int yazarID; char yazarAd[30]; char yazarSoyad[30]; struct Yazar *next; };
struct KitapOrnek { char EtiketNo[20]; char Durum[8]; struct KitapOrnek *next; };
struct Kitap {char kitapAdi[30]; char ISBN[13]; int adet; struct Kitap *next; struct KitapOrnek *head; };
struct KitapYazar{ char ISBN[13]; int YazarID; };
struct Tarih{ int gun:5; int ay:4; int yil:12; };
struct KitapOdunc{ char EtiketNo[20]; char ogrID[8]; int islemTipi:1; struct Tarih islemTarihi; };

void dosyadanOgrenciEkle() {
    FILE* fp = fopen("Ogrenciler.csv", "r");
    if(!fp) { perror("Ogrenciler.csv dosyasi bulunamadi"); exit(0); }
    int ogrenciID;
    char ogrenciAd[30];
    char ogrenciSoyad[30];
    int ogrenciPuan;

    char line[100];

    char* sp;
    while(fgets(line, 100, fp) != NULL) {
        sp = strtok(line, ",");
        ogrenciID = atoi(sp);
        sp = strtok(NULL, ",");
        strcpy(ogrenciAd, sp);
        sp = strtok(NULL, ",");
        strcpy(ogrenciSoyad, sp);
        sp = strtok(NULL, ",");
        ogrenciPuan = atoi(sp);
        printf("Ogrenci ID: %d Ogrenci adi: %s Ogrenci soyadi: %s Puani: %d\n", ogrenciID, ogrenciAd, ogrenciSoyad, ogrenciPuan);
    }
}

void dosyadanYazarEkle() {
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
        printf("Yazar ID: %d Yazar adi: %s Yazar soyadi: %s\n", yazarID, yazarAd, yazarSoyad);
    }
}

void dosyadanKitapEkle() {
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
        printf("Kitap adi: %s ISBN: %s Kitap adedi: %d\n", kitapAdi, ISBN, kitapAdedi);
    }
}

void dosyadanKitapYazarEkle() {
    FILE* fp = fopen("KitapYazar.csv", "r");
    if(!fp) { perror("KitapYazar.csv dosyasi bulunamadi"); exit(0); }
    int yazarID;
    char ISBN[14];

    char line[100];

    char* sp;
    while(fgets(line, 100, fp) != NULL) {
        sp = strtok(line, ",");
        strcpy(ISBN, sp);
        sp = strtok(NULL, ",");
        yazarID = atoi(sp);
        printf("Kitap ISBN: %s Yazar ID: %d\n", ISBN, yazarID);
    }
}

int main() {
    struct Ogrenci *Ogrenciler;
    struct Yazar *Yazarlar;
    struct KitapOrnek *KitapOrnekler;
    struct Kitap *Kitaplar;
    struct KitapYazar *KitapYazarlar;
    struct Tarih *Tarihler;
    struct KitapOdunc *KitapOduncler;
    dosyadanOgrenciEkle();
    dosyadanYazarEkle();
    dosyadanKitapEkle();
    dosyadanKitapYazarEkle();
    return 0;
}
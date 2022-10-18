#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Menünün struct yapısı
struct Yemekler{
    char yemekAdi[256];
    int yemekGrami;
    double yemekFiyati;
    struct Yemekler *next;
};

typedef struct Yemekler YemekNode;

// Yemek adı, yemek fiyatı ve yemek gramı yemekEkle fonksiyonuna gönderilir.
// yemekEkle fonksiyonu gerekli kontrolleri sağlayarak yemekleri fiyatlarına göre sıralı bir şekilde root düğümüne ekler.
YemekNode *yemekEkle(YemekNode *root, char yemekAdi[], double yemekFiyati, int yemekGrami) {
    // root'ta daha önce eklenmiş bir yemek var mı diye kontrol yapılır.
    if(root == NULL) {
        root = (YemekNode *) malloc(sizeof(YemekNode));
        strcpy(root->yemekAdi, yemekAdi);
        root->yemekFiyati = yemekFiyati;
        root->yemekGrami = yemekGrami;
        root->next = root;
        return root;
    }
    YemekNode *iter = root;
    YemekNode *temp;

    // menüye menünün ilk başında bulunan yemekten daha düşük fiyatlı bir yemek eklendiğinde burası çalışır.
    if(root->yemekFiyati > yemekFiyati) {
        temp = (YemekNode *) malloc(sizeof(YemekNode));
        strcpy(temp->yemekAdi, yemekAdi);
        temp->yemekFiyati = yemekFiyati;
        temp->yemekGrami = yemekGrami;
        temp->next = root;
        while(iter->next != root) {
            iter = iter->next;
        }
        iter->next = temp;
        return temp;
    }

    // düğümün ilerisinde fiyatı daha yüksek bir yemek bulunana kadar iter nextlenir ve araya yeni yemek eklenir.
    // arada bulunması şart değil, yeni eklenecek en yüksek fiyata sahipse listenin sonuna eklenir.
    while(iter->next->yemekFiyati < yemekFiyati && iter->next != root) {
        iter = iter->next;
    }
    temp = (YemekNode *) malloc(sizeof(YemekNode));
    temp->next = iter->next;
    iter->next = temp;
    strcpy(temp->yemekAdi, yemekAdi);
    temp->yemekFiyati = yemekFiyati;
    temp->yemekGrami = yemekGrami;
    return root;
}

// yemekleriListele fonksiyonuna menü gönderilir ve burada yemekler sırasına göre bastırılır.
void yemekleriListele(YemekNode *root) {
    if(root == NULL) {
        printf("Listelenecek yemek bulunamadi.\n");
        return;
    }

    YemekNode *iter = root;
    // ilk yemek bastırılır.
    printf("%s ", root->yemekAdi);
    printf("%dgr ", root->yemekGrami);
    printf("%.1lf TL\n", root->yemekFiyati);
    // iter root'tan başlatılarak ilerletilir ve yemekler bastırılır.
    while(iter->next != root)
    {
        iter = iter->next;
        printf("%s ", iter->yemekAdi);
        printf("%dgr ", iter->yemekGrami);
        printf("%.1lf TL\n", iter->yemekFiyati);
    }
}

// FILE pointer ve yemek rootu input olarak alınır, dosya read moduyla 
// açılarak okunur ve yemekler yemekEkle fonksiyonuna gönderilerek sırasıyla menüye eklenirler.
YemekNode *txtYazdir(FILE *yemekListesi, YemekNode *root) {
    char yemekAdi[256];
    double yemekFiyati;
    int yemekGrami;

    if(yemekListesi == NULL) {
        printf("Yemek listesi bostur.\n");
        return root;
    }

    while(!feof(yemekListesi)) {
        fscanf(yemekListesi, "%s %d %lf", yemekAdi, &yemekGrami, &yemekFiyati);
        if(feof(yemekListesi)) break;
        
        root = yemekEkle(root, yemekAdi, yemekFiyati, yemekGrami);
    }
    fclose(yemekListesi);
    return root;
}

// menüde tek tek yemek basılırken burası çağrılır.
void tekYemekYazdir(YemekNode *yemek) {
    printf("%s ", yemek->yemekAdi);
    printf("%dgr ", yemek->yemekGrami);
    printf("%.1lf TL", yemek->yemekFiyati);
}

// yemek seçimi burada yapılır.
int yemekSec(YemekNode *root) {
    char yemekSecimi = 'h';
    YemekNode *iter = root;

    printf("Yemek secimi icin 'e',\n");
    printf("bir sonraki yemege gecmek icin 'h',\n");
    printf("ana menuye donmek icin 'a' degerini giriniz.\n\n");

    // menüde bulunan ilk yemek ekrana bastırılır ve kullanıcıdan seçim yapması beklenir.
    tekYemekYazdir(iter);
    printf(" : ");
    scanf(" %c", &yemekSecimi);
    if(yemekSecimi == 'e') {
        printf("\n%s Sectiniz.\n", iter->yemekAdi);
        printf("Siparisiniz en kisa zamanda teslim edilecektir.\nAfiyet Olsun!\n");
        return 0;
    } else if(yemekSecimi == 'a') {
        printf("\nAna menuye donuluyor.\n");
        return 1;
    }

    // ilk menüde 'h' girildiyse yemek seçimi 'e' ya da menüden çıkış yapılana kadar bu döngü çalışır.
    while(yemekSecimi == 'h'){
        iter = iter->next;
        tekYemekYazdir(iter);
        printf(" : ");
        scanf(" %c", &yemekSecimi);
        if(yemekSecimi == 'e') {
            printf("\n%s Sectiniz.\n", iter->yemekAdi);
            printf("Siparisiniz en kisa zamanda teslim edilecektir.\nAfiyet Olsun!\n");
            return 0;
        } else if(yemekSecimi == 'a') {
            printf("\nAna menuye donuluyor.\n");
            return 1;
        }
    }
}

// menüye kullanıcının ekleneceği yeni yemeğin bilgileri burada alınır.
YemekNode *menuyeYeniYemekEkle(YemekNode *root) {
    int yemekGrami;
    char yemekAdi[256];
    double yemekFiyati;

    printf("Yemek adi: ");
    scanf("%s", yemekAdi);
    printf("Yemek fiyati: ");
    scanf("%lf", &yemekFiyati);
    printf("Yemek grami: ");
    scanf("%d", &yemekGrami);
    root = yemekEkle(root, yemekAdi, yemekFiyati, yemekGrami);
    return root;
}

// kullanıcının silmek istediği yemeğin adı bu fonksiyona gönderilir.
// yemek menüde bulunuyorsa yemek silinir ve root returnlenir.
YemekNode *silinecekYemek(YemekNode *root, char yemekAdi[]) {
    YemekNode *iter = root;
    YemekNode *temp;
    if(root == NULL) {
        printf("Menuden silinecek herhangi bir yemek yok.\n");
        return root;
    }

    if(strcmp(root->yemekAdi, yemekAdi) == 0) {
        while(iter->next != root) {
            iter = iter->next;
        }
        iter->next = root->next;
        free(root);
        printf("Yemek basariyla menuden silindi.\n\n");
        return iter->next;
    }

    while(strcmp(iter->next->yemekAdi, yemekAdi) != 0 && iter->next != root) {
        iter = iter->next;
    }

    if(iter->next == root) {
        printf("Silinecek yemek bulunamadi.\n");
        return root;
    }
    printf("yemek siliniyor...\n");
    temp = iter->next;
    iter->next = iter->next->next;
    free(temp);
    printf("Yemek basariyla menuden silindi.\n\n");
    return root;
}

// menüden yemek silineceği zaman alınacak yemeğin adı burada sorulur kullanıcıya.
YemekNode *menudenYemekSil(YemekNode *root) {
    char menuSecimi = 'h';
    char yemekAdi[256];

    printf("Silmek istediginiz yemegin adini giriniz: ");
    scanf("%s", yemekAdi);
    root = silinecekYemek(root, yemekAdi);

    YemekNode *iter = root;
    
}

// ana menü seçimleri burada yapılır.
YemekNode *anaMenu(YemekNode *root) {
    int menuSecimi;
    
    printf("1- Yemek ekle\n2- Yemek sil\n3- Tum yemekleri listele\n4- Yemek sec\n5- Cikis\nSecim: ");
    scanf("%d", &menuSecimi);
    if(menuSecimi == 1) {
        root = menuyeYeniYemekEkle(root);
        printf("Yeni yemek menuye eklendi.\n\n");
        anaMenu(root);
    }
    else if(menuSecimi == 2) {
        root = menudenYemekSil(root);
        anaMenu(root);
    }
    else if(menuSecimi == 3) {
        yemekleriListele(root);
        anaMenu(root);
    }
    else if(menuSecimi == 4) {
        if(yemekSec(root) == 0) {
            return root;
        } else {
            anaMenu(root);
        }
    } else {
        printf("Cikis yapiliyor.\n");
        return root;
    }
    return root;
}

// menu burada input dosyasına geri eklenir.
void menuyuDosyayaEkle(YemekNode *root) {
    FILE *yemekListesi = fopen("menu.txt", "w");
    YemekNode *iter = root;

    while(iter->next != root) {
        fprintf(yemekListesi, "%s %d %lf\n", iter->yemekAdi, iter->yemekGrami, iter->yemekFiyati);
        iter = iter->next;
        printf("eklendi.\n");
    }
    fprintf(yemekListesi, "%s %d %lf\n", iter->yemekAdi, iter->yemekGrami, iter->yemekFiyati);
    fclose(yemekListesi);
}

// main fonksiyonu.
int main()
{
    FILE *yemekListesi = fopen("menu.txt", "r");
    YemekNode *root = NULL;

    root = txtYazdir(yemekListesi, root);
    root = anaMenu(root);
    menuyuDosyayaEkle(root);
    return 0;
}
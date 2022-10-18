#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define CHAR_SIZE 100

typedef struct Menu
{
    struct Menu *sonraki;
    char yemek_adi[CHAR_SIZE];
    double yemek_fiyati;
    int yemek_grami;
} Menu;

/*Menüyü listeleyen fonksiyon*/
void MenuListele(Menu *YemekMenusu)
{
    /*Yemek listesinin boş olduğu durum kontrol ediliyor*/
    if(YemekMenusu == NULL)
    {
        printf("Yemek menusu bos.\n");
        return;
    };
    /*Menü üzerinde gezileceği için YemekMenusu objesi kaybedilecek,
    bu durumu engellemek için geçici bir yemek menüsü oluşturuldu*/
    Menu *GeciciYemekMenusu = YemekMenusu;
    /*while döngüsü ile geçici menüde bulunan tüm yemekler
    gezilerek ekrana yazdırılır*/
    printf("%s %dgr %.1lf TL\n", GeciciYemekMenusu->yemek_adi, GeciciYemekMenusu->yemek_grami, GeciciYemekMenusu->yemek_fiyati);
    while(GeciciYemekMenusu->sonraki != YemekMenusu)
    {
        GeciciYemekMenusu = GeciciYemekMenusu->sonraki;
        printf("%s %dgr %.1lf TL\n", GeciciYemekMenusu->yemek_adi, GeciciYemekMenusu->yemek_grami, GeciciYemekMenusu->yemek_fiyati);        
    };
};

Menu *YemekOlustur(char yeni_yemek_adi[], int yeni_yemek_grami, double yeni_yemek_fiyati)
{
    Menu *YeniYemek = (Menu *)malloc(sizeof(Menu));
    strcpy(YeniYemek->yemek_adi, yeni_yemek_adi);
    YeniYemek->yemek_grami = yeni_yemek_grami;
    YeniYemek->yemek_fiyati = yeni_yemek_fiyati;
    return YeniYemek;
};

Menu *MenuyeYemekEkle(Menu *YemekMenusu, char yemek_adi[], double yemek_fiyati, int yemek_grami)
{
    /*Menüde daha önce yemek olup olmadığına bakılır*/
    if(YemekMenusu == NULL)
    {
        YemekMenusu = YemekOlustur(yemek_adi, yemek_grami, yemek_fiyati);
        /*menü boş olduğundan sonraki menüye kendi bağlanır,
        böylece dairesel listeye dönüştürülmüş olur.*/
        YemekMenusu->sonraki = YemekMenusu;
        return YemekMenusu;
    }
    if(YemekMenusu->yemek_fiyati > yemek_fiyati)
    {
        Menu *GeciciYemekMenusu = YemekMenusu;
        Menu *YeniYemek = YemekOlustur(yemek_adi, yemek_grami, yemek_fiyati);
        YeniYemek->sonraki = YemekMenusu;
        while(GeciciYemekMenusu->sonraki != YemekMenusu)
        {
            GeciciYemekMenusu = GeciciYemekMenusu->sonraki;
        }
        GeciciYemekMenusu->sonraki = YeniYemek;
        return YeniYemek;
    }
    /*Menüde daha önce yemek varsa geçici bir yemek menüsü oluşturulur 
    çünkü bu menü üzerinde ilerlenecek ve fiyatına göre yemek araya eklenecek,
    bu durumda orijinal yemek menüsünün değişmemesi gerekiyor*/
    Menu *GeciciYemekMenusu = YemekMenusu;
    /*Fiyatı yeni eklenecek yemekten daha yüksek bir yemek bulunana kadar
    geçici yemek menüsünde ilerleniyor*/
    while(GeciciYemekMenusu->sonraki->yemek_fiyati < yemek_fiyati && GeciciYemekMenusu->sonraki != YemekMenusu)
    {
        GeciciYemekMenusu = GeciciYemekMenusu->sonraki;
    }
    Menu *YeniYemek = YemekOlustur(yemek_adi, yemek_grami, yemek_fiyati);
    YeniYemek->sonraki = GeciciYemekMenusu->sonraki;
    GeciciYemekMenusu->sonraki = YeniYemek;
    return YemekMenusu;
};

/*kullanıcı menüden yemek silmek istediği zaman yemek adı sorulur ve input alınır,
menü boşsa ya da menüde yemek bulunamadıysa hata mesajları bastırılır, yemek bulunursa
menüden silinir ve yeni menü return edilir*/
Menu *MenudenYemekSil(Menu *YemekMenusu, char silinecek_yemek_adi[])
{
    if(YemekMenusu == NULL)
    {
        printf("Menu bos.\n");
        return NULL;
    };
    if(strcmp(YemekMenusu->yemek_adi, silinecek_yemek_adi) == 0)
    {
        Menu *GeciciYemekMenusu = YemekMenusu;
        while(GeciciYemekMenusu->sonraki != YemekMenusu)
            GeciciYemekMenusu = GeciciYemekMenusu->sonraki;
            
        GeciciYemekMenusu->sonraki = YemekMenusu->sonraki;
        printf("%s silindi. Ana menuye donuluyor...\n", silinecek_yemek_adi);
        free(YemekMenusu);
        GeciciYemekMenusu = GeciciYemekMenusu->sonraki;
        return GeciciYemekMenusu;
    };
    Menu *GeciciYemekMenusu = YemekMenusu;
    while(strcmp(GeciciYemekMenusu->sonraki->yemek_adi, silinecek_yemek_adi) != 0 && GeciciYemekMenusu->sonraki != YemekMenusu)
        GeciciYemekMenusu = GeciciYemekMenusu->sonraki;

    if(GeciciYemekMenusu->sonraki == YemekMenusu)
    {
        printf("%s menude bulunamadi. Ana menuye donuluyor...\n", silinecek_yemek_adi);
        return YemekMenusu;
    };
    Menu *SilinecekYemek = GeciciYemekMenusu->sonraki;
    GeciciYemekMenusu->sonraki = GeciciYemekMenusu->sonraki->sonraki;
    printf("%s silindi. Ana menuye donuluyor...\n", silinecek_yemek_adi);
    free(SilinecekYemek);
    return YemekMenusu;
};

/*kullanıcı menüden yemek eklemek istediği zaman bu fonksiyonla
yeni yemeğin bilgileri sorulur ve yemek menüye eklenir*/
Menu* YeniYemekEkle(Menu *YemekMenusu)
{
    char eklenecek_yemek_adi[CHAR_SIZE];
    double eklenecek_yemek_fiyati;
    int eklenecek_yemek_grami;
    printf("Eklemek istediginiz yemegin adini giriniz: ");
    scanf("%s", eklenecek_yemek_adi);
    printf("%s icin fiyat giriniz: ", eklenecek_yemek_adi);
    scanf("%lf", &eklenecek_yemek_fiyati);
    printf("%s icin porsiyon grami giriniz: ", eklenecek_yemek_adi);
    scanf("%d", &eklenecek_yemek_grami);
    /*menüye yemek ekleme fonksiyonu çağrılarak bilgiler
    gönderilir ve return edilen değer menüye eşitlenir*/
    YemekMenusu = MenuyeYemekEkle(YemekMenusu, eklenecek_yemek_adi, eklenecek_yemek_fiyati, eklenecek_yemek_grami);
    return YemekMenusu;
};

void YemekSecimiIcinYemekListele(Menu *ListedekiYemek)
{
    printf("%s %dgr %.1lf TL (e/h/a) : ", ListedekiYemek->yemek_adi, ListedekiYemek->yemek_grami, ListedekiYemek->yemek_fiyati);
};

bool MenudenYemekSec(Menu *YemekMenusu)
{
    char YemekSecimi = 'h';
    Menu *ListelenenYemek = YemekMenusu;
    printf("Yemek secimi icin 'e',\n");
    printf("bir sonraki yemege gecmek icin 'h',\n");
    printf("ana menuye donmek icin 'a' degerini giriniz.\n");
    while(YemekSecimi != 'a')
    {
        YemekSecimiIcinYemekListele(ListelenenYemek);
        scanf(" %c", &YemekSecimi);
        if(YemekSecimi == 'h')
        {
            ListelenenYemek = ListelenenYemek->sonraki;
            continue;
        }
        else if(YemekSecimi == 'e')
        {
            printf("%s Sectiniz.\n", ListelenenYemek->yemek_adi);
            printf("Siparisiniz en kisa zamanda teslim edilecektir.\n");
            printf("Afiyet Olsun!\n");
            return false;
        }
        else
        {
            printf("Yanlis secim yaptiniz. Ana menuye donuluyor...\n");
            return true;
        }
    }
    printf("Ana menuye donuluyor...\n");
    return true;
};

Menu *TxtDosyasiOku(Menu *YemekMenusu)
{
    char dosya_adi[] = "menu.txt";
    FILE *menu = fopen(dosya_adi, "r");
    if(menu == NULL)
    {
        printf("Input dosyasi bulunamadi. Kontrol edin. (Dosya adinin 'menu.txt' olmasina dikkat edin.)\n");
        return NULL;
    }
    int ifAnyCharacter = fgetc(menu);
    if(ifAnyCharacter == EOF){
        printf("Menu icerigi bos, kontrol edin.\n");
        return NULL;
    }
    Menu *GeciciYemekListesi = YemekMenusu;
    char yemek_adi[CHAR_SIZE];
    double yemek_fiyati;
    int yemek_grami;
    while(!feof(menu))
    {
        fscanf(menu, "%s %d %lf", yemek_adi, &yemek_grami, &yemek_fiyati);
        if(feof(menu)) break;
        YemekMenusu = MenuyeYemekEkle(YemekMenusu, yemek_adi, yemek_fiyati, yemek_grami);
    }
    fclose(menu);
    return YemekMenusu;
}

int main()
{
    Menu *YemekMenusu = NULL;

    YemekMenusu = TxtDosyasiOku(YemekMenusu);
    if(YemekMenusu == NULL)
    {
        return 0;
    }
    int AnaMenuSecimi = 0;
    while(AnaMenuSecimi != 5)
    {
        printf("1- Yemek Ekle\n");
        printf("2- Yemek Sil\n");
        printf("3- Menuyu Listele\n");
        printf("4- Yemek Secimi Yap\n");
        printf("5- Cikis Yap\n");
        printf("Seciminiz: ");
        scanf("%d", &AnaMenuSecimi);

        if(AnaMenuSecimi == 1)
        {
            YemekMenusu = YeniYemekEkle(YemekMenusu);
        }
        else if(AnaMenuSecimi == 2)
        {
            char silinecek_yemek_adi[CHAR_SIZE];
            printf("Silmek istediginiz yemegin adini giriniz: ");
            scanf("%s", silinecek_yemek_adi);
            YemekMenusu = MenudenYemekSil(YemekMenusu, silinecek_yemek_adi);
        }
        else if(AnaMenuSecimi == 3) MenuListele(YemekMenusu);
        else if(AnaMenuSecimi == 4)
            if(MenudenYemekSec(YemekMenusu)==false)
                return 0;
        else if(AnaMenuSecimi == 5)
        {
            printf("Cikis yapiliyor...\n");
            return 0;
        }
    };
    return 0;
};
#include "YemekEkle.h"

Menu *YeniYemekEkle(char yeni_yemek_adi[], int yeni_yemek_grami, double yeni_yemek_fiyati){
    Menu *YeniYemek = (Menu *)malloc(sizeof(Menu));
    strcpy(YeniYemek->yemek_adi, yeni_yemek_adi);
    YeniYemek->yemek_grami = yeni_yemek_grami;
    YeniYemek->yemek_fiyati = yeni_yemek_fiyati;
    return YeniYemek;
};

Menu *MenuyeYemekEkle(Menu *YemekMenusu, char yemek_adi[], double yemek_fiyati, int yemek_grami) {
    /*Menüde daha önce yemek olup olmadığına bakılır*/
    if(YemekMenusu == NULL) {
        YemekMenusu = YeniYemekEkle(yemek_adi, yemek_grami, yemek_fiyati);
        /*menü boş olduğundan sonraki menüye kendi bağlanır,
        böylece dairesel listeye dönüştürülmüş olur.*/
        YemekMenusu->sonraki = YemekMenusu;
        return YemekMenusu;
    }
    if(YemekMenusu->yemek_fiyati > yemek_fiyati) {
        Menu *GeciciYemekMenusu = YemekMenusu;
        Menu *YeniYemek = YeniYemekEkle(yemek_adi, yemek_grami, yemek_fiyati);
        YeniYemek->sonraki = YemekMenusu;
        while(GeciciYemekMenusu->sonraki != YemekMenusu) {
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
    while(GeciciYemekMenusu->sonraki->yemek_fiyati < yemek_fiyati && GeciciYemekMenusu->sonraki != YemekMenusu) {
        GeciciYemekMenusu = GeciciYemekMenusu->sonraki;
    }
    Menu *YeniYemek = YeniYemekEkle(yemek_adi, yemek_grami, yemek_fiyati);
    YeniYemek->sonraki = GeciciYemekMenusu->sonraki;
    GeciciYemekMenusu->sonraki = YeniYemek;
    return YemekMenusu;
};
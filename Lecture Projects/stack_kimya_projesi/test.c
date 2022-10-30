#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define CHAR_SIZE 256
#define SOL_PARANTEZ 40
#define SAG_PARANTEZ 41

/* A~Z -> 65~90      a~z -> 97~122    ( -> 40      ) -> 41      0~9 -> 48~57   decimal values in ascii table */

struct Stack {
    char metin[CHAR_SIZE];
    int katSayi;
    struct Stack *next;
};

typedef struct Stack StackElements;
StackElements *STACK_1 = NULL;
StackElements *STACK_2 = NULL;

StackElements *pushStack2(char metin[], int katSayi);
StackElements *pushStack1(char metin[], int katSayi);

/* parametre olarak gönderilen STACK'e göre stack listelenir */
void displayStack(StackElements *STACK) {
    StackElements *iterStack1 = STACK;
    printf("Stack ->\n");
    while(iterStack1 != NULL) {
        printf("%s: %d\n", iterStack1->metin, iterStack1->katSayi);
        iterStack1 = iterStack1->next;
    }
}

void katSayiylaCarp(int parantezCarpani) {
    StackElements *iter = STACK_2;
    while(iter != NULL) {
        iter->katSayi *= parantezCarpani;
        iter = iter->next;
    }
}

bool sonKarakterParantez(StackElements *STACK) {
    StackElements *iter = STACK;
    while(iter->next != NULL) iter = iter->next;
    if(iter->metin[0] == SOL_PARANTEZ) return true;
    return false;
}

StackElements *sonKarakteriSil(StackElements *STACK) {
    StackElements *iter = STACK;
    StackElements *prevNode;
    while(iter->next != NULL) {
        prevNode = iter;
        iter = iter->next;
    } 
    prevNode->next = NULL;
    free(iter);
    return STACK;
}

/* parantezCarpani parametre olarak alındı ve sol parantez*/
void popStack1PushStack2() {
    StackElements *iterStack1 = STACK_1;
    StackElements *iterStack2 = STACK_2;
    StackElements *prevNode;
    int katSayi;
    char metin[CHAR_SIZE];
    bool sonKarakterParantezMi = sonKarakterParantez(STACK_1);

    while(sonKarakterParantezMi != true) {
        iterStack1 = STACK_1;
        iterStack2 = STACK_2;
        if(iterStack1->next == NULL) {
            katSayi = iterStack1->katSayi;
            strcpy(metin, iterStack1->metin);
            free(iterStack1);
            iterStack1 = NULL;
            STACK_2 = pushStack2(metin, katSayi);
            return;
        }

        while(iterStack1->next != NULL) {
            prevNode = iterStack1;
            iterStack1 = iterStack1->next;
        }
        
        katSayi = iterStack1->katSayi;
        strcpy(metin, iterStack1->metin);
        prevNode->next = NULL;
        free(iterStack1);
        STACK_2 = pushStack2(metin, katSayi);
        sonKarakterParantezMi = sonKarakterParantez(STACK_1);
    }
    STACK_1 = sonKarakteriSil(STACK_1);
    
}

bool isStackEmpty(StackElements *STACK) {
    if(STACK == NULL) return true;
    return false;
}

void popStack2PushStack1() {
    StackElements *iterStack1 = STACK_1, *iterStack2 = STACK_2, *prevNode;
    bool stack2Empty = isStackEmpty(STACK_2);
    int katSayi;
    char metin[CHAR_SIZE];
    while(stack2Empty != true) {
        iterStack1 = STACK_1;
        iterStack2 = STACK_2;
        if(STACK_2->next == NULL) {
            katSayi = STACK_2->katSayi;
            strcpy(metin, STACK_2->metin);
            pushStack1(metin, katSayi);
            STACK_2 = NULL;
            //displayStack(STACK_1);
            break;
        }
        while(iterStack2->next != NULL) {
            prevNode = iterStack2;
            iterStack2 = iterStack2->next;
        }
        
        katSayi = iterStack2->katSayi;
        strcpy(metin, iterStack2->metin);
        pushStack1(metin, katSayi);
        //displayStack(STACK_1);
        prevNode->next = NULL;
        free(iterStack2);
        stack2Empty = isStackEmpty(STACK_2);
    }
}

/* verilen parametreler STACK_2 içerisine atılır */
StackElements *pushStack2(char metin[], int katSayi) {
    if(STACK_2 == NULL) {
        STACK_2 = (StackElements *) malloc(sizeof(StackElements));
        strcpy(STACK_2->metin, metin);
        STACK_2->katSayi = katSayi;
        STACK_2->next = NULL;
        //printf("%s: %d eklendi NULL'di\n", STACK_2->metin, STACK_2->katSayi);
        //displayStack1();
        return STACK_2;
    }
    StackElements *iterStack1 = STACK_2;
    while(iterStack1->next != NULL) iterStack1 = iterStack1->next;
    iterStack1->next = (StackElements *) malloc(sizeof(StackElements));
    strcpy(iterStack1->next->metin, metin);
    iterStack1->next->katSayi = katSayi;
    iterStack1->next->next = NULL;
    //printf("%s: %d eklendi\n", iterStack1->next->metin, iterStack1->next->katSayi);
    //displayStack1();
    return STACK_2;
}

/* alınan parametre değerine bakılmaksızın direkt STACK_1'e ekleme işlemi yapar
çünkü daha öncesinde eklenip eklenmemesi kontrollerini yapmıştık */
StackElements *pushStack1(char metin[], int katSayi) {
    if(STACK_1 == NULL) {
        STACK_1 = (StackElements *) malloc(sizeof(StackElements));
        strcpy(STACK_1->metin, metin);
        STACK_1->katSayi = katSayi;
        STACK_1->next = NULL;
        //printf("%s: %d eklendi NULL'di\n", STACK_1->metin, STACK_1->katSayi);
        //displayStack1();
        return STACK_1;
    }
    StackElements *iterStack1 = STACK_1;
    while(iterStack1->next != NULL) iterStack1 = iterStack1->next;
    iterStack1->next = (StackElements *) malloc(sizeof(StackElements));
    strcpy(iterStack1->next->metin, metin);
    iterStack1->next->katSayi = katSayi;
    iterStack1->next->next = NULL;
    //printf("%s: %d eklendi\n", iterStack1->next->metin, iterStack1->next->katSayi);
    //displayStack1();
    return STACK_1;
}

/* gelen parametrelere göre ekleme yapar ya da stack1'den çıkarılıp
stack2'ye ekleme ve katsayıyla çarpma ardından stack2'nin boşalılıp
stack1'e geri eklenmesi işlemlerini yapar */
void push(char metin[], int katSayi) {
    /* parantez ve parantez katsayısı olmayan element olduğunu belirtir */
    if(katSayi != 0 && metin[0] != '1') {
        /* gelen parametre doğrudan STACK_1'e eklenebilir */
        STACK_1 = pushStack1(metin, katSayi);
        return;
    }
    /* gelen metinin ilk indexinde parantez olduğunu belirtiyor */
    if(katSayi == 0) {
        /* gelen parametre sol yani açma parantezi olduğundan STACK_1'e eklenebilir */
        if(metin[0] == SOL_PARANTEZ) {
            STACK_1 = pushStack1(metin, katSayi);
            return;
        }
        /* STACK_1'den alınıp 2'ye atılacak ve katsayıyla çarpılıp 1'e geri alınacaklar */
        if(metin[0] == SAG_PARANTEZ) {
            
            return;
        }
    }
    /* gelen katSayi'nin paranteze ait bir katsayı olduğunu anlıyoruz haliyle STACK2'ye ekleme yapıp çarpacağız */
    if(metin[0] == '1') {
        /*geriye dönük stack2ye ekleme ve çarpma sonrasında tekrar ekleme işlemi burada dönecek*/
        //printf("Parantez carpani : %d\n", katSayi);
        popStack1PushStack2();
        katSayiylaCarp(katSayi);
        popStack2PushStack1();
    }
}

/* alınan parametreleri push fonksiyonuna ileten aracı fonksiyon */
void stackeEkle(char metin[], int katSayi) {
    //printf("%s %d\n", metin, katSayi);
    push(metin, katSayi);
}

/* mainden gelen uzun stringi sonraki kelimenin başlangıcını parantez
ya da büyük harf olarak algılayarak parçalar*/
void stringiParcala(char metin[]) {
    char geciciMetin[CHAR_SIZE];
    int geciciMetinIndex = 0, i, index;
    int katSayi;
    char katSayiString[CHAR_SIZE];

    for(index = 0; index < strlen(metin); index++) {
        //printf("su anki index: %c\n", metin[index]);
        /* şu anki karakter parantez */
        if(metin[index] == SOL_PARANTEZ || metin[index] == SAG_PARANTEZ) {
            geciciMetin[geciciMetinIndex++] = metin[index],
            geciciMetin[geciciMetinIndex++] = '\0';
            katSayi = 0;
            stackeEkle(geciciMetin, katSayi);
            for(i = 0; i < CHAR_SIZE; i++) geciciMetin[i] = '\0';
            geciciMetinIndex = 0;
            if(metin[index+1] == SOL_PARANTEZ || metin[index+1] == SAG_PARANTEZ) {
                geciciMetin[0] = '1';
                geciciMetin[1] = '\0';
                katSayi = 1;
                stackeEkle(geciciMetin, katSayi);
                for(i = 0; i < CHAR_SIZE; i++) geciciMetin[i] = '\0';
                geciciMetinIndex = 0;
            }
            continue;
        }
        /* şu anki karakter büyük harf */
        if(metin[index] >= 65 && metin[index] <= 90) {
            /* sonraki karakter sayı olabilir */
            if(metin[index+1] >= 48 && metin[index+1] <= 57) {
                geciciMetin[geciciMetinIndex++] = metin[index];
                geciciMetin[geciciMetinIndex++] = '\0';
                katSayiString[0] = metin[index+1];
                katSayiString[1] = '\0';
                katSayi = atoi(katSayiString);
                stackeEkle(geciciMetin, katSayi);
                for(i = 0; i < CHAR_SIZE; i++) geciciMetin[i] = '\0';
                geciciMetinIndex = 0;
                continue;
            }
            /* sonraki karakter parantez olabilir */
            if(metin[index+1] == SOL_PARANTEZ || metin[index+1] == SAG_PARANTEZ) {
                geciciMetin[geciciMetinIndex++] = metin[index];
                geciciMetin[geciciMetinIndex++] = '\0';
                katSayi = 1;
                stackeEkle(geciciMetin, katSayi);
                for(i = 0; i < CHAR_SIZE; i++) geciciMetin[i] = '\0';
                geciciMetinIndex = 0;
                continue;
            }
            /* sonraki karakter küçük harf olabilir */
            if(metin[index+1] >= 97 && metin[index+1] <= 122) {
                geciciMetin[geciciMetinIndex++] = metin[index];
                continue;
            }
            /* sonraki karakter büyük harf olabilir */
            if(metin[index+1] >= 65 && metin[index+1] <= 90) {
                geciciMetin[geciciMetinIndex++] = metin[index];
                geciciMetin[geciciMetinIndex++] = '\0';
                katSayi = 1;
                stackeEkle(geciciMetin, katSayi);
                for(i = 0; i < CHAR_SIZE; i++) geciciMetin[i] = '\0';
                geciciMetinIndex = 0;
                continue;
            }
            /* son karakter olduğundan katsayısı 1 olarak gönderilir */
            if(index+1 == strlen(metin)) {
                geciciMetin[geciciMetinIndex++] = metin[index];
                geciciMetin[geciciMetinIndex++] = '\0';
                katSayi = 1;
                stackeEkle(geciciMetin, katSayi);
                for(i = 0; i < CHAR_SIZE; i++) geciciMetin[i] = '\0';
                geciciMetinIndex = 0;
                continue;
            }
        }
        /* şu anki karakter küçük harfse */
        if(metin[index] >= 97 && metin[index] <= 122) {      
            /* sonraki karakter yine küçük harf */      
            if (metin[index+1] >= 97 && metin[index+1] <= 122) {
                geciciMetin[geciciMetinIndex++] = metin[index];
                continue;
            }
            /* sonraki karakter büyük harf */
            if (metin[index+1] >= 65 && metin[index+1] <= 90) {
                geciciMetin[geciciMetinIndex++] = metin[index];
                geciciMetin[geciciMetinIndex++] = '\0';
                katSayi = 1;
                stackeEkle(geciciMetin, katSayi);
                for(i = 0; i < CHAR_SIZE; i++) geciciMetin[i] = '\0';
                geciciMetinIndex = 0;
                continue;
            }
            /* sonraki karakter rakam */
            if(metin[index+1] >= 48 && metin[index+1] <= 57) {
                geciciMetin[geciciMetinIndex++] = metin[index];
                geciciMetin[geciciMetinIndex++] = '\0';
                katSayiString[0] = metin[index+1];
                katSayiString[1] = '\0';
                katSayi = atoi(katSayiString);
                stackeEkle(geciciMetin, katSayi);
                for(i = 0; i < CHAR_SIZE; i++) geciciMetin[i] = '\0';
                geciciMetinIndex = 0;
                continue;
            }
            /* sonraki karakter parantez */
            if(metin[index+1] == SOL_PARANTEZ || metin[index+1] == SAG_PARANTEZ){
                geciciMetin[geciciMetinIndex++] = metin[index];
                geciciMetin[geciciMetinIndex++] = '\0';
                katSayi = 1;
                stackeEkle(geciciMetin, katSayi);
                for(i = 0; i < CHAR_SIZE; i++) geciciMetin[i] = '\0';
                geciciMetinIndex = 0;
                continue;
            }
            /* son karakter olduğundan katsayısı 1 olarak gönderilir */
            if(index+1 == strlen(metin)) {
                geciciMetin[geciciMetinIndex++] = metin[index];
                geciciMetin[geciciMetinIndex++] = '\0';
                katSayi = 1;
                stackeEkle(geciciMetin, katSayi);
                for(i = 0; i < CHAR_SIZE; i++) geciciMetin[i] = '\0';
                geciciMetinIndex = 0;
                continue;
            }
        }
        /* şu anki karakter rakam */
        if (metin[index] >= 48 && metin[index] <= 57) {
            /* önceki karakter kapama yani sağ parantez olduğundan şu anki rakamın parantez katsayısı olduğunu anlıyoruz */
            if(metin[index-1] == SAG_PARANTEZ) {
                geciciMetin[0] = '1';
                geciciMetin[1] = '\0';
                katSayiString[0] = metin[index];
                katSayiString[1] = '\0';
                katSayi = atoi(katSayiString);
                stackeEkle(geciciMetin, katSayi);
            }
        }
    }
}

StackElements *ilkKarakterParantezMi(StackElements *STACK_1) {
    if(STACK_1->metin[0] == SOL_PARANTEZ) {
        STACK_1 = STACK_1->next;
        return STACK_1;
    }
    return STACK_1;
}

int main() {

    char metin[] = "Kr4(OnNe(SOne3)2)2";

    stringiParcala(metin);
    STACK_1 = ilkKarakterParantezMi(STACK_1);
    //printf("test\n");
    displayStack(STACK_1);



    return 0;
}
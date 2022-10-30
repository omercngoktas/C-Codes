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
    bool parantezKatSayisiMi;
    bool parantezMi;
    char parantez;
    struct Stack *next;
};

typedef struct Stack StackElements;
StackElements *STACK_1 = NULL;
StackElements *STACK_2 = NULL;

StackElements *popStack2PushStack1(StackElements *STACK_1, StackElements *STACK_2) {
    StackElements *iterStack2 = STACK_2;
    StackElements *iterStack1 = STACK_1;
    bool isStack2Empty = false;
    while(isStack2Empty != false) {
        while(iterStack2->next != NULL) {
            iterStack2 = iterStack2->next;
        }
        while(iterStack1->next != NULL) {
            iterStack1 = iterStack1->next;
        }
        iterStack1->next = (StackElements *) malloc(sizeof(StackElements));
        strcpy(iterStack1->next->metin, iterStack2->metin);
        iterStack1->next->katSayi = iterStack2->katSayi;
        iterStack1->next->parantezMi = iterStack2->parantezMi;
        iterStack1->next->parantezKatSayisiMi = iterStack2->parantezKatSayisiMi;
        iterStack1->next->next = NULL;
        if(STACK_2 == iterStack2) {
            isStack2Empty = true;
            STACK_2 = NULL;
            return STACK_1;
        }    
    } 
}

StackElements *popStack1PushStack2(StackElements *STACK_1, StackElements *STACK_2, int parantezKatSayisi) {
    StackElements *iter = STACK_1;
    bool isOpDone = false;
    while(isOpDone != false) {
        iter = STACK_1;
        while(iter->next != NULL) iter = iter->next;

        /* STACK_1'den STACK_2'ye aktarma bitti çünkü paranteze rastladık, şimdi parantez katsayısıyla katsayılar çarpılacak ve STACK_1'e aktarılacak */
        if(iter->parantezMi == true) {
            iter = NULL;
            StackElements *iterStack_2 = STACK_2;
            while(iterStack_2->next != NULL) {
                iterStack_2->katSayi *= parantezKatSayisi;
                iterStack_2 = iterStack_2->next;
            }
            iterStack_2->katSayi *= parantezKatSayisi;
            /* stack_2'nin boşaltılıp STACK_1'e eklenmesi */
            STACK_1 = popStack2PushStack1(STACK_1, STACK_2);
        } 
        if(STACK_2 == NULL) {
            STACK_2 = (StackElements *) malloc(sizeof(StackElements));
            strcpy(STACK_2->metin, iter->metin);
            STACK_2->katSayi = iter->katSayi;
            STACK_2->parantezMi = iter->parantezMi;
            STACK_2->parantezKatSayisiMi = iter->parantezKatSayisiMi;
            STACK_2->next = NULL;
            iter = NULL;
            continue;
        }
        StackElements *iterStack_2 = STACK_2;
        while(iterStack_2->next != NULL) iterStack_2 = iterStack_2->next;
        iterStack_2->next = (StackElements *) malloc(sizeof(StackElements));
        strcpy(iterStack_2->next->metin, iter->metin);
        iterStack_2->katSayi = iter->katSayi;
        iterStack_2->parantezMi = iter->parantezMi;
        iterStack_2->parantezKatSayisiMi = iter->parantezKatSayisiMi;
        iterStack_2->next->next = NULL;
        iter = NULL;
        continue;
    }
    
}

bool sagParantezMi = false;
int parantezinKatSayisi;

StackElements *push(StackElements *STACK_1, char metin[], int katSayi, bool parantezKatSayisiMi, bool parantezMi, char parantez) {
    
    /* bu durumda gelen alınan parametrenin katsayılı bir string olduğunu biliyoruz */
    if(parantezKatSayisiMi == false && parantezMi == false) {
        if(STACK_1 == NULL) {
            STACK_1 = (StackElements *) malloc(sizeof(StackElements));
            strcpy(STACK_1->metin, metin);
            STACK_1->katSayi = katSayi;
            STACK_1->next = NULL;
            STACK_1->parantezMi = false;
            STACK_1->parantezKatSayisiMi = false;
            return STACK_1;
        }
        StackElements *iter = STACK_1;
        while(iter->next != NULL) iter = iter->next;
        iter->next = (StackElements *) malloc(sizeof(StackElements));
        strcpy(iter->next->metin, metin);
        iter->next->katSayi = katSayi;
        iter->next->next = NULL;
        iter->next->parantezMi = false;
        iter->next->parantezKatSayisiMi = false;
        return STACK_1;
    }

    /* gelen parametrenin parantez olduğunu biliyoruz */
    if(parantezMi == true) {
        /* gelen parantez sol yani açma olduğu için STACK_1'e eklemeye devam ediyoruz */
        if(parantez == SOL_PARANTEZ) {
            if(STACK_1 == NULL) {
                STACK_1 = (StackElements *) malloc(sizeof(StackElements));
                STACK_1->parantez = parantez;
                STACK_1->parantezMi = true;
                STACK_1->parantezKatSayisiMi = false;
                STACK_1->next = NULL;
                return STACK_1;
            }
            StackElements *iter = STACK_1;
            while(iter->next != NULL) iter = iter->next;
            iter->next = (StackElements *) malloc(sizeof(StackElements));
            iter->next->parantezKatSayisiMi = false;
            iter->next->parantezMi = true;
            iter->next->parantez = parantez;
            iter->next->next = NULL;
            return STACK_1;
        }
        
        /* gelen parametre sağ yani kapatma parantezi, sol parantez görene kadar STACK_2'ye eklenecek ve katsayıyla çarpılacak değerler */
        if(parantez == SAG_PARANTEZ) {
            return STACK_1;
        }
    }

    /* gelen parametrenin parantez katsayısı olduğunu biliyoruz */
    if(parantezKatSayisiMi == true) {
        STACK_1 = popStack1PushStack2(STACK_1, STACK_2, katSayi);
        return STACK_1;
    }
}

void stackYazdir(StackElements *root) {
    if(root == NULL) {
        printf("Stack bos.\n");
        return;
    }
    StackElements *iter = root;
    while(iter != NULL) {
        printf("%s: %d\n", iter->metin, iter->katSayi);
        iter = iter->next;
    }
    return;
}

bool parantezIceriyor(char metin[]) {
    int i, length = strlen(metin);
    for(i = 0; i < length; i++) {
        if(metin[i] == 40 || metin[i] == 41) {
            return true; /* string içerisinde parantez olduğundan true değer döndürür*/
        }
    }
    return false; /* string içerisinde parantez olmadığını döndürür (false). */
};

void metniBastir(char rootMetin[], bool rootParantezMi) {
    char metin[CHAR_SIZE], geciciMetin[CHAR_SIZE];
    int katSayi, geciciMetinIndex = 0, i;
    bool parantezMi = rootParantezMi;
    char parantez;
    /* parantezMi değeri true olduğundan gelen stringin parantez olduğunu biliyoruz */
    if(parantezMi == true) {
        
        parantez = rootMetin[0];
        katSayi = 0;
        /* gelen parantez sol yani açma parantezi */
        if(parantez == SOL_PARANTEZ) {
            printf("SOL PARANTEZ %c\n", parantez);
            return;
        }
        /* gelen parantez sağ yani kapama parantezi */
        printf("SAG PARANTEZ %c\n", parantez);
        return;
    }
    /* gelen string büyük harfle başlıyor ve katsayısı var*/
    if(rootMetin[strlen(rootMetin)-1] >= 48 && rootMetin[strlen(rootMetin)-1] <= 57 && strlen(rootMetin) > 1) {
        for(i = 0; i < strlen(rootMetin)-1; i++) {
            /* geciciMetin'e son metinden bir önceki karaktere kadar olan kısım atılıyor çünkü son karakter katSayı olacak */
            geciciMetin[i] = rootMetin[i];
            geciciMetin[i+1] = '\0';
        }
        /* son karakter kat sayı olduğundan bu karakterden ascii table değeri çıkartılıp decimal değer elde ediliyor ve katSayı'ya atılıyor */
        katSayi = rootMetin[strlen(rootMetin)-1]-48;
        printf("%s %d\n", geciciMetin, katSayi);
        return;
    }
    /* gelen string'te yalnızca kat sayı var ve bu katsayı parantezin tümünün katsayısı */
    if(rootMetin[strlen(rootMetin)-1] >= 48 && rootMetin[strlen(rootMetin)-1] <= 57 && strlen(rootMetin) == 1) {
        katSayi = rootMetin[0]-48;
        printf("%d\n", katSayi);
        return;
    }
    /* gelen stringin kat sayısı yok, tek karakter ya da çok karakter olabilir, bu durumda katsayısının 1 olduğunu biliyoruz */
    katSayi = 1;
    printf("%s %d\n", rootMetin, katSayi);

}

void testFunc(char metin[]) {    
    char geciciMetin[CHAR_SIZE];
    int geciciMetinIndex = 0, i, index;

    for(index = 0; index < strlen(metin); index++) {
        if(metin[index] == SAG_PARANTEZ && metin[index+1] == SAG_PARANTEZ) {
            
        }
        if(metin[index] == SOL_PARANTEZ || metin[index] == SAG_PARANTEZ) {
            geciciMetin[0] = metin[index];
            geciciMetin[1] = '\0';
            metniBastir(geciciMetin, true);
            for(i = 0; i < CHAR_SIZE; i++) geciciMetin[i] = '\0';
            continue;
        }
        if(index+1 == strlen(metin)) {
            geciciMetin[0] = metin[index];
            geciciMetin[1] = '\0';
            if(metin[index] == SOL_PARANTEZ || metin[index] == SAG_PARANTEZ){
                metniBastir(geciciMetin, true);
            }
            metniBastir(geciciMetin, false);
        }
        if((metin[index] >= 65 && metin[index] <= 90)) {
            if((metin[index+1] >= 65 && metin[index+1] <= 90) || (metin[index+1] == SOL_PARANTEZ || metin[index+1] == SAG_PARANTEZ)) {
                geciciMetin[geciciMetinIndex++] = metin[index];
                geciciMetin[geciciMetinIndex] = '\0';
                metniBastir(geciciMetin, false);
                for(i = 0; i < CHAR_SIZE; i++) geciciMetin[i] = '\0';
                geciciMetinIndex = 0;
                continue;
            }
            geciciMetin[geciciMetinIndex++] = metin[index];
            continue;
        }

        geciciMetin[geciciMetinIndex++] = metin[index];
        if((metin[index+1] >= 65 && metin[index+1] <= 90) || (metin[index+1] == SOL_PARANTEZ || metin[index+1] == SAG_PARANTEZ)) {
            geciciMetin[geciciMetinIndex] = '\0';
            metniBastir(geciciMetin, false);
            for(i = 0; i < CHAR_SIZE; i++) geciciMetin[i] = '\0';
            geciciMetinIndex = 0;
            continue;
        }
    }

}

int main() {
    StackElements *STACK_1 = NULL;
    StackElements *STACK_2 = NULL;

    char metin[] = "Kr4(OnNe(SOne3)2)2";

    printf("Length: %d\n\n", strlen(metin));
    testFunc(metin);

    // root = push(root, "Kr", 4);
    // root = push(root, "On", 1);
    // root = push(root, "Ne", 1);
    // root = push(root, "S", 1);
    // root = push(root, "One", 3);
    // stackYazdir(root);
    return 0;
}
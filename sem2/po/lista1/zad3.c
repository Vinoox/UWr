/*
* Maciej Styś
* lista1: zad3
* gcc zad3.c
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Tablica{
    int idx;
    float val;
    struct Tablica* next;
}Tablica;

Tablica* nowaTablica(){
    return NULL;
}

Tablica* utworz(int idx, float val){
    Tablica* pom = (Tablica*) malloc(sizeof(Tablica));
    pom->idx = idx;
    pom->val = val;
    pom->next = NULL;
    return pom;
}

void dodaj(Tablica** tab, int idx, float val){
    if(*tab == NULL){
        *tab = utworz(idx, val);
    }
    else{
        Tablica* pom = *tab;
        if(idx < pom->idx){
            Tablica* nowa = utworz(idx, val);
            for(Tablica* licznik = nowa; licznik->idx < pom->idx; licznik = licznik->next){
                int n = licznik->idx;
                if(n == pom->idx - 1) licznik->next = pom;
                else licznik->next = utworz(n + 1, 0);
            }
            *tab = nowa;
        }
        else{
            for(Tablica* licznik = *tab; licznik->idx <= idx; licznik = licznik->next){
                if(licznik->idx == idx){
                    licznik->val = val;
                    break;
                }
                else{
                    if(licznik->next == NULL){
                    int n = licznik->idx;
                    licznik->next = utworz(n + 1, 0);
                    }
                }
            }
        }
    }
}

void indeks(Tablica* t, int idx){
    if(idx < t->idx){
        printf("nie ma takiego indeksu\n");
    }
    else{
        for(Tablica* licznik = t; licznik != NULL; licznik = licznik->next){
            if(idx == licznik->idx){
                printf("%d : %f\n", idx, licznik->val);
                break;
            }
            if(licznik->next == NULL) printf("nie ma takiego indeksu\n");
        }
    }
}

void show(Tablica* t){
    for(Tablica* licznik = t; licznik != NULL; licznik = licznik->next){
            printf("%d : %f\n", licznik->idx, licznik->val);
        }
}

int main(){
    Tablica* t = nowaTablica();
    dodaj(&t, 2, 6.0);
    dodaj(&t, -3, 5.0);
    indeks(t, -1);

    show(t);

    return 0;
}
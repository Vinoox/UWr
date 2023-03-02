/*
* Maciej Styś
* lista1: zad2
* gcc zad2.c
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Ulamek{
    int num;
    int denom;
}Ulamek;

int nwd(int a, int b){
    if(b != 0) return nwd(b, a%b);

    return a;
}

void skroc(Ulamek* u){
    int n = nwd(u->num, u->denom);
    u->num /= n;
    u->denom /= n;
}

Ulamek* nowy_ulamek(int num, int denom){
    Ulamek* ulamek = (Ulamek*)malloc(sizeof(Ulamek));
    ulamek->num = num;
    ulamek->denom = denom;

    return ulamek;
}

void show(Ulamek* u){
    printf("%f\n", (float)u->num/u->denom);
}

Ulamek* dodawanie1(Ulamek* u1, Ulamek* u2){
    Ulamek* wynik = (Ulamek*)malloc(sizeof(Ulamek));

    wynik->num = (u1->num * u2->denom) + (u2->num * u1->denom);
    wynik->denom = u1->denom * u2->denom;

    skroc(wynik);
    return wynik;
}

Ulamek* odejmowanie1(Ulamek* u1, Ulamek* u2){
    Ulamek* wynik = (Ulamek*)malloc(sizeof(Ulamek));

    wynik->num = (u1->num * u2->denom) - (u2->num * u1->denom);
    wynik->denom = u1->denom * u2->denom;

    skroc(wynik);
    return wynik;
}

Ulamek* mnozenie1(Ulamek* u1, Ulamek* u2){
    Ulamek* wynik = (Ulamek*)malloc(sizeof(Ulamek));

    wynik->num = u1->num * u2->num;
    wynik->denom = u1->denom * u2->denom;

    skroc(wynik);
    return wynik;
}

Ulamek* dzielenie1(Ulamek* u1, Ulamek* u2){
    Ulamek* wynik = (Ulamek*)malloc(sizeof(Ulamek));

    wynik->num = u1->num * u2->denom;
    wynik->denom = u1->denom * u2->num;

    skroc(wynik);
    return wynik;
}

void dodawanie2(Ulamek* u1, Ulamek* u2){
    u2->num = (u2->num * u1->denom) + (u1->num * u2->denom);
    u2->denom *= u1->denom;
}

void odejmowanie2(Ulamek* u1, Ulamek* u2){
    u2->num = (u1->num * u2->denom) - (u2->num * u1->denom);
    u2->denom *= u1->denom;
    skroc(u2);
}

void mnozenie2(Ulamek* u1, Ulamek* u2){
    u2->num *= u1->num;
    u2->denom *= u1->denom;
    skroc(u2);
}

void dzielenie2(Ulamek* u1, Ulamek* u2){
    int num = u2->num;
    u2->num = u2->denom * u1->num;
    u2->denom = num * u1->denom;
    skroc(u2);
}
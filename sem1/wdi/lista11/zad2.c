#include <stdio.h>
#include <stdlib.h>

typedef struct node *pnode;

typedef struct node{
    int val;
    pnode left;
    pnode right;
}snode;

pnode utworz(int wart){
    pnode pom;
    pom = (pnode) malloc(sizeof(snode));
    pom->left = NULL;
    pom->right = NULL;
    pom->val = wart;
    return pom;
}

void dodaj(pnode wezel, int wart){
    if(wart < wezel->val){
        if(wezel->left == NULL){
            wezel->left = utworz(wart);
        }
        else{
            dodaj(wezel->left, wart);
        }
    }
    else{
        if(wezel->right == NULL){
            wezel->right = utworz(wart);
        }
        else{
            dodaj(wezel->right, wart);
        }
    }
}

int zlicz(pnode wezel){ //zad2
    int licznik = 1;
    if(wezel->left != NULL){
        licznik += zlicz(wezel->left);
    }
    if(wezel->right != NULL){
        licznik += zlicz(wezel->right);
    }

    return licznik;
}

int wysokosc(pnode wezel){ //zad3
    if(wezel->left == NULL && wezel->right == NULL){
        return 1;
    }
    else{
        if(wezel->left == NULL){
            return 1 + wysokosc(wezel->right);
        }
        else if(wezel->right == NULL){
            return 1 + wysokosc(wezel->left);
        }
        else{
            return 1 + (wysokosc(wezel->left) > wysokosc(wezel->right) ? wysokosc(wezel->left) : wysokosc(wezel->right));
        }
    }
}

void wypisz(pnode wezel){ //zad4
    if(wezel->left != NULL){
        wypisz(wezel->left);
    }

    if(wezel->val > 0){
        printf("%d ", wezel->val);
    }

    if(wezel->right != NULL){
        wypisz(wezel->right);
    }
}

void polacz(pnode wezel1, pnode wezel2){ //zad6
    if(wezel2->left == NULL){
        wezel2->left = wezel1;
    }
    else{
        while(wezel2->left->left != NULL){
            wezel2 = wezel2->left;
        }
        wezel2->left->left = wezel1;
    }
}

void wstawBez(pnode wezel, int wart){ //zad7
    pnode nowy = utworz(wart);
    while(wezel->right != nowy && wezel->left != nowy){
        if(wart < wezel->val){
            if(wezel->left == NULL){
                wezel->left = nowy;
            }
            else{
                wezel = wezel->left;
            }
        }
        else{
            if(wezel->right == NULL){
                wezel->right = nowy;
            }
            else{
                wezel = wezel->right;
            }
        }
    }
}

void zamien(pnode wezel, pnode wezelZamien, pnode poprzedni){ //zad8
    if(wezel->left == wezelZamien){
        pnode pom = wezel->left->right;
        if(poprzedni != NULL){
            poprzedni->left = wezel->left;
        }
        wezel->left->right = wezel;
        wezel->left = pom;
    }
    else{
        if(wezel->left != NULL){
            zamien(wezel->left, wezelZamien, wezel);
        }
        if(wezel->right != NULL){
            zamien(wezel->right, wezelZamien, wezel);
        }
    }
}

int main(){

    pnode drzewo = utworz(10);
    wstawBez(drzewo, 3);
    wstawBez(drzewo, -1);
    wstawBez(drzewo, 7);
    wstawBez(drzewo, -5);
    wstawBez(drzewo, 4);
    wstawBez(drzewo, 5);
    wstawBez(drzewo, 7);
    wstawBez(drzewo, -12);
    wstawBez(drzewo, -10);
    wstawBez(drzewo, 9);
    wstawBez(drzewo, 11);
    wstawBez(drzewo, 14);
    wstawBez(drzewo, 13);
    wstawBez(drzewo, 15);

    pnode wezelZamien = drzewo->left->left->left;

    zamien(drzewo, wezelZamien, NULL);

    printf("\n%d\n", zlicz(drzewo));
    printf("%d\n", wysokosc(drzewo));
    wypisz(drzewo);

    return 0;
}
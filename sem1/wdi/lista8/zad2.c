#include<stdio.h>

int pola[4];
int n = 4;

int isfree(int a, int b){  //a - kolumna; b - wiersz
    for(int i = 0; i < a; i++){
        if(pola[i] == b || pola[i] + i == a + b || i - pola[i] == a - b){
            return 0;
        }
    }
    return 1;
}

void pokaz(){
    char tab[4][4];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            tab[i][j] = 'o';
        }
    }

    for(int i = 0; i < n; i++){
        if(pola[i] == 0){
            tab[i][pola[i]] = 'x';
        }
    }

    printf("\n");
    for(int i = 0; i < n; i++){
        printf("\n");
        for(int j = 0; j < n; j++){
           printf("%c", tab[i][j]);
        }
    }
}

int hetman(){
    int licznik = 0;
    int hetmany = 1;
    int k = 1;
    pola[0] = 0;
    while(k < n && k >=0){
        pokaz();
        // do{
        //     pola[k] ++;
        //     // hetmany++;
        // }while(pola[k] < n && !isfree(k, pola[k]));

        while(pola[k] < n && !isfree(k, pola[k]) && hetmany != 4){
            pola[k]++;
            pokaz();
        }
        if(pola[k] < n){
            k++;
            licznik++;
            pokaz();
        }
        else{
            pola[k] = -1;
            k--;
        }
    }
    return licznik;
}


int main(){
    for(int i = 0; i < n; i++){  //wypelnienie tablicy -1 (brak hetmanow)
        pola[i] = -1;
    }
    
    printf("%d", hetman());

    return 0;
}
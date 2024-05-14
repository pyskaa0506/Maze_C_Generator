#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "labirynt_generacja.h"
#include "lab_na_graf.h"
#include "czyszczenie.h"
#include "znajdywanie_drogi.h"
#include "wyswietlanie_labiryntu.h"


int main() {

    srand(time(NULL));
    printf("Podaj rozmiar labiryntu: "); fflush(stdout);
    int rozmiar;
    do {
        scanf("%d", &rozmiar);
        if (rozmiar < 2) {
            printf("Rozmiar labiryntu musi byc wiekszy od 1.\n"); fflush(stdout);
        }
        else if (rozmiar > 19) {
            printf("Zalecam aby rozmiar byl mniejszy niz 20: wieksze labirynty traca na czytelnosci. \n"); fflush(stdout);
        }
    } while (rozmiar < 2 || rozmiar > 19);

    printf("Wyswietlac numeracje wierzcholkow w labiryncie? (t/n) \n");
    char znak;
    do {
        scanf(" %c", &znak);
        if (znak == 't' || znak == 'n') {
            printf("\n"); fflush(stdout);
            break;
        } else {
            printf("Niepoprawny znak. Wpisz t lub n.\n"); fflush(stdout);
        }
    } while (znak != 't' || znak != 'n');



    //inicjalizacja labiryntu
    kratka **labirynt = malloc(rozmiar * sizeof (kratka *));
    if (labirynt == NULL) {
        printf("Nie udalo sie zalokowac pamieci.\n"); fflush(stdout);
        return 1;
    }
    zainicjuj_labirynt(&labirynt, rozmiar);

    // tworzenie stosu z ruchami i wypelnienie go -1
    int rozmiar2 = rozmiar * rozmiar;
    int **stos_z_ruchami = (int **)malloc(rozmiar2 * sizeof(int *));
    if (stos_z_ruchami == NULL) {
        printf("Nie udalo sie zalokowac pamieci.\n"); fflush(stdout);
        return 1;
    }
    for (int i = 0; i < rozmiar2; i++) {
        stos_z_ruchami[i] = (int *)malloc(2 * sizeof(int));
        if (stos_z_ruchami[i] == NULL) {
            printf("Nie udalo sie zalokowac pamieci.\n"); fflush(stdout);
            return 1;
        }
    }
    for (int i = 0; i < rozmiar2; i++) {
        stos_z_ruchami[i][0] = -1;
        stos_z_ruchami[i][1] = -1;
    }

    int ypocz = 0;
    int xpocz = 0;
    int xkon = rozmiar - 1;
    losowanie_x(&xpocz, rozmiar);
    losowanie_x(&xkon, rozmiar);

    generowanie_labiryntu(&labirynt, rozmiar, stos_z_ruchami, ypocz, xpocz);

    //inicjalizacja dynamicznej tablicy typu int 2n+1 x 2n+1
    int **tablica = malloc((2 * rozmiar + 1) * sizeof (int *));
    if (tablica == NULL) {
        printf("Nie udalo sie zalokowac pamieci.\n"); fflush(stdout);
        return 1;
    }
    for (int i = 0; i < 2 * rozmiar + 1; i++) {
        tablica[i] = malloc((2 * rozmiar + 1) * sizeof(int));
        if (tablica[i] == NULL) {
            printf("Nie udalo sie zalokowac pamieci.\n"); fflush(stdout);
            return 1;
        }
    }
    wyswietlanie_labiryntu(&labirynt, rozmiar, xpocz, xkon, tablica, znak);


    //tworzenie listy sąsiedztwa na podstawie labiryntu
    NodeListy **lista_sasiedztwa = malloc(rozmiar * sizeof (NodeListy *));
    if (lista_sasiedztwa == NULL) {
        printf("Nie udalo sie zalokowac pamieci.\n"); fflush(stdout);
        return 1;
    }
    przepisywanieLabnaGraf(rozmiar,tablica, &lista_sasiedztwa);

    NodeListy *wierzcholek_poczatkowy = &lista_sasiedztwa[0][xpocz];
    NodeListy *wierzcholek_koncowy = &lista_sasiedztwa[rozmiar - 1][xkon];

    int (*droga)[2] = malloc(rozmiar * rozmiar * sizeof(int[2]));

    for (int i = 0; i < rozmiar * rozmiar; i++) {
        droga[i][0] = -1;
        droga[i][1] = -1;
    }

    znajdywanie_najkrotszej_drogi(rozmiar, wierzcholek_poczatkowy, wierzcholek_koncowy, droga);

    wyswietlanie_drogi(rozmiar, xpocz, xkon, tablica, droga, znak);

//zwalnianie pamieci na koniec programu
//    zwolnij_labirynt(&labirynt, rozmiar);
//
//    for (int i = 0; i < rozmiar2; i++) {
//        free(stos_z_ruchami[i]);
//    }
//    free(stos_z_ruchami);
//
//    for (int i = 0; i < 2 * rozmiar + 1; i++) {
//        free(tablica[i]);
//    }
//    free(tablica);
//
//    for (int i = 0; i < rozmiar; i++) {
//        free(lista_sasiedztwa[i]);
//    }
//    free(lista_sasiedztwa);
//
//    free(droga);
    return 0;
}



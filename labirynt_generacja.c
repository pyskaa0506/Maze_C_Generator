#include "labirynt_generacja.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"

void zainicjuj_labirynt(kratka ***labirynt, int rozmiar){
    int i;
    int j;
    *labirynt = malloc(rozmiar * sizeof (kratka *));

    for (i = 0; i < rozmiar; i++) {
        (*labirynt)[i] = malloc(rozmiar * sizeof(kratka));
        for (j = 0; j < rozmiar; j++){
            (*labirynt)[i][j].gora = false;
            (*labirynt)[i][j].prawo = false;
            (*labirynt)[i][j].dol = false;
            (*labirynt)[i][j].lewo = false;
            (*labirynt)[i][j].odwiedzona = false;
        }
    }
}

int lab_przebijanie_scian(kratka ***labirynt, int rozmiar, int **stos_z_ruchami, int *kordyx, int *kordyy) {


    bool dostepne_kierunki[4] = {false}; // Tablica dostępnych kierunków
    int ilosc_dostepnych = 0; // Liczba dostępnych kierunków
    bool udane_los = false;

    // Sprawdzenie dostępności kierunków
    if (*kordyy > 0 && !(*labirynt)[*kordyy - 1][*kordyx].odwiedzona) {
        dostepne_kierunki[0] = true; // Góra
        ilosc_dostepnych++;
    }
    if (*kordyx < rozmiar - 1 && !(*labirynt)[*kordyy][*kordyx + 1].odwiedzona) {
        dostepne_kierunki[1] = true; // Prawo
        ilosc_dostepnych++;
    }
    if (*kordyy < rozmiar - 1 && !(*labirynt)[*kordyy + 1][*kordyx].odwiedzona) {
        dostepne_kierunki[2] = true; // Dół
        ilosc_dostepnych++;
    }
    if (*kordyx > 0 && !(*labirynt)[*kordyy][*kordyx - 1].odwiedzona) {
        dostepne_kierunki[3] = true; // Lewo
        ilosc_dostepnych++;
    }

    // Losowanie spośród dostępnych kierunków
    while (ilosc_dostepnych > 0 && !udane_los) {
        int kierunek = rand() % 4;
        if (dostepne_kierunki[kierunek]) {
            if (kierunek == 0) {
                (*labirynt)[*kordyy][*kordyx].gora = true;
                (*labirynt)[(*kordyy) - 1][*kordyx].dol = true;
                (*kordyy)--;
            } else if (kierunek == 1) {
                (*labirynt)[*kordyy][*kordyx].prawo = true;
                (*labirynt)[*kordyy][(*kordyx) + 1].lewo = true;
                (*kordyx)++;
            } else if (kierunek == 2) {
                (*labirynt)[*kordyy][*kordyx].dol = true;
                (*labirynt)[(*kordyy) + 1][*kordyx].gora = true;
                (*kordyy)++;
            } else if (kierunek == 3) {
                (*labirynt)[*kordyy][*kordyx].lewo = true;
                (*labirynt)[*kordyy][(*kordyx) - 1].prawo = true;
                (*kordyx)--;
            }
            //printf("Wybrano kierunek %d\n", kierunek); fflush(stdout);
            (*labirynt)[*kordyy][*kordyx].odwiedzona = true;
            push_stack(stos_z_ruchami, *kordyx, *kordyy, rozmiar * rozmiar);
            udane_los = true;
        } else {
            //    printf("Kierunek %d nie jest dostepny, Losowanie ponowne... \n", kierunek); fflush(stdout);
        }
    }

    // Jeśli nie ma dostępnych kierunków
    if (!udane_los) {
        //printf("Nie ma dostepnych kierunkow.\n"); fflush(stdout);
        return -1; // Zwracamy wartość ujemną
    }

    return 1;
}
void generowanie_labiryntu(kratka ***labirynt,int rozmiar, int **stos_z_ruchami, int ypocz, int xpocz){

    int kordyy = ypocz;
    int kordyx = xpocz;
    (*labirynt)[kordyy][kordyx].odwiedzona = true;
    push_stack(stos_z_ruchami, kordyx, kordyy, rozmiar*rozmiar);
    while( top_stack(stos_z_ruchami, rozmiar*rozmiar) != -1){
        while(lab_przebijanie_scian(labirynt, rozmiar, stos_z_ruchami, &kordyx, &kordyy) == -1){
            pop_stack(stos_z_ruchami, rozmiar*rozmiar);
            int i_staku = top_stack(stos_z_ruchami, rozmiar*rozmiar);
            if (i_staku == -1){
                return;
            }
            kordyy = stos_z_ruchami[i_staku][0];
            kordyx = stos_z_ruchami[i_staku][1];
        }
    }
    if (kordyx == xpocz && kordyy == ypocz){
        return;
    }
}

void wyswietlanie_labiryntu(kratka ***labirynt, int rozmiar, int xpocz, int xkon, int **tablica_wys_lab, char znak) {
// 0, 1 to jest sciana (pusta lub niepusta),
// 2 to jest sciana zewnetrzna,
// 3 to jest wierzcholek,
// 4 to jest wypelnienie (do debugowania)

    //wypelnienie tablicy wyswietlajacej labirynt liczba 4
    for (int i = 0; i < 2 * rozmiar + 1; i++) {
        for (int j = 0; j < 2 * rozmiar + 1; j++) {
            tablica_wys_lab[i][j] = 4;
        }
    }

    //wypelnienie scian tablicy dwojkami
    for (int i = 0; i < 2 * rozmiar + 1; i++) {
        tablica_wys_lab[i][0] = 2;
        tablica_wys_lab[i][2 * rozmiar] = 2;
        tablica_wys_lab[0][i] = 2;
        tablica_wys_lab[2 * rozmiar][i] = 2;
    }

    //ustawianie co 2 kratki od 0 do 2n+1 na 1
    for (int i = 0; i < 2 * rozmiar + 1; i+= 2) {
        for (int j = 0; j < 2 * rozmiar + 1; j+= 2) {
            tablica_wys_lab[i][j] = 2;
        }
    }

    //ustawianie kratki powyzej wierzcholka labiryntu wzgledem tego co jest w labiryncie
    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            if ((*labirynt)[i][j].gora == true) {
                tablica_wys_lab[i * 2][j * 2 + 1] = 0;
            }
            else   tablica_wys_lab[i * 2][j * 2 + 1] = 1;
            tablica_wys_lab[i * 2 + 1][j * 2 + 1] = 3;
        }
    }
    //ustawianie kratki po prawej stronie wierzcholka labiryntu wzgledem tego co jest w labiryncie
    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            if ((*labirynt)[i][j].prawo == true) {
                tablica_wys_lab[i * 2 + 1][j * 2 + 2] = 0;
            }
            else   tablica_wys_lab[i * 2 + 1][j * 2 + 2] = 1;
        }
    }
    //skorygowanie sciany gornej i prawej labiryntu by wylacznie skladaly sie z 2
    for (int i = 0; i < rozmiar; i++) {
        tablica_wys_lab[0][i * 2 + 1] = 2;
        tablica_wys_lab[i * 2 + 1][2 * rozmiar] = 2;
    }

    //losowe burzenie scian wewnetrznych labiryntu (z prawdopodobienstwem 1/10)
    for (int i = 0; i < 2 * rozmiar + 1; i++) {
        for (int j = 0; j < 2 * rozmiar + 1; j++) {
            if (tablica_wys_lab[i][j] == 1) {
                int los = rand() % 10;
                if (los == 1) {
                    tablica_wys_lab[i][j] = 0;
                }
            }
        }
    }

    //ustawianie sciany dla poczatku i konca na 0
    tablica_wys_lab[0][xpocz*2+1] = 0;
    tablica_wys_lab[2 * rozmiar][xkon*2+1] = 0;

    if (znak == 'n') {    //printowanie tablicy wyswietlajacej labirynt z ponumerowanymi wierzcholkami
        printf("Czytelny labirynt:\n");
        fflush(stdout);
        for (int i = 0; i < 2 * rozmiar + 1; i++) {
            for (int j = 0; j < 2 * rozmiar + 1; j++) {
                if (tablica_wys_lab[i][j] == 1 || tablica_wys_lab[i][j] == 2) {
                    //printf("%c ", 178);
                    printf(" # ");
                } else if (tablica_wys_lab[i][j] == 0 || tablica_wys_lab[i][j] == 3) {
                    //printf("%c ", 176);
                    printf(" %c ", 32);

                } else if (tablica_wys_lab[i][j] == 4) {
                    printf("w");
                }
            }
            printf("\n");
        }
        fflush(stdout);
    }
    if (znak == 't') {
        int ktory_wierzcholek = 0;
        //printowanie tablicy wyswietlajacej labirynt bez ponumerowanych wierzcholkow
        printf("\n Labirynt z zaznaczonymi numerami wierzcholkow:\n");
        fflush(stdout);
        for (int i = 0; i < 2 * rozmiar + 1; i++) {
            for (int j = 0; j < 2 * rozmiar + 1; j++) {
                if (tablica_wys_lab[i][j] == 1 || tablica_wys_lab[i][j] == 2) {
                    //printf("%c ", 178);
                    printf(" # ");
                } else if (tablica_wys_lab[i][j] == 0) {
                    //printf("%c ", 176);
                    printf(" %c ", 32);
                } else if (tablica_wys_lab[i][j] == 3) {
                    if (ktory_wierzcholek < 10) printf("00%d", ktory_wierzcholek);
                    else if (ktory_wierzcholek < 100) printf("0%d", ktory_wierzcholek);
                    else printf("%d", ktory_wierzcholek);
                    ktory_wierzcholek++;

                } else if (tablica_wys_lab[i][j] == 4) {
                    printf("w");
                }
            }
            printf("\n");
        }
        fflush(stdout);
    }

    //ustawianie sciany z powrotem dla poczatku i konca na 2
    tablica_wys_lab[0][xpocz*2+1] = 2;
    tablica_wys_lab[2 * rozmiar][xkon*2+1] = 2;

//    //printowanie zawartosci tablica_wys_lab w kolumna x wiersz
//    for (int i = 0; i < 2 * rozmiar + 1; i++) {
//        for (int j = 0; j < 2 * rozmiar + 1; j++) {
//            printf("%d ", tablica_wys_lab[i][j]);
//        }
//        printf("\n");fflush(stdout);
//    }




}
int losowanie_x(int *x, int rozmiar){
    *x = rand() % rozmiar;
    return *x;
}

void zwolnij_labirynt(kratka ***labirynt, int rozmiar) {
    for (int i = 0; i < rozmiar; i++) {
        free((*labirynt)[i]);
    }
    free(*labirynt);
    *labirynt = NULL;
}
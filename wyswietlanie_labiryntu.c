//
// Created by pyska on 07.01.2024.
//

#include "wyswietlanie_labiryntu.h"

void wyswietlanie_drogi(int rozmiar, int xpocz, int xkon, int **tablica, int droga[][2], char znak) {
    //uwzglednienie wierzcholkow poczatkowego i koncowego
    tablica[0][xpocz*2+1] = 0;
    tablica[2 * rozmiar][xkon*2+1] = 0;

    int i = 0;
    while(droga[i][0] != -1) {
        if (droga[i][1] == -1) break;
        tablica[droga[i][1]*2+1][droga[i][0]*2+1] = 5;
        i++;
    }

    if (znak == 't') {
        int ktory_wierzcholek = 0;
        //printowanie tablicy wyswietlajacej labirynt bez ponumerowanych wierzcholkow
        printf("\n Labirynt z zaznaczona sciezka:\n");
        fflush(stdout);
        for (int i = 0; i < 2 * rozmiar + 1; i++) {
            for (int j = 0; j < 2 * rozmiar + 1; j++) {
                if (tablica[i][j] == 1 || tablica[i][j] == 2) {
                    //printf("%c ", 178);
                    printf(" # ");
                } else if (tablica[i][j] == 0) {
                    //printf("%c ", 176);
                    printf(" %c ", 32);
                } else if (tablica[i][j] == 3) {
                    if (ktory_wierzcholek < 10) printf("00%d", ktory_wierzcholek);
                    else if (ktory_wierzcholek < 100) printf("0%d", ktory_wierzcholek);
                    else printf("%d", ktory_wierzcholek);
                    ktory_wierzcholek++;

                } else if (tablica[i][j] == 4) {
                    printf("w");
                } else if (tablica[i][j] == 5) {
                    printf(" X ");
                    ktory_wierzcholek++;
                }
            }
            printf("\n");
        }
        fflush(stdout);
    }
    else if (znak == 'n') {
        //printowanie tablicy wyswietlajacej labirynt bez ponumerowanych wierzcholkow
        printf("\n Labirynt z zaznaczona sciezka:\n");
        fflush(stdout);
        for (int i = 0; i < 2 * rozmiar + 1; i++) {
            for (int j = 0; j < 2 * rozmiar + 1; j++) {
                if (tablica[i][j] == 1 || tablica[i][j] == 2) {
                    //printf("%c ", 178);
                    printf(" # ");
                } else if (tablica[i][j] == 0) {
                    //printf("%c ", 176);
                    printf(" %c ", 32);
                } else if (tablica[i][j] == 3) {
                    printf("   ");
                } else if (tablica[i][j] == 4) {
                    printf("w");
                } else if (tablica[i][j] == 5) {
                    printf(" X ");
                }
            }
            printf("\n");
        }
        fflush(stdout);
    }
}

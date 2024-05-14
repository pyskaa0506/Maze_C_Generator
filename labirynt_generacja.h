#ifndef MAZEORGINAL_LABIRYNT_GENERACJA_H
#define MAZEORGINAL_LABIRYNT_GENERACJA_H

#include <stdbool.h>

typedef struct {
    bool odwiedzona;
    bool gora, prawo, dol, lewo;
    bool sciana;
} kratka;

void zainicjuj_labirynt(kratka ***labirynt, int rozmiar);
int lab_przebijanie_scian(kratka ***labirynt, int rozmiar, int **stos_z_ruchami, int *kordyx, int *kordyy);
void generowanie_labiryntu(kratka ***labirynt, int rozmiar, int **stos_z_ruchami, int ypocz, int xpocz);
void wyswietlanie_labiryntu(kratka ***labirynt, int rozmiar, int xpocz, int xkon, int **tablica_wys_lab, char znak);
int losowanie_x(int *x, int rozmiar);
void zwolnij_labirynt(kratka ***labirynt, int rozmiar);
void zwolnij_stos(int rozmiar, int **stos_z_ruchami);

#endif //MAZEORGINAL_LABIRYNT_GENERACJA_H

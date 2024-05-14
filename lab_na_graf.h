//
// Created by pyska on 30.12.2023.
//

#ifndef MAZEORGINAL_LAB_NA_GRAF_H
#define MAZEORGINAL_LAB_NA_GRAF_H
#include <stdbool.h>

//tworzenie listy sąsiedztwa na podstawie labiryntu
typedef struct NodeListy {
    int *kordynaty;
    int ile_polaczen;
    double waga;
    int *sasiedzi;
    double koszt_dojscia; // koszt poprzedniego sąsiada + waga
    bool czy_odwiedzony;
    struct NodeListy **sasiedzi_adresy;
} NodeListy;

void przepisywanieLabnaGraf(int rozmiar, int **tablica, NodeListy ***lista_sasiedztwa);

#endif //MAZEORGINAL_LAB_NA_GRAF_H

#include <stdio.h>
#include <stdlib.h>

#include "lab_na_graf.h"
void przepisywanieLabnaGraf(int rozmiar, int **tablica, NodeListy ***lista_sasiedztwa){
    *lista_sasiedztwa = malloc(rozmiar * sizeof (NodeListy *));
    //losowanie i przepisywanie wag w zakresie 0-10 z 2 miejscami po przecinku
    for (int i = 0; i < rozmiar; i++) {
        (*lista_sasiedztwa)[i] = malloc(rozmiar * sizeof(NodeListy));
        for (int j = 0; j < rozmiar; j++) {
            (*lista_sasiedztwa)[i][j].waga = (double) (rand() % 1000) / 100;
        }
    }
//sprawdzanie ile polaczen ma kazdy wierzcholek
    for (int wier = 0; wier < rozmiar; wier++) {
        for (int kol = 0; kol < rozmiar; kol++){
            int wierzcholek[2] = {2*wier + 1, 2*kol+1};
            int polaczenia = 0;

            if (tablica[wierzcholek[0]][wierzcholek[1] - 1] == 0) {
                polaczenia++;
            }
            if (tablica[wierzcholek[0] - 1][wierzcholek[1]] == 0) {
                polaczenia++;
            }
            if (tablica[wierzcholek[0]][wierzcholek[1] + 1] == 0) {
                polaczenia++;
            }
            if (tablica[wierzcholek[0] + 1][wierzcholek[1]] == 0) {
                polaczenia++;
            }
            (*lista_sasiedztwa)[wier][kol].ile_polaczen = polaczenia;
        }
    }
//    //wyprintowanie ilosci polaczen dla kazdego wierzcholka
//    for (int wier = 0; wier < rozmiar; wier++) {
//        for (int kol = 0; kol < rozmiar; kol++){
//            printf("Wierzcholek %d : %d \n", (wier)*rozmiar + kol, (*lista_sasiedztwa)[wier][kol].ile_polaczen);
//        }
//    }

    //stworzenie tablicy o wielkosci ile_polaczen dla kazdego wierzcholka
    for (int wier = 0; wier < rozmiar; wier++) {
        for (int kol = 0; kol < rozmiar; kol++){
            (*lista_sasiedztwa)[wier][kol].sasiedzi = malloc((*lista_sasiedztwa)[wier][kol].ile_polaczen * sizeof(int));
            (*lista_sasiedztwa)[wier][kol].sasiedzi_adresy = malloc((*lista_sasiedztwa)[wier][kol].ile_polaczen * sizeof(int));
        }
    }


    //przypisanie adresow sasiadow do tablicy sasiedzi
    for (int wier = 0; wier < rozmiar; wier++) {
        for (int kol = 0; kol < rozmiar; kol++){
            int wierzcholek[2] = {2*wier + 1, 2*kol+1};
            int polaczenia = 0;

            if (tablica[wierzcholek[0]][wierzcholek[1] - 1] == 0) {
                (*lista_sasiedztwa)[wier][kol].sasiedzi[polaczenia] = (wier)*rozmiar + kol - 1;
                (*lista_sasiedztwa)[wier][kol].sasiedzi_adresy[polaczenia] = &((*lista_sasiedztwa)[wier][kol - 1]);
                //printf("%p %p\n", (*lista_sasiedztwa)[wier][kol].sasiedzi_adresy[polaczenia], &((*lista_sasiedztwa)[wier][kol - 1])); fflush(stdout);
                polaczenia++;
            }
            if (tablica[wierzcholek[0] - 1][wierzcholek[1]] == 0) {
                (*lista_sasiedztwa)[wier][kol].sasiedzi[polaczenia] = (wier-1)*rozmiar + kol;
                (*lista_sasiedztwa)[wier][kol].sasiedzi_adresy[polaczenia] = &((*lista_sasiedztwa)[wier-1][kol]);
                polaczenia++;
            }
            if (tablica[wierzcholek[0]][wierzcholek[1] + 1] == 0) {
                (*lista_sasiedztwa)[wier][kol].sasiedzi[polaczenia] = (wier)*rozmiar + kol + 1;
                (*lista_sasiedztwa)[wier][kol].sasiedzi_adresy[polaczenia] = &((*lista_sasiedztwa)[wier][kol + 1]);
                polaczenia++;
            }
            if (tablica[wierzcholek[0] + 1][wierzcholek[1]] == 0) {
                (*lista_sasiedztwa)[wier][kol].sasiedzi[polaczenia] = (wier+1)*rozmiar + kol;
                (*lista_sasiedztwa)[wier][kol].sasiedzi_adresy[polaczenia] = &((*lista_sasiedztwa)[wier+1][kol]);
                polaczenia++;
            }
        }
    }
    //wyswietlanie listy sasiedztwa
    printf("\nLista sasiedztwa:\n");
    for (int wier = 0; wier < rozmiar; wier++) {
        for (int kol = 0; kol < rozmiar; kol++){
            printf("Wierzcholek %d : ", (wier)*rozmiar + kol);
            for (int pol = 0; pol < (*lista_sasiedztwa)[wier][kol].ile_polaczen; pol++){
                printf("%d ", (*lista_sasiedztwa)[wier][kol].sasiedzi[pol]); fflush(stdout);
            //  printf("waga: %f ", (*lista_sasiedztwa)[wier][kol].sasiedzi_adresy[pol]->waga); fflush(stdout);
            }
            printf("\n");
        }
    }



    //przypisanie kordynatow do kazdego Node
    for (int wier = 0; wier < rozmiar; wier++) {
        for (int kol = 0; kol < rozmiar; kol++){
            (*lista_sasiedztwa)[wier][kol].kordynaty = malloc(3 * sizeof(int));
            (*lista_sasiedztwa)[wier][kol].kordynaty[0] = wier;
            (*lista_sasiedztwa)[wier][kol].kordynaty[1] = kol;
            (*lista_sasiedztwa)[wier][kol].kordynaty[2] = (wier)*rozmiar + kol;

        }
    }

    //ustawienie wierzcholkow na nieodwiedzone
    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {

            (*lista_sasiedztwa)[i][j].czy_odwiedzony = false;
        }
    }

//    //wyprintowanie koordynatow sasiadow za pomoca pointerow
//    // array_of_nodes[0][0].sasiedzi_adresy[0]->kordynaty[0]
//    for (int wier = 0; wier < rozmiar; wier++) {
//        for (int kol = 0; kol < rozmiar; kol++){
//            printf("Wierzcholek %d : ", (wier)*rozmiar + kol);
//            for (int pol = 0; pol < (*lista_sasiedztwa)[wier][kol].ile_polaczen; pol++){
//                printf("%d %d ", (*lista_sasiedztwa)[wier][kol].sasiedzi_adresy[pol]->kordynaty[0], (*lista_sasiedztwa)[wier][kol].sasiedzi_adresy[pol]->kordynaty[1]); fflush(stdout);
//            }
//            printf("\n");
//        }
//    }

}
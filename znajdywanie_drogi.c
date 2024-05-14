//
// Created by pyska on 04.01.2024.
//

#include "znajdywanie_drogi.h"
void znajdywanie_najkrotszej_drogi(int rozmiar, NodeListy *wierzcholek_poczatkowy, NodeListy *wierzcholek_koncowy, int droga[][2]) {

    // Ustawienie kosztu dojścia wierzchołka początkowego na jego wagę
    wierzcholek_poczatkowy->koszt_dojscia = wierzcholek_poczatkowy->waga;
    wierzcholek_poczatkowy->czy_odwiedzony = true;

    NodeListy **lista_potencjalnych_sasiadow = malloc(rozmiar * sizeof(NodeListy *));
    int ile_potencjalnych_sasiadow = 0;

    // Sprawdzenie poprawności alokacji pamięci
    if (lista_potencjalnych_sasiadow == NULL) {
        printf("Nie udalo sie zalokowac pamieci dla listy potencjalnych sasiadow.\n");
        return;
    }

    // Inicjalizacja listy potencjalnych sąsiadów
    for (int i = 0; i < wierzcholek_poczatkowy->ile_polaczen; i++) {
        NodeListy *sasiad = wierzcholek_poczatkowy->sasiedzi_adresy[i];
        lista_potencjalnych_sasiadow[ile_potencjalnych_sasiadow++] = sasiad;
        sasiad->koszt_dojscia = wierzcholek_poczatkowy->koszt_dojscia + sasiad->waga;
    }

    while (!wierzcholek_koncowy->czy_odwiedzony && ile_potencjalnych_sasiadow > 0) {
        // Znajdowanie najtańszego sąsiada
        NodeListy *najtanszy_sasiad = lista_potencjalnych_sasiadow[0];
        int najtanszy_index = 0;

        for (int i = 1; i < ile_potencjalnych_sasiadow; i++) {
            if (lista_potencjalnych_sasiadow[i]->koszt_dojscia < najtanszy_sasiad->koszt_dojscia) {
                najtanszy_sasiad = lista_potencjalnych_sasiadow[i];
                najtanszy_index = i;
            }
        }

        // Oznaczenie najtańszego sąsiada jako odwiedzonego i usunięcie z listy potencjalnych sąsiadów
        najtanszy_sasiad->czy_odwiedzony = true;
        for (int i = najtanszy_index; i < ile_potencjalnych_sasiadow - 1; i++) {
            lista_potencjalnych_sasiadow[i] = lista_potencjalnych_sasiadow[i + 1];
        }
        ile_potencjalnych_sasiadow--;

        // Sprawdzenie sąsiadów najtańszego węzła
        for (int i = 0; i < najtanszy_sasiad->ile_polaczen; i++) {
            NodeListy *sprawdzany_sasiad = najtanszy_sasiad->sasiedzi_adresy[i];

            if (!sprawdzany_sasiad->czy_odwiedzony) {
                bool czy_jest_juz_w_liscie = false;

                for (int j = 0; j < ile_potencjalnych_sasiadow; j++) {
                    if (sprawdzany_sasiad == lista_potencjalnych_sasiadow[j]) {
                        czy_jest_juz_w_liscie = true;
                        if (sprawdzany_sasiad->koszt_dojscia >
                            najtanszy_sasiad->koszt_dojscia + sprawdzany_sasiad->waga) {
                            sprawdzany_sasiad->koszt_dojscia =
                                    najtanszy_sasiad->koszt_dojscia + sprawdzany_sasiad->waga;
                        }
                        break;
                    }
                }

                if (!czy_jest_juz_w_liscie) {
                    lista_potencjalnych_sasiadow[ile_potencjalnych_sasiadow++] = sprawdzany_sasiad;
                    sprawdzany_sasiad->koszt_dojscia = najtanszy_sasiad->koszt_dojscia + sprawdzany_sasiad->waga;
                }
            }
        }
    }

    for(int i = 0; i < rozmiar * rozmiar; i++){
        droga[i][0] = -1;
        droga[i][1] = -1;
    }

    int numer_tab = 0;
    NodeListy* aktualny_wierzcholek = wierzcholek_koncowy;
//    printf("%d %d\n", aktualny_wierzcholek->kordynaty[1], aktualny_wierzcholek->kordynaty[0]);
    while(aktualny_wierzcholek != wierzcholek_poczatkowy) {
        NodeListy* najblizszy_sasiad = aktualny_wierzcholek->sasiedzi_adresy[0];
        for(int i = 1; i < aktualny_wierzcholek->ile_polaczen; i++) {
            if(aktualny_wierzcholek->sasiedzi_adresy[i]->koszt_dojscia < najblizszy_sasiad->koszt_dojscia) {
                najblizszy_sasiad = aktualny_wierzcholek->sasiedzi_adresy[i];
            }
        }
        aktualny_wierzcholek = najblizszy_sasiad;

//        printf("%d %d\n", aktualny_wierzcholek->kordynaty[1], aktualny_wierzcholek->kordynaty[0]);
        //dodanie do tablicy z droga po kolei wierzcholkow
        droga[numer_tab+1][0] = aktualny_wierzcholek->kordynaty[1];
        droga[numer_tab+1][1] = aktualny_wierzcholek->kordynaty[0];
        numer_tab++;
    }
    droga[0][0] = wierzcholek_koncowy->kordynaty[1];
    droga[0][1] = wierzcholek_koncowy->kordynaty[0];

    //zamiana wspolrzednych na id
    int dlugosc_drogi = numer_tab+1;
    int droga_z_id[dlugosc_drogi];
    for(int i = 0; i < dlugosc_drogi; i++){
        if (droga[i][0] != -1){
            droga_z_id[i] = droga[i][1] * rozmiar + droga[i][0];
        }
    }

    //wyswietlenie drogi i wypisanie jej wagi
    printf("\n");
    printf("Droga o najmniejszej wadze: ");
    for(int i = dlugosc_drogi - 1; i >= 0; i--){
        printf("%d ", droga_z_id[i]);
    }
    printf("\n");
    printf("Waga drogi: %f\n", wierzcholek_koncowy->koszt_dojscia);



    free(lista_potencjalnych_sasiadow); // Zwolnienie zaalokowanej pamięci dla listy potencjalnych sąsiadów
}
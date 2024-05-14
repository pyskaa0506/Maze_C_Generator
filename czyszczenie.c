
#include "czyszczenie.h"


void zwolnij_liste(NodeListy **lista_sasiedztwa, int rozmiar) {
    for (int i = 0; i < rozmiar; i++) {
        free(lista_sasiedztwa[i]);
    }
    free(lista_sasiedztwa);
}

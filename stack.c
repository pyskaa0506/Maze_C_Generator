#include "stack.h"
#include <stdio.h>

int push_stack(int **stos_z_ruchami, int x, int y, int rozmiar) {
    int i = 0;
    while (i < rozmiar && stos_z_ruchami[i][0] != -1 && stos_z_ruchami[i][1] != -1) {
        i++;
    }
    if (i >= rozmiar) {
        //    printf("Stos jest pelny\n");
        return -1; // Stos jest pełny jeśli -1
    }
    stos_z_ruchami[i][0] = y;
    stos_z_ruchami[i][1] = x;
    return 0;
}

int pop_stack(int **stos_z_ruchami, int rozmiar) {
    int i = 0;
    while (i < rozmiar && stos_z_ruchami[i][0] != -1 && stos_z_ruchami[i][1] != -1) {
        i++;
    }
    if (i == 0) {
        //    printf("Stos jest pusty\n");
        return -1; // Stak jest pusty jeśli -1
    } else {
        stos_z_ruchami[i - 1][0] = -1;
        stos_z_ruchami[i - 1][1] = -1;
        return 0;
    }
}

int top_stack(int **stos_z_ruchami, int rozmiar) {
    int i = 0;
    while (i < rozmiar && stos_z_ruchami[i][0] != -1 && stos_z_ruchami[i][1] != -1) {
        i++;
    }
    if (i == 0) {
        //    printf("Stos jest pusty\n");
        return -1; // Stak jest pusty jeśli -1
    } else {
        //    printf("Ostatni element stosu to: %d %d\n", stos_z_ruchami[i - 1][0], stos_z_ruchami[i - 1][1]);
        return i - 1;
    }
}

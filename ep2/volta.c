#include "volta.h"

char volta_atual_atualiza () {
    int i, j;
    char cond = 1;

    while (cond && volta_atual_barreira < ciclista_n*2) {
        i = (volta_atual_barreira < ciclista_n);
        j = (volta_atual_barreira - i*ciclista_n);

        if (!ciclista[i][j].fim && ciclista[i][j].volta < volta_atual)
            cond = 0;

        volta_atual_barreira += cond;
    }

    if (volta_atual_barreira == ciclista_n*2) {
        volta_atual++;
        volta_atual_barreira = 0;
        return 1;
    }
    return 0;
}

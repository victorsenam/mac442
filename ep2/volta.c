#include "volta.h"

char volta_atual_atualiza () {
    int i;
    char cond = 1;

    ciclista_atual_barreira--;
    while (cond) {
        ciclista_aual_barreira++;
        i = (volta_atual_barreira < ciclista_n);
        j = (volta_atual_barreira - ciclista_n);

        if (!ciclista[i][j].fim && ciclista[i][j].volta < volta_atual)
            cond = 0;
    }

    if (volta_atual_barreira == ciclista_n*2) {
        volta_atual++;
        volta_atual_barreira = 0;
        return 1;
    }
    return 0;
}

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ciclista.h"
#include "pista.h"
#include "sorteio.h"
#include "debug.h"

int main (int argc, char * argv[]) {
    int i, j;

    /* lendo parâmetros da linha de comando */
    if (argc < 4) {
        fprintf(stderr, "Erro Fatal: Parâmetros insuficientes.\n");
        return 1;
    }

    // obrigatórios
    sscanf(argv[1], "%d", &pista_tamanho);
    sscanf(argv[2], "%d", &ciclista_n);
    sscanf(argv[3], " %c", &sorteio_tipo); // v (variado) ou u (uniforme)

    if (pista_tamanho <= 2*ciclista_n) {
        fprintf(stderr, "Erro Fatal: Por favor, escolha uma pista suficientemente grande para a quantidade de ciclistas.\n");
        return 2;
    }

    // opcionais
    debug_ativado = 0;
    for (i = 4; i < argc; i++) {
        // para acionar o debug (print verboso), basta inserir a flag opcional -d no final da lista de argumentos
        debug_ativado |= (argv[i][0] == '-' && argv[i][1] == 'd' && !argv[i][2]);
    }

    /* inicializando ciclistas */
    for (i = 0; i < 2; i++) {
        ciclista[i] = (ciclista_obj*) malloc(sizeof(ciclista_obj) * ciclista_n);

        for (j = 0; j < ciclista_n; j++) {
            ciclista[i][j].id = (!!i)*ciclista_n + j;
            ciclista[i][j].time = i;

            ciclista[i][j].ini = 0;
            ciclista[i][j].round = 0;
            ciclista[i][j].posicao = 0 + (!!i)*pista_tamanho/2;

            ciclista[i][j].ultima_velocidade = 1;
            ciclista[i][j].velocidade = 0;

            // TODO Thread
        }
    }
}

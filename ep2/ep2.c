#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ciclista.h"
#include "volta.h"
#include "pista.h"
#include "debug.h"

int main (int argc, char * argv[]) {
    int i, j;
    /* settings */
    srand(time(NULL)); rand(); rand();
    debug_mutex_ativado = 0;
    debug_ciclista_ativado = 0;

    /* lendo parâmetros da linha de comando */
    if (argc < 4) {
        fprintf(stderr, "Erro Fatal: Parâmetros insuficientes.\n");
        return 1;
    }

    // obrigatórios
    sscanf(argv[1], "%d", &pista_tamanho);
    sscanf(argv[2], "%d", &ciclista_n);
    sscanf(argv[3], " %c", &ciclista_tipo); // v (variado) ou u (uniforme)
    ciclista_tipo = (ciclista_tipo == 'v');

    if (pista_tamanho <= 2*ciclista_n) {
        // se não houver mais metros de pista do que ciclistas, deadlocks podem ocorrer enquanto os ciclistas tentam atualizar o vetor pista. Basta que todos os ciclistas tranquem o mutex da posição atual antes de trancar o da seguinte, todas as posições estarão trancadas e ninguém conseguirá atualizar o vetor.
        fprintf(stderr, "Erro Fatal: Escolha uma pista com tamanho em metros maior do que a quantidade de ciclistas, caso contrário, deadlocks são inevitáveis.\n");
        return 2;
    }

    // opcionais
    debug_ativado = 0;
    for (i = 4; i < argc; i++) {
        // para acionar o debug (print verboso), basta inserir a flag opcional -d no final da lista de argumentos
        debug_ativado |= (argv[i][0] == '-' && argv[i][1] == 'd' && !argv[i][2]);
    }

    /* inicializando pista */
    pista = (pista_obj *) malloc(sizeof(pista_obj) * 2 * pista_tamanho);
    for (i = 0; i < 2*pista_tamanho; i++) {
        pista_init(&(pista[i]));
    }

    /* inicializando ciclistas */
    ciclista_round = 0;
    debug_ciclista("=== Round: %d ===\n", ciclista_round);
    for (i = 0; i < 2; i++) {
        ciclista[i] = (ciclista_obj *) malloc(sizeof(ciclista_obj) * ciclista_n);

        for (j = 0; j < ciclista_n; j++)
            ciclista_init(&(ciclista[i][j]), i, j);
    }

    /* rodando simulacao */
    volta_atual = 0;
    volta_atual_barreira = 0;
    while (ciclista_fim < 2*ciclista_n) {
        i = 0;
        while (i < 2) {
            j = 0;
            while (j < ciclista_n) {
                while (ciclista[i][j].round <= ciclista_round && !ciclista[i][j].fim);
                j++;
            }
            i++;
        }

        if (ciclista_round&1) {
            while (volta_atual_atualiza()) {
                if (volta_atual%4 == 0) {
                    ciclista_quebra();
                }
            }
        }

        debug_ciclista("=== Round: %d ===\n", ciclista_round+1);
        ciclista_round++;
    }

    free(pista);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < ciclista_n; j++)
            pthread_join(ciclista[i][j].thread, NULL);
        free(ciclista[i]);
    }
}

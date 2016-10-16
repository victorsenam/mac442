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
        ciclista_quebraveis[i] = (int *) malloc(sizeof(int) * ciclista_n);
        ciclista_quebraveis_n[i] = ciclista_n;

        for (j = 0; j < ciclista_n; j++) {
            ciclista_init(&(ciclista[i][j]), i, j);
            ciclista_quebraveis[i][j] = j;
        }
    }
    volta_final = (volta_ciclista *) malloc(sizeof(volta_ciclista) * ciclista_n * 2);
    volta_final_n = 0;

    /* rodando simulacao */
    volta_atual = 0;
    volta_atual_barreira = 0;
    ciclista_acabou = 0;
    while (ciclista_fim < 2*ciclista_n && !ciclista_acabou) {
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
            if (volta_completos[15][0] == 3 || volta_completos[15][1] == 3) {
                ciclista_acabou = 1;
                printf("Fim da corrida em %dms.\n", (ciclista_round/2+1)*60);
                if (volta_completos[15][0] == 3 && volta_completos[15][1] == 3) {
                    printf("Empate! Os terceiros colocados dos dois times empataram.\n");
                } else if (volta_completos[15][0] == 3) {
                    printf("Time 0 ganhou! O terceiro colocado do time 0 cruzou a linha de chegada.\n");
                    printf("%d ciclistas do time 1 cruzaram a linha de chegada.\n", volta_completos[15][1]);
                } else {
                    printf("Time 1 ganhou! O terceiro colocado do time 1 cruzou a linha de chegada.\n");
                    printf("%d ciclistas do time 0 cruzaram a linha de chegada.\n", volta_completos[15][0]);
                }
            }

            while (volta_atual_atualiza()) {
                if (volta_atual%4 == 0) {
                    ciclista_sorteia_quebra();
                }
            }
        } else {
            if (debug_ativado) {
                debug("Pista depois de %dms: \n", (ciclista_round/2+1)*60);
                debug("Posicao | Ocupantes (Time,Id)\n");
                for (i = 0; i < pista_tamanho; i++) {
                    debug("%4dm |", i);
                    for (j = 0; j < 4; j++)
                        if (pista[2*i+j/2].ocupantes[j%2] != NULL)
                            debug(" (%d,%d)", pista[2*i+j/2].ocupantes[j%2]->time, pista[2*i+j/2].ocupantes[j%2]->id);
                    debug("\n");
                }
            }
        }
        debug_ciclista("=== Round: %d ===\n", ciclista_round+1);
        ciclista_round++;
    }

    printf("Classificação Final:\n");
    for (i = 0; i < volta_final_n; i++)
        printf("%d : Time %d Id %d Terminou em %dms\n", i, volta_final[i].time, volta_final[i].id, volta_final[i].tempo*60);
    printf("Quebrados:\n");
    for (i = 0; i < 2; i++)
        for (j = 0; j < ciclista_n; j++)
            if (ciclista[i][j].quebrado)
                printf("Time %d Id %d Quebrou na volta %d\n", i, j, ciclista[i][j].volta);

    free(pista);
    for (i = 0; i < 2; i++) {
        free(ciclista_quebraveis[i]);
        for (j = 0; j < ciclista_n; j++)
            pthread_join(ciclista[i][j].thread, NULL);
        free(ciclista[i]);
    }
}

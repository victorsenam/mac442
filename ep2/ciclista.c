#include "ciclista.h"

void ciclista_sorteia_quebra () {
    int rnd;
    int time;
    int esc;

    // 10% de chance de deixar quebrar
    rnd = rand()%10;
    if (rnd) return;
    
    while (ciclista_quebraveis_n[0] + ciclista_quebraveis_n[1]) {
        // escolhendo time
        rnd = rand()%(ciclista_quebraveis_n[0] + ciclista_quebraveis_n[1]);
        if (rnd < ciclista_quebraveis_n[0])
            time = 0;
        else
            time = 1;

        // verificando
        if (ciclista_quebraveis_n[time] <= 3) {
            ciclista_quebraveis_n[time] = 0;
            continue;
        }

        // escolhendo ciclista
        rnd = rand()%(ciclista_quebraveis_n[time]);
        esc = ciclista_quebraveis[time][rnd];
        ciclista_quebraveis[time][rnd] = ciclista_quebraveis[time][ciclista_quebraveis_n[time]];
        ciclista_quebraveis[time][ciclista_quebraveis_n[time]] = esc;
        ciclista_quebraveis_n[time]--;

        if (ciclista[time][esc].fim || ciclista[time][esc].quebrado) continue;

        ciclista[time][esc].quebrado = 1;
        break;
    }
}

void ciclista_init (ciclista_obj * obj, char time, int idx) {
    obj->id = idx;
    obj->time = time;

    obj->volta = obj->posicao = 0;
    if (time)
        obj->posicao += pista_tamanho;

    obj->velocidade = obj->ultrapassavel = 0;
    obj->ini = obj->fim = obj->quebrado = 0;

    obj->round = idx*4;

    pthread_create(&(obj->thread), NULL, ciclista_runner, obj);
}

void ciclista_volta (ciclista_obj * obj) {
    int ls;
    int i;
    char imprime;

    pthread_mutex_lock(&volta_mutex[obj->volta][(int) obj->time]);
    if (volta_completos[obj->volta][(int) obj->time] < 3) {
        volta_primeiros[obj->volta][(int) obj->time][volta_completos[obj->volta][(int) obj->time]].tempo = obj->round/2 + 1;
        volta_primeiros[obj->volta][(int) obj->time][volta_completos[obj->volta][(int) obj->time]].id = obj->id;
    }

    if (obj->volta == 15) {
        volta_final[volta_final_n].id = obj->id;
        volta_final[volta_final_n].time = obj->time;
        volta_final[volta_final_n].tempo = (ciclista_round/2)+1;
        volta_final_n++;
    }
    volta_completos[obj->volta][(int) obj->time]++;
    imprime = (volta_completos[obj->volta][(int) obj->time] == 3);
    pthread_mutex_unlock(&volta_mutex[obj->volta][(int) obj->time]);

    if (imprime) {
        pthread_mutex_lock(&volta_imprimindo);
            printf("== Time %d Volta %d ==\n", obj->time, obj->volta+1);
        for (i = 0; i < 3; i++)
            printf("%d completou com %dms\n", volta_primeiros[obj->volta][(int) obj->time][i].id, (volta_primeiros[obj->volta][(int) obj->time][i].tempo)*60);
        pthread_mutex_unlock(&volta_imprimindo);
    }


    obj->volta++;
    ls = obj->velocidade;
    obj->velocidade = rand()%(ciclista_tipo+1);
    obj->ultrapassavel = (!ls && !obj->velocidade);
}

void ciclista_avanca (ciclista_obj * obj) {
    pista_lock((obj->posicao+1)%(2*pista_tamanho), 1, 1);
    pista_lock((obj->posicao+2)%(2*pista_tamanho), 1, 1);

    if (pista_livre((obj->posicao+1)%(2*pista_tamanho)) && pista_livre((obj->posicao+2)%(2*pista_tamanho))) {
        pista_remove(obj);
        obj->posicao = (obj->posicao+1)%(2*pista_tamanho);
        pista_insere(obj);

        if (obj->posicao == pista_tamanho * obj->time)
            ciclista_volta(obj);

        pista_unlock(obj->posicao);
        pista_unlock((obj->posicao+1)%(2*pista_tamanho));
    } else {

        pista_unlock((obj->posicao+1)%(2*pista_tamanho));
        pista_unlock((obj->posicao+2)%(2*pista_tamanho));
    }

}

void * ciclista_runner (void * ref) {
    ciclista_obj * obj = (ciclista_obj *) ref;
    int init_pos;
    int trylock;

    while (42) {
        while (ciclista_round < obj->round);
        assert(ciclista_round == obj->round);

        init_pos = obj->posicao;

        if (obj->round&1) {
            // resetando o estado da pista
            pista[init_pos].atualizados = 0; 
        } else {
            pista_lock(init_pos, 0, 1);

            if (!obj->ini) {
                pista_insere(obj);
                obj->ini = 1;
            }

            if (ciclista_acabou) {
                obj->fim = 1;
            } else if (obj->volta == 16 && !obj->fim) {
                obj->fim = 1;

            } else if (obj->quebrado) {
                printf("%d do time %d quebrou em %dms\n", obj->id, obj->time, (ciclista_round/2+1)*60);
                obj->fim = 1;
            }

            if (obj->fim) {
                pista_remove(obj);
                pista_unlock(init_pos);

                pthread_mutex_lock(&ciclista_fim_mutex);
                ciclista_fim++;
                pthread_mutex_unlock(&ciclista_fim_mutex);

                return NULL;
            }

            ciclista_avanca(obj);
            if (obj->velocidade)
                ciclista_avanca(obj);

            trylock = pista_lock(obj->posicao, 0, 0);
            pista[obj->posicao].atualizados++;
            if (!trylock)
                pista_unlock(obj->posicao);

            pista_unlock(init_pos);
            debug_ciclista("[%d] %d : %d %d\n", obj->time, obj->id, obj->volta, obj->posicao);
        }

        obj->round++;
    }
}

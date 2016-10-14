#include "ciclista.h"

void ciclista_init (ciclista_obj * obj, char time, int idx) {
    obj->id = idx;
    obj->time = time;

    obj->volta = obj->posicao = 0;
    if (time)
        obj->posicao += pista_tamanho;

    obj->velocidade = obj->ultrapassavel = 0;
    obj->ini = obj->fim = 0;

    obj->round = idx*4;

    pthread_create(&(obj->thread), NULL, ciclista_runner, obj);
}

void ciclista_volta (ciclista_obj * obj) {
    int ls;

    obj->volta++;
    ls = obj->velocidade;
    obj->velocidade = rand()%(ciclista_tipo+1);
    obj->ultrapassavel = (!ls && !obj->velocidade);
    
    debug("(%d) %d : volta %d em %d\n", obj->time, obj->id, obj->volta, ciclista_round/2);
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
            pista_lock(init_pos, 0, 1);
            assert(pista[init_pos].atualizados == 0 || pista[init_pos].atualizados == pista[init_pos].quantidade);
            // resetando o estado da pista
            pista[init_pos].atualizados = 0; 
            pista_unlock(init_pos);
        } else {
            pista_lock(init_pos, 0, 1);

            if (!obj->ini) {
                pista_insere(obj);
                obj->ini = 1;
            }

            if (obj->volta == 16 && !obj->fim) {
                obj->fim = 1;
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
            debug_ciclista("(%d) %d : %d %d\n", obj->time, obj->id, obj->volta, obj->posicao);
        }

        obj->round++;
    }
}

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

void ciclista_avanca (ciclista_obj * obj) {
    pista_lock((obj->posicao+1)%(2*pista_tamanho), 1, 0);
    pista_lock((obj->posicao+2)%(2*pista_tamanho), 1, 0);

    if (pista_livre((obj->posicao+1)%(2*pista_tamanho)) && pista_livre((obj->posicao+2)%(2*pista_tamanho))) {
        pista_remove(obj);
        obj->posicao = (obj->posicao+1)%(2*pista_tamanho);

        if (obj->posicao == obj->time * pista_tamanho) {
            obj->volta++;
            debug("(%d) %d : volta %d em %d\n", obj->time, obj->id, obj->volta, ciclista_round/2);
        }

        pista_insere(obj);

        pista_unlock(obj->posicao);
        pista_unlock((obj->posicao+1)%(2*pista_tamanho));
    } else {

        pista_unlock((obj->posicao+1)%(2*pista_tamanho));
        pista_unlock((obj->posicao+2)%(2*pista_tamanho));
    }

}

void * ciclista_runner (void * ref) {
    ciclista_obj * obj = (ciclista_obj *) ref;
    int init_pos = obj->posicao;
    int trylock;

    while (42) {
        while (ciclista_round < obj->round);
        assert(ciclista_round == obj->round);

        if (!obj->ini) {
            pista_insere(obj);
            obj->ini = 1;
        }

        if (obj->fim) return NULL;

        if (obj->round&1) {
            // resetando o estado da pista
            pista[init_pos].atualizados = 0; 
        } else {
            pista_lock(init_pos, 0, 0);

            ciclista_avanca(obj);
            if (obj->velocidade)
                ciclista_avanca(obj);
            
            trylock = pista_lock(obj->posicao, 0, 1);
            pista[obj->posicao].atualizados++;
            if (trylock)
                pista_unlock(obj->posicao);

            pista_unlock(init_pos);
            debug_ciclista("(%d) %d : %d\n", obj->time, obj->id, obj->posicao);
        }

        obj->round++;
    }
}

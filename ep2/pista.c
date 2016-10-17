/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#include "pista.h"

void pista_init (pista_obj * obj) {
    int i;
    for (i = 0; i < 2; i++)
        obj->ocupantes[i] = NULL;

    obj->quantidade = obj->atualizados = 0;
    pthread_cond_init(&(obj->cond), NULL);
    pthread_mutex_init(&(obj->mutex), NULL);
}

int pista_lock (int posicao, char estavel, char block) {
    int res;
    if (estavel) {
        debug_mutex("<%04d> : wait\n", posicao);
        pthread_mutex_lock(&(pista[posicao].mutex));
        while (pista[posicao].atualizados < pista[posicao].quantidade)
            pthread_cond_wait(&(pista[posicao].cond), &(pista[posicao].mutex));
        pthread_mutex_unlock(&(pista[posicao].mutex));
    }

    if (block) {
        res = 1;
        debug_mutex("<%04d> : force\n", posicao);
        pthread_mutex_lock(&(pista[posicao].mutex));
    } else {
        debug_mutex("<%04d> : try\n", posicao);
        res = pthread_mutex_trylock(&(pista[posicao].mutex));
    }

    if (res) {
        debug_mutex("<%04d> : lock\n", posicao);
    } else {
        debug_mutex("<%04d> : keep locked\n", posicao);
    }

    return res;
}

void pista_unlock (int posicao) {
    pthread_cond_signal(&(pista[posicao].cond));
    pthread_mutex_unlock(&(pista[posicao].mutex));
    debug_mutex("<%04d> : free\n", posicao);
}

void pista_remove (ciclista_obj * cic) {
    int i;
    pista_obj * obj = &(pista[cic->posicao]);

    for (i = 0; i < 2; i++) {
        if (obj->ocupantes[i] == cic) {
            obj->ocupantes[i] = NULL;
            obj->quantidade--;
        }
    }
}

void pista_insere (ciclista_obj * cic) {
    int i;
    pista_obj * obj = &(pista[cic->posicao]);

    debug_mutex("<%04d> !\n", cic->posicao);

    for (i = 0; i < 2; i++) {
        if (!obj->ocupantes[i]) {
            obj->ocupantes[i] = cic;
            obj->quantidade++;
            break;
        }
    }
}

char pista_livre (int posicao) {
    int i;
    int cnt = 0;
    pista_obj * obj = &(pista[posicao]);

    for (i = 0; i < 2; i++) {
        if (obj->ocupantes[i]) {
            cnt++;
            if (!obj->ocupantes[i]->ultrapassavel)
                return 0;
        }
    }

    if (cnt == 2) return 0;
    return 1;
}

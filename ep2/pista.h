#ifndef PISTA_MAC442
#define PISTA_MAC442

#include <pthread.h>
#include "ciclista.h"
#include "debug.h"

struct pista_obj_struct ;
typedef struct pista_obj_struct {
    // ocupantes
    struct ciclista_obj_struct * ocupantes[2];

    // contadores
    int quantidade;
    int atualizados;

    // mutex
    pthread_mutex_t mutex;
} pista_obj;

int pista_tamanho;
pista_obj * pista;

void pista_init (pista_obj * obj);

int pista_lock (int posicao, char estavel, char trylock);
void pista_unlock (int posicao);

void pista_remove (struct ciclista_obj_struct * obj);
void pista_insere (struct ciclista_obj_struct * obj);
char pista_livre (int posicao);

#endif

#ifndef CICLISTA_MAC442
#define CICLISTA_MAC442

#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include "pista.h"
#include "debug.h"

struct ciclista_obj_struct ;
typedef struct ciclista_obj_struct {
    // info basica
    int id;
    char time;

    // movimento
    int volta;
    int posicao;        // indica o meio metro da pista onde está a roda traseira do ciclista
    char velocidade;
    char ultrapassavel;
    int fim;
    int ini;

    // threads
    int round;   
    pthread_t thread;
} ciclista_obj;

int ciclista_n;
int ciclista_round;
ciclista_obj * ciclista[2];

void ciclista_init (ciclista_obj * obj, char time, int idx);

void ciclista_avanca (ciclista_obj * obj);
void * ciclista_runner (void * ref);

#endif

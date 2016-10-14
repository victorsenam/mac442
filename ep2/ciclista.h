#ifndef CICLISTA_MAC442
#define CICLISTA_MAC442

#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "pista.h"
#include "volta.h"
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

    // status
    int fim;
    int ini;
    int quebrado;

    // threads
    int round;   
    pthread_t thread;
} ciclista_obj;

int ciclista_n;
int ciclista_round;
int ciclista_fim;
pthread_mutex_t ciclista_fim_mutex;
char ciclista_tipo;
ciclista_obj * ciclista[2];

void ciclista_init (ciclista_obj * obj, char time, int idx);

void ciclista_avanca (ciclista_obj * obj);
void ciclista_volta (ciclista_obj * obj);
void * ciclista_runner (void * ref);

#endif

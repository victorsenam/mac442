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
    pthread_mutex_t cond_mutex;
} ciclista_obj;

int ciclista_n;
char ciclista_tipo;
char ciclista_acabou;
void ciclista_init (ciclista_obj * obj, char time, int idx);

ciclista_obj * ciclista[2];
int ciclista_fim;
void ciclista_avanca (ciclista_obj * obj);
void ciclista_volta (ciclista_obj * obj);

int * ciclista_quebraveis[2];
int ciclista_quebraveis_n[2];
void ciclista_sorteia_quebra ();

int ciclista_round;
pthread_mutex_t ciclista_fim_mutex;
void * ciclista_runner (void * ref);

pthread_cond_t ciclista_cond_principal;
pthread_cond_t ciclista_cond_ciclista;
pthread_mutex_t ciclista_cond_mutex;

#endif

#ifndef CICLISTA_MAC442
#define CICLISTA_MAC442

#include <pthread.h>

typedef struct {
    // info basica
    int id;
    char time;

    // movimento
    char ini;
    int posicao;
    char velocidade;
    char ultima_velocidade;

    // threads
    int round;   
    pthread_t thread;
} ciclista_obj;

int ciclista_n;
int ciclista_round;
ciclista_obj * ciclista[2];

void * ciclista_thread (void * ciclista_ref);

#endif

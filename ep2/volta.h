#ifndef VOLTA_MAC442
#define VOLTA_MAC442

#include <stdlib.h>
#include "debug.h"
#include "pthread.h"
#include "ciclista.h"

struct volta_ciclista_struct ;
typedef struct volta_ciclista_struct {
    int tempo;
    int id;
    int time;
} volta_ciclista;

volta_ciclista volta_primeiros[16][2][3];
int volta_completos[16][2];
pthread_mutex_t volta_mutex[16][2];
pthread_mutex_t volta_imprimindo;

volta_ciclista * volta_final;
int volta_final_n;

int volta_atual;
int volta_atual_barreira;
char volta_atual_atualiza();

#endif

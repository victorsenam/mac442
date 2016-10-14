#ifndef VOLTA_MAC442
#define VOLTA_MAC442

#include <stdlib.h>
#include "debug.h"

struct volta_ciclista_struct ;
typedef struct volta_ciclista_struct {
    int tempo;
    int id;
} volta_ciclista;

volta_ciclista volta_primeiros[16][2][3];
int volta_completos[16][2];
pthread_mutex_t volta_mutex[16][2];
pthread_mutex_t volta_imprimindo;
int volta_atual;

#endif

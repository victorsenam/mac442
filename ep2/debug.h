/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#ifndef DEBUG_MAC442
#define DEBUG_MAC442

#include <stdio.h>
#include <time.h>

int debug_ativado;
int debug_mutex_ativado;
int debug_sync_ativado;
int debug_ciclista_ativado;

#define debug(...) {if (debug_ativado) {fprintf(stdout, __VA_ARGS__);}}
#define debug_mutex(...) {if (debug_mutex_ativado) {fprintf(stdout, __VA_ARGS__);}}
#define debug_sync(...) {if (debug_sync_ativado) {fprintf(stdout, __VA_ARGS__);}}
#define debug_ciclista(...) {if (debug_ciclista_ativado) {fprintf(stdout, __VA_ARGS__);}}

#endif

#include "ciclista.h"

void * ciclista_thread (void * ciclista_ref) {
    ciclista_obj * obj = (ciclista_obj *) ciclista_ref;

    while (true) {
        while (obj->round != ciclista_round);
        obj->round++;
        
        if (!obj->ini) continue;
        
        
    }
}

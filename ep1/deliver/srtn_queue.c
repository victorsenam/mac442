#include "srtn_queue.h"

void srtn_queue_init () {
    srtn_queue_n = 0;
    srtn_queue_size = INIT_SIZE;

    srtn_queue = (task_obj **) malloc(sizeof(task_obj *) * srtn_queue_size);
}

void srtn_queue_add (task_obj * x) {
    task_obj ** nw;
    int i;

    if (srtn_queue_n + 1 == srtn_queue_size) {
        srtn_queue_size *= 2;
        nw = (task_obj **) malloc(sizeof(task_obj *) * srtn_queue_size);

        for (i = 1; i <= srtn_queue_n; i++)
            nw[i] = srtn_queue[i];
        free(srtn_queue);
        srtn_queue = nw;
    }

    srtn_queue[++srtn_queue_n] = x;
    srtn_queue_swim_up(srtn_queue_n);
}

void srtn_queue_deinit () {
    free(srtn_queue);
    srtn_queue_size = 0;
    srtn_queue_n = 0;
}

task_obj * srtn_queue_top () {
    return srtn_queue[1];
}

void srtn_queue_pop () {
    task_obj * aux;

    aux = srtn_queue[srtn_queue_n];
    srtn_queue[srtn_queue_n] = srtn_queue[1];
    srtn_queue[1] = aux;

    srtn_queue_n--;
    srtn_queue_sink_down(1);
}

void srtn_queue_swim_up (int i) {
    task_obj * aux;
    while (i > 1 && srtn_queue[i]->remaining_time < srtn_queue[i>>1]->remaining_time) {
        aux = srtn_queue[i];
        srtn_queue[i] = srtn_queue[i>>1];
        srtn_queue[i>>1] = aux;

        i >>= 1;
    }
}

void srtn_queue_sink_down (int i) {
    task_obj * aux;
    while ((i<<1) <= srtn_queue_n) {
        i <<= 1;
        if (i + 1 <= srtn_queue_n && srtn_queue[i+1]->remaining_time < srtn_queue[i]->remaining_time)
            i++;

        if (srtn_queue[i]->remaining_time > srtn_queue[i>>1]->remaining_time)
            break;

        aux = srtn_queue[i];
        srtn_queue[i] = srtn_queue[i>>1];
        srtn_queue[i>>1] = aux;
    }
}

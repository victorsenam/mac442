#include "queue.h"

void queue_init () {
    queue_n = 0;
    queue_size = INIT_SIZE;

    queue = (task_obj **) malloc(sizeof(task_obj *) * queue_size);
}

void queue_add (task_obj * x) {
    task_obj ** nw;
    int i;

    debug("Task %s arrived at queue\n", x->name);
    if (queue_n + 1 == queue_size) {
        queue_size *= 2;
        nw = (task_obj **) malloc(sizeof(task_obj *) * queue_size);

        for (i = 1; i <= queue_n; i++)
            nw[i] = queue[i];
        free(queue);
        queue = nw;
    }

    queue[++queue_n] = x;
    queue_swim_up(queue_n-1);
}

void queue_deinit () {
    free(queue);
    queue_size = 0;
    queue_n = 0;
}

task_obj * queue_top () {
    return queue[1];
}

void queue_pop () {
    task_obj * aux;

    aux = queue[queue_n];
    queue[queue_n] = queue[1];
    queue[1] = aux;

    queue_n--;
    queue_sink_down(1);
}

void queue_swim_up (int i) {
    task_obj * aux;
    while (i > 1 && queue[i]->remaining_time < queue[i>>1]->remaining_time) {
        aux = queue[i];
        queue[i] = queue[i>>1];
        queue[i>>1] = aux;

        i >>= 1;
    }
}

void queue_sink_down (int i) {
    task_obj * aux;
    while ((i<<1) <= queue_n) {
        i <<= 1;
        if (i + 1 <= queue_n && queue[i+1]->remaining_time < queue[i]->remaining_time)
            i++;

        if (queue[i]->remaining_time > queue[i>>1]->remaining_time)
            break;

        aux = queue[i];
        queue[i] = queue[i>>1];
        queue[i>>1] = aux;
    }
}

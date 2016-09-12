#include "mqs_queue.h"

void mqs_queue_init () {
    mqs_queue_front = mqs_queue_back = 0;
    mqs_queue_size = INIT_SIZE;
    mqs_queue = (task_obj **) malloc(sizeof(task_obj *) * mqs_queue_size);
    mqs_queue_quantum = (int *) malloc(sizeof(int) * mqs_queue_size);
}

void mqs_resize () {
    task_obj ** nw;
    int * nq;
    int new_back, i;

    if (mqs_queue_back == mqs_queue_size) {
        mqs_queue_size *= 2;
        new_back = 0;
        nw = (task_obj **) malloc(sizeof(task_obj *) * mqs_queue_size);
        nq = (int *) malloc(sizeof(int) * mqs_queue_size);

        for (i = mqs_queue_front; i < mqs_queue_back; i++) {
            nw[new_back] = mqs_queue[i];
            nq[new_back] = mqs_queue_quantum[i];
            new_back++;
        }

        mqs_queue_front = 0;
        mqs_queue_back = new_back;
        free(mqs_queue);
        mqs_queue = nw;
        free(mqs_queue_quantum);
        mqs_queue_quantum = nq;
    }

}

void mqs_queue_add (task_obj * new_task) {
    mqs_resize();
    mqs_queue[mqs_queue_back] = new_task;
    mqs_queue_quantum[mqs_queue_back] = 1;
    mqs_queue_back++;

    if (mqs_queue_front == mqs_queue_back)
        mqs_queue_top_start_time = clock();
}

task_obj * mqs_queue_top () {
    return mqs_queue[mqs_queue_front];
}
void mqs_queue_pop () {
    mqs_queue_front++;
    mqs_queue_top_start_time = clock();
}

void mqs_queue_promote_top() {
    mqs_resize();
    mqs_queue[mqs_queue_back] = mqs_queue[mqs_queue_front];
    mqs_queue_quantum[mqs_queue_back] = 1 + mqs_queue_quantum[mqs_queue_front];
    mqs_queue_back++;
    mqs_queue_pop();
}

int mqs_queue_current_queue () {
    return mqs_queue_quantum[mqs_queue_front];
}

#ifndef MQS_QUEUE_MAC442
#define MQS_QUEUE_MAC442

#include "task.h"
#include "debug.h"

#define INIT_SIZE 8

int mqs_queue_front, mqs_queue_back;
int mqs_queue_size;
task_obj ** mqs_queue;
int * mqs_queue_quantum;

void mqs_queue_init ();
void mqs_queue_add (task_obj *);
task_obj * mqs_queue_top ();
void mqs_queue_pop ();

int mqs_queue_current_queue ();
clock_t mqs_queue_top_start_time;

void mqs_queue_promote_top ();

void mqs_resize ();

#endif

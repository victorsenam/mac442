/* Implements a heap ordering tasks by remaining_time */

#ifndef SRTN_QUEUE_MAC442
#define SRTN_QUEUE_MAC442

#include "task.h"
#include "debug.h"

#define INIT_SIZE 8

int srtn_queue_n;
int srtn_queue_size;
task_obj ** srtn_queue;

void srtn_queue_init ();
void srtn_queue_add (task_obj *);
void srtn_queue_deinit ();
task_obj * srtn_queue_top ();
void srtn_queue_pop ();

void srtn_queue_swim_up (int i);
void srtn_queue_sink_down (int i);

#endif

/* Implements a heap ordering tasks by remaining_time */

#ifndef QUEUE_MAC442
#define QUEUE_MAC442

#include "task.h"
#include "debug.h"

#define INIT_SIZE 8

int queue_n;
int queue_size;
task_obj ** queue;

void queue_init ();
void queue_add (task_obj *);
void queue_deinit ();
task_obj * queue_top ();
void queue_pop ();

void queue_swim_up (int i);
void queue_sink_down (int i);

#endif

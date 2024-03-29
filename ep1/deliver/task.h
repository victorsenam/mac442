#ifndef TASK_MAC442
#define TASK_MAC442

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "debug.h"

#define MAX_SIZE (1<<11)
#define INIT_SIZE 8

typedef struct {
    int id;

    struct timespec initial_time;

    double start_time;
    double remaining_time;

    double duration;
    double deadline;
    char * name;

	pthread_t thread;
    char has_thread;

    char running;
} task_obj;

int task_n;
int task_siz;

char task_running;
int task_complete_count;
int task_context_change_count;
int task_deadline_fail_count;
pthread_mutex_t task_running_mutex;

task_obj * task_tasks;

void task_init ();
void task_add (double t0, char * name, double dt, double fn);
void task_free (int i);
void task_deinit ();
char task_read ();
void task_stop (task_obj * task);
void task_run (task_obj * task);

#endif

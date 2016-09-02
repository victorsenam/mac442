#ifndef TASK_MAC442
#define TASK_MAC442

#include <stdio.h>
#include <string.h>

#define MAX_SIZE (1<<11)
#define INIT_SIZE 8

typedef struct {
    double t0, dt, fn;
    char * name;
} task_obj;

int task_n;
int task_siz;
task_obj * task_tasks;

void task_init ();
void task_add (double t0, char * name, double dt, double fn);
void task_free (int i);
void task_deinit ();
char task_read ();

#endif

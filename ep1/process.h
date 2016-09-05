#ifndef PROCESS_MAC442
#define PROCESS_MAC442

#include <stdio.h>
#include "helper.h"
#include "task.h"
#include "debug.h"

int process_running;
void * process_runner (void * task_ref);

#endif

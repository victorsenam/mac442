#include "task.h"

void task_init () {
    task_n = 0;
    task_siz = INIT_SIZE;
    
    task_tasks = (task_obj*) malloc(sizeof(task_obj) * task_siz);
}

void task_add (double t0, char * name, double dt, double fn) {
    int i, name_size;
    task_obj * nw;
    if (task_n == task_siz) {
        task_siz *= 2;
        nw = (task_obj*) malloc(sizeof(task_obj) * task_siz);

        for (i = 0; i < task_n; i++)
            nw[i] = task_tasks[i];
        free(task_tasks);
        task_tasks = nw;
    }

    name_size = strlen(name);

    task_tasks[task_n].start_time = t0;
    task_tasks[task_n].remaining_time = task_tasks[task_n].duration = dt;
    task_tasks[task_n].deadline = fn;
    task_tasks[task_n].running = 0;
    task_tasks[task_n].has_thread = 0;

    task_tasks[task_n].name = (char *) malloc(sizeof(char) * name_size);
    strcpy(task_tasks[task_n].name, name);

    task_n++;
}

void task_free (int i) {
    free(task_tasks[i].name);
}

void task_deinit () {
    int i;
    for (i = 0; i < task_n; i++)
        task_free(i);
    free(task_tasks);
    task_n = 0;
    task_siz = 0;
}

char task_read () {
    char buff[MAX_SIZE];
    double t0, dt, fn;

    if (scanf("%lf %s %lf %lf", &t0, buff, &dt, &fn) == EOF) return 0;
    
    task_add(t0, buff, dt, fn);

    return 1;
}

void task_run (task_obj * task) {
    pthread_mutex_lock(&task_running_mutex);

    if (!task->running) {
        debug("Running task %s %.4fs\n", task->name, task->remaining_time);
        task->running = 1;
        task_running++;
    }

    pthread_mutex_unlock(&task_running_mutex);
}

void task_stop (task_obj * task) {
    pthread_mutex_lock(&task_running_mutex);

    if (task->running) {
        debug("Stopping task %s %.4fs\n", task->name, task->remaining_time);
        task->running = 0;
        task_running--;
    }

    pthread_mutex_unlock(&task_running_mutex);
}

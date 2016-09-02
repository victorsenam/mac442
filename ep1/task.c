#include "task.h"

void task_init () {
    task_n = 0;
    task_siz = INIT_SIZE;
    
    task_tasks = (task_obj*) malloc(sizeof(task_obj) * task_siz);
}

void task_add (double t0, char * name, double dt, double fn) {
    int i, name_size;
    if (task_n == task_siz) {
        task_siz *= 2;
        task_obj * nw = (task_obj*) malloc(sizeof(task_obj) * task_siz);

        for (i = 0; i < task_n; i++)
            nw[i] = task_tasks[i];
        free(task_tasks);
        task_tasks = nw;
    }

    name_size = strlen(name);

    task_tasks[task_n].t0 = t0;
    task_tasks[task_n].dt = dt;
    task_tasks[task_n].fn = fn;

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

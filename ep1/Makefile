GCC_FLAGS=-Wall -pedantic -g -std=c99 -D _POSIX_C_SOURCE=199309L
FILES=ep1sh ep1 task debug helper process fcfs srtn_queue srtn mqs mqs_queue

clear:
	rm ${FILES}

ep1sh: ep1sh.c
	gcc -lreadline ${GCC_FLAGS} -o ep1sh ep1sh.c

ep1: ep1.c task.h debug.h helper.h process.h fcfs.h srtn_queue.h srtn.h mqs_queue.h mqs.h task.c debug.c helper.c process.c fcfs.c srtn_queue.c srtn.c mqs_queue.c mqs.c
	gcc -lpthread ${GCC_FLAGS} -o ep1 ep1.c task.c debug.c helper.c process.c fcfs.c srtn_queue.c srtn.c mqs_queue.c mqs.c



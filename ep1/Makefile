GCC_FLAGS=-Wall -pedantic -g -std=c99
FILES=ep1sh ep1 task debug helper process fcfs

clear:
	rm ${FILES}

ep1sh: ep1sh.c
	gcc -lreadline ${GCC_FLAGS} -o ep1sh ep1sh.c

ep1: ep1.c task.h debug.h helper.h process.h fcfs.h queue.h task.c debug.c helper.c process.c fcfs.c queue.c
	gcc -lpthread ${GCC_FLAGS} -o ep1 ep1.c task.c debug.c helper.c process.c fcfs.c queue.c



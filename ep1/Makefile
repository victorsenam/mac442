GCC_FLAGS=-Wall -pedantic
FILES=ep1sh ep1 debug fcfs

clear:
	rm ${FILES}

ep1sh: ep1sh.c
	gcc -lreadline ${GCC_FLAGS} -o ep1sh ep1sh.c

ep1: ep1.c fcfs.h task.h debug.h fcfs.c task.c debug.c
	gcc -lreadline ${GCC_FLAGS} -o ep1 ep1.c fcfs.c task.c debug.c



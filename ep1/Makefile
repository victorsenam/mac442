GCC_FLAGS=-Wall -pedantic
FILES=ep1sh debug fcfs

clean:
	rm ${FILES}

ep1sh: ep1sh.c fcfs.c debug.c
	gcc -lreadline ${GCC_FLAGS} -o ep1sh ep1sh.c debug.c fcfs.c



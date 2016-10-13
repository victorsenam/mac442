GCC_FLAGS=-g -Wall -pedantic -std=c99 -D _POSIX_C_SOURCE=199309L
FILES=ep2 ciclista pista sorteio

clear:
	rm ${FILES}

ep2: ep2.c ciclista.h pista.h sorteio.h ciclista.c pista.c
	gcc -pthread ${GCC_FLAGS} -o ep2 ep2.c ciclista.c pista.c




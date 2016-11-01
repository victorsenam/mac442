# Nathan Benedetto Proença 8941276
# Victor Sena Molero 8941317
GCC_FLAGS=-g -Wall -pedantic -std=c99 -D _POSIX_C_SOURCE=199309L
FILES=ep2

clear:
	rm ${FILES}

ep2: ep2.c ciclista.h pista.h volta.h ciclista.c pista.c volta.c
	gcc -pthread ${GCC_FLAGS} -o ep2 ep2.c ciclista.c pista.c volta.c




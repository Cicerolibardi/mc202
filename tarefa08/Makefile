CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: listas_legais

listas_legais: *.c
	gcc $(CFLAGS) -c listas_legais.c $(LDFLAGS)
	gcc $(CFLAGS) -c main.c $(LDFLAGS)
	gcc $(CFLAGS) -o listas_legais main.o listas_legais.o $(LDFLAGS)

clean:
	rm -f listas_legais
	rm -f *.o

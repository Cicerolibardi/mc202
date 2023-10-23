CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: mensageiro

mensageiro: mensageiro.c
	gcc $(CFLAGS) -c mensageiro.c $(LDFLAGS)
	gcc $(CFLAGS) -c main.c $(LDFLAGS)
	gcc $(CFLAGS) -o mensageiro main.o mensageiro.o $(LDFLAGS)

clean:
	rm -f mensageiro

CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: corretor

corretor: corretor.c
	gcc $(CFLAGS) -c corretor.c $(LDFLAGS)
	gcc $(CFLAGS) -c main.c $(LDFLAGS)
	gcc $(CFLAGS) -o corretor main.o corretor.o $(LDFLAGS)

clean:
	rm -f corretor

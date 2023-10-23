
all: complexos

complexos: complexos_main.o complexos.o
	gcc complexos_main.o complexos.o -lm -g -o complexos

complexos.o: complexos.c complexos.h
	gcc -std=c99 -Wall -Werror -c -g complexos.c

complexos_main.o: complexos_main.c complexos.h
	gcc -std=c99 -Wall -Werror -c -g complexos_main.c

clean:
	rm -f complexos
	rm -f *.o
FLAGS = -Wall -lm

all: main broker

main: main.c funciones.o 
	gcc $(FLAGS) -o main main.c funciones.o

funciones.o: funciones.c
	gcc -c $(FLAGS) funciones.c

broker: broker.c
	gcc $(FLAGS) -o broker broker.c

clear:
	rm -f *.o main

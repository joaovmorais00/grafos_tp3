all: main

main: main.c tp3.o 
	gcc -O3 tp3.o main.c -o main  -w

tp3.o: tp3.c tp3.h
	gcc -O3 -c  tp3.c  -w

clear:
	rm *.o
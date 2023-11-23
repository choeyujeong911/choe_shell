choesh: main.o mysh.o
	gcc -o choesh main.o mysh.o
main.o: main.c mysh.h
	gcc -c main.c
mysh.o: mysh.c mysh.h
	gcc -c mysh.c

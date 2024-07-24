all : add_nbo

all: add_nbo

add-nbo: add_nbo.o
	gcc -o add_nbo add_nbo.c

add-nbo.o: add_nbo.c
	gcc -c add_nbo.c

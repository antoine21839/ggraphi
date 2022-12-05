OBJS = Graph.o Lecture_fichiers.o main.o Tableau_dynamique.o
OUT = ggraphi
CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
LDFLAGS =

all : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT) $(LDFLAGS)

Graph.o: Graph.c Graph.h
	$(CC) -c $(CFLAGS) Graph.c

Lecture_fichiers.o: Lecture_fichiers.c Lecture_fichiers.h
	$(CC) -c $(CFLAGS) Lecture_fichiers.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

Tableau_dynamique.o: Tableau_dynamique.c Tableau_dynamique.h
	$(CC) -c $(CFLAGS) Tableau_dynamique.c


clean:
	rm -f $(OBJS) $(OUT)

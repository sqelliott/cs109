OBJ= graph
CC = g++
CFLAGS=-c -Wall

all: graph

graph: Graph.o
	$(CC) Graph.o -o $(OBJ)

GraphADT.o: Graph.cpp
	$(CC) $(CFLAGS) Graph.cpp

clean:
	rm *o graph

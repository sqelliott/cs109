EXE=graph
CC = g++ -std=c++11
CFLAGS=-c -Wall
SOURCES= Graph.cpp ShortestPath.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o graph

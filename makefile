OBJS=main.o Graph.o
CXX=g++
CFLAGS=-Wall -std=c++11
LFLAGS=

graph.out: $(OBJS) Graph.h
	$(CXX) $(OBJS) -o graph.out

main.o: main.cpp
	$(CXX) -c $(CFLAGS) main.cpp -o main.o

Graph.o: Graph.cpp
	$(CXX) -c $(CFLAGS) Graph.cpp -o Graph.o

clean:
	rm -f *.o
.PHONY: clean
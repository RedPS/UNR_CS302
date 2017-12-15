CPPFLAGS =

all: test12

test12: test12.o WeightedGraph.o
	g++ $(CPPFLAGS) -o test12 test12.o WeightedGraph.o

clean:
	rm -f test12; rm -f test12.o; rm -f WeightedGraph.o

test12.o: test12.cpp WeightedGraph.h

WeightedGraph.o: WeightedGraph.cpp WeightedGraph.h

CPPFLAGS =

all: test11 ossim

test11: test11.o 
	g++ $(CPPFLAGS) -o test11 test11.o 

ossim: ossim.o 
	g++ $(CPPFLAGS) -o ossim ossim.o 

clean:
	rm -f test11; rm -f test11.o; rm -f ossim; rm -f ossim.o
	
test11.o: test11.cpp Heap.cpp Heap.h

ossim.o: ossim.cpp PriorityQueue.cpp PriorityQueue.h Heap.h Heap.cpp
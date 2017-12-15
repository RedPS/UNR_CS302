all: clean test7 storesim

test7: test7.cpp QueueLinked.cpp
	g++ -I. -Wall -o test7 test7.cpp
	
storesim: storesim.cpp QueueLinked.cpp
	g++ -I. -Wall -o storesim storesim.cpp

clean:
	rm -f test7
	rm -f storesim
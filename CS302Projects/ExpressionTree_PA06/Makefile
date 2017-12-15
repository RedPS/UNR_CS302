CPPFLAGS =

all: test8 test8-ec

test8: test8.o 
	g++ $(CPPFLAGS) -o test8 test8.o 

test8-ec: test8-ec.o 
	g++ $(CPPFLAGS) -o test8-ec test8-ec.o 

clean:
	rm -f test8; rm -f test8.o; rm -f test8-ec; rm -8 test8-ec.o
	
test8.o: test8.cpp ExpressionTree.cpp ExpressionTree.h

test8-ec.o: test8-ec.cpp ExpressionTree.cpp ExpressionTree.h
CPPFLAGS =

all: test9 db9

test9: test9.o 
	g++ $(CPPFLAGS) -o test9 test9.o 

db9: database.o 
	g++ $(CPPFLAGS) -o db9 database.o 

clean:
	rm -f test9; rm -f test9.o; rm -f database; rm -f database.o
	
test9.o: test9.cpp BSTree.cpp BSTree.h config.h

database.o: database.cpp BSTree.cpp BSTree.h
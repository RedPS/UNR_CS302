CPPFLAGS =

all: test10 login

test10: test10.o 
	g++ $(CPPFLAGS) -o test10 test10.o 

login: login.o 
	g++ $(CPPFLAGS) -o login login.o 

clean:
	rm -f test10; rm -f test10.o; rm -f login; rm -f login.o
	
test10.o: test10.cpp BSTree.cpp BSTree.h HashTable.h HashTable.cpp

login.o: login.cpp BSTree.cpp BSTree.h HashTable.h HashTable.cpp
CPPFLAGS = -O2

all: testtimer

testtimer: testtimer.o Timer.o
	g++ $(CPPFLAGS) -o testtimer testtimer.o Timer.o

Timer.o: Timer.cpp Timer.h

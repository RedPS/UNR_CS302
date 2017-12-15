CPPFLAGS =

all: RushHour

RushHour: RushHour.o RushHourClasses.o
	g++ $(CPPFLAGS) -o RushHour RushHour.o RushHourClasses.o

clean:
	rm -f RushHour; rm -f RushHour.o; rm -f RushHourClasses.o

RushHour.o: RushHour.cpp RushHourClasses.h

RushHourClasses.o: RushHourClasses.cpp RushHourClasses.h

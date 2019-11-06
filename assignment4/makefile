all: main.o goboard.o
	g++ -Wall -o doorn4 goboard.o main.o
goboard.o: goboard.cpp goboard.h
	g++ -Wall -c goboard.cpp
main.o: main.cpp goboard.h
	g++ -Wall -c main.cpp
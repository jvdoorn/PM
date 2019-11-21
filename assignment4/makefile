all: main.o board.o
	g++ -Wall -o doorn4 board.o main.o
board.o: board.cpp board.h
	g++ -Wall -c board.cpp
main.o: main.cpp board.h
	g++ -Wall -c main.cpp
all: main.o board.o
	g++ -Wall -std=c++11 -o doorn4 board.o main.o
board.o: board.cpp board.h
	g++ -Wall -std=c++11 -c board.cpp
main.o: main.cpp board.h
	g++ -Wall -std=c++11 -c main.cpp
#include "board.h"

int main() {
    Board board;

    board.construct();

    board.set(3, 4, 'w');
    board.set(9, 8, 'z');

    board.print();

    return 0;
}
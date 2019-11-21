#include "board.h"

int main() {
    Board board = Board(10, 10, 3, true, false);

    board.construct();

    board.set(3, 4, 'w');
    board.set(9, 8, 'z');

    board.print();

    return 0;
}
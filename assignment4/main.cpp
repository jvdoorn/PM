#include <iostream>
#include "board.h"

bool is_affirmative(const std::string &value) {
    return value == "Y" ||
           value == "y";
}

int main() {
    // TODO: info block

//    int _height, _width, _amount;
//    std::string _holder;
//    bool _player1, _player2;
//    std::cout << "What will be the height of the board: ";
//    std::cin >> _height;
//    std::cout << "What will be the width of the board: ";
//    std::cin >> _width;
//    std::cout << "How many on a row will we play: ";
//    std::cin >> _amount;
//    std::cout << "Do you want a human to play player 1 (black) (Y/N): ";
//    std::cin >> _holder;
//    _player1 = is_affirmative(_holder);
//    std::cout << "Do you want a human to play player 2 (white) (Y/N): ";
//    std::cin >> _holder;
//    _player2 = is_affirmative(_holder);
//
//    Board board = Board(_height, _width, _amount, _player1, _player2);
    Board board = Board(20, 20, 5, true, true);

    board.construct();

    board.set(0, 0, 1);
    board.set(1, 1, 1);
    board.set(3, 4, 1);
    board.set(9, 8, 2);

    board.print();

    return 0;
}
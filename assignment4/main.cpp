/*
 * main.cpp
 *
 * Assignment 4: n-on-a-row
 * Author: Julian van Doorn (2518074)
 *
 * This is a game called n-on-a-row. It allows you to play yourself
 * or simulate games. It also provides additional functionality as
 * described in the task.
 *
 * Last edited on: Sunday December 8th 2019
 * Compiled using cmake version 3.15.3 on macOS 10.15
 *
 */

#include <iostream>
#include "board.h"

bool is_affirmative(const std::string &value) {
    /**
     * Checks if an input is affirmative.
     */
    return value == "Y" ||
           value == "y";
}

void print_description() {
    /**
     * Print a description of the game.
     */
    std::cout << "================================================" << std::endl
              << "|n-on-a-row                                    |" << std::endl
              << "|Author: Julian van Doorn (s2518074)           |" << std::endl
              << "|The program will ask you for a couple settings|" << std::endl
              << "|and then lets you play or simulate the game.  |" << std::endl
              << "|                                              |" << std::endl
              << "|Date: 8 December 2019                         |" << std::endl
              << "================================================" << std::endl;
}

void query_options(int &height, int &width, int &amount, bool &player1, bool &player2, int &count) {
    /**
     * Query the user for the game settings.
     */
    std::string holder;

    std::cout << "What will be the height of the board: ";
    std::cin >> height;
    std::cout << "What will be the width of the board: ";
    std::cin >> width;
    std::cout << "How many on a row will we play: ";
    std::cin >> amount;
    std::cout << "Do you want a human to play player 1 (black) (Y/N): ";
    std::cin >> holder;
    player1 = is_affirmative(holder);
    std::cout << "Do you want a human to play player 2 (white) (Y/N): ";
    std::cin >> holder;
    player2 = is_affirmative(holder);
    std::cout << "How many games do you want to play: ";
    std::cin >> count;
}

int main() {
    /**
     * Main function.
     */
    srand(time(nullptr));

    print_description();

    int height, width, amount, count;
    bool player1, player2;

    query_options(height, width, amount, player1, player2, count);

    Board board = Board(height, width, amount, player1, player2);
    board.construct();

    for (int i = 0; i < count; i++) {
        board.play();
        board.clean();
    }

    if (!player1 && !player2) {
        board.print_summary();
    }

    board.deconstruct();

    return 0;
}
#include <iostream>
#include "board.h"

Board::Board() {
    start = nullptr;

    height = 10;
    width = 10;
    amount = 1;

    player1 = true;
    player2 = true;

    player1char = 'W';
    player2char = 'Z';

    turn = true;
}

void Board::construct() {
    Field *previous_row = nullptr;
    Field *row_start = nullptr;
    Field *previous = nullptr;
    Field *current = nullptr;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            current = new Field;

            if (row == 0 and col == 0) {
                start = current;
            }
            if (col == 0) {
                row_start = current;
                previous = current;
            } else {
                // Connect us to our left neighbour
                current->neighbours[3] = previous;
                current->neighbours[3]->neighbours[4] = current;
            }

            if (row > 0) {
                Field *above = previous_row;
                for (int i = 0; i < col; i++) {
                    above = above->neighbours[4];
                }

                // Connect us to our upper neighbours
                current->neighbours[0] = above->neighbours[3];
                current->neighbours[1] = above;
                current->neighbours[2] = above->neighbours[4];

                if (row != 0) {
                    // Connect our upper neighbours to us and our direct (left/right) neighbours
                    above->neighbours[5] = current->neighbours[3];
                    above->neighbours[6] = current;
                    above->neighbours[7] = current->neighbours[4];
                }
            }
            previous = current;
        }
        previous_row = row_start;
    }
}

bool Board::set(int w, int h, char value) {
    Field *target = start;

    if (w > width - 1 || h > height - 1) {
        return false;
    }

    for (int y = 0; y < h; y++) {
        target = target->neighbours[6];
    }
    for (int x = 0; x < w; x++) {
        target = target->neighbours[4];
    }

    if (target->value != ' ') {
        return false;
    }

    target->value = value;
    return true;
}

void Board::print() {
    Field *row = start;

    while (row != nullptr) {
        Field *col = row;

        while (col != nullptr) {
            std::cout << col->value << ' ';
            col = col->neighbours[4];
        }
        std::cout << std::endl;
        row = row->neighbours[6];
    }
}
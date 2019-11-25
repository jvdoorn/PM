#include <iostream>
#include "board.h"


Board::Board(int _height, int _width, int _amount, bool _player1, bool _player2) {
    height = _height;
    width = _width;
    amount = _amount;

    player1 = _player1;
    player2 = _player2;
}

void Board::construct() {
    Field *previous_row_start = nullptr;
    Field *row_start = nullptr;
    Field *previous = nullptr;
    Field *current = nullptr;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            current = new Field;

            if (col == 0) {
                row_start = current;

                if (row == 0) {
                    start = current;
                }
            } else {
                // Connect us to our left neighbour
                current->neighbours[3] = previous;
                current->neighbours[3]->neighbours[4] = current;
            }

            if (row > 0) {
                Field *above = previous_row_start;
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
        previous_row_start = row_start;
    }
}

Field *Board::get(int x, int y) {
    Field *target = start;

    if (x > width - 1 || y > height - 1 || x < 0 || y < 0) {
        return nullptr;
    }

    for (int i = 0; i < y; i++) {
        target = target->neighbours[6];
    }
    for (int i = 0; i < x; i++) {
        target = target->neighbours[4];
    }

    return target;
}

bool Board::set(int x, int y, int value) {
    Field *target = get(x, y);
    if (target == nullptr) {
        return false;
    }

    switch (value) {
        case 1:
            target->value = player1char;
            turns++;
            return true;
        case 2:
            target->value = player2char;
            turns++;
            return true;
        default:
            target->value = ' ';
            turns--;
            return true;
    }
}

void Board::print() {
    Field *row = start;

    std::string s1 = "\n";
    std::string s2 = "\n";
    std::string s3 = "\n";

    for (int i = width - 1; i >= 0; i--) {
        std::string si = std::to_string(i);
        si.reserve();

        if (i > 99) {
            s1 = si[2] + s1;
            s2 = si[1] + s2;
            s3 = si[0] + s3;
        } else if (i > 9) {
            s1 = " " + s1;
            s2 = si[1] + s2;
            s3 = si[0] + s3;
        } else {
            s1 = " " + s1;
            s2 = " " + s2;
            s3 = si[0] + s3;
        }

        s1 = " " + s1;
        s2 = " " + s2;
        s3 = " " + s3;
    }

    std::cout << "  " << s1 << "  " << s2 << "  " << s3;

    int r = 0;
    while (row != nullptr) {
        Field *col = row;

        printf("%3d", r);
        while (col != nullptr) {
            std::cout << col->value << ' ';
            col = col->neighbours[4];
        }
        std::cout << std::endl;
        row = row->neighbours[6];

        r++;
    }
}

bool Board::full() {
    return turns >= width * height;
}

int Board::score(Field *target, int direction) {
    int score = 0;

    if (target->neighbours[direction] == nullptr) {
        return score;
    }

    Field *next = target->neighbours[direction];
    while (next->value == target->value) {
        score += 1;
        if (next->neighbours[direction] == nullptr) {
            break;
        }
    }
    return score;
}

bool Board::check(int x, int y) {
    Field *target = get(x, y);
    if (target == nullptr || target->value == ' ') {
        return false;
    }

    return score(target, 0) + score(target, 7) + 1 >= amount ||
           score(target, 1) + score(target, 6) + 1 >= amount ||
           score(target, 2) + score(target, 5) + 1 >= amount ||
           score(target, 3) + score(target, 4) + 1 >= amount;

}
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

bool Board::set(int x, int y, char value) {
    Field *target = get(x, y);
    if (target == nullptr || (target->value != ' ' && value != ' ')) {
        return false;
    }

    target->value = value;
    return true;
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

int Board::filled() {
    return turns;
}

bool Board::full() {
    return filled() == width * height;
}

int Board::score(Field *target, int direction) {
    int score = 0;

    Field *next = target->neighbours[direction];
    while (next != nullptr && next->value == target->value) {
        score += 1;
        next = next->neighbours[direction];
    }
    return score;
}

bool Board::check(int x, int y) {
    Field *target = get(x, y);
    if (target == nullptr) {
        return false;
    }

    return score(target, 0) + score(target, 7) + 1 >= amount ||
           score(target, 1) + score(target, 6) + 1 >= amount ||
           score(target, 2) + score(target, 5) + 1 >= amount ||
           score(target, 3) + score(target, 4) + 1 >= amount;

}

void Board::user_controls(int &x, int &y, bool &q, bool &c) {
    std::cout << "Enter x-coordinate or negative number for options: ";
    std::cin >> x;

    if (x < 0) {
        int m;
        std::cout << "1) Quit 2) Back 3) Undo 4) calculate: ";
        std::cin >> m;

        switch (m) {
            case 1:
                q = true;
                break;
            case 2:
                break;
            case 3:
                undo(2);
                break;
            case 4:
                std::cout << calculate() << " possible games from this point.";
                c = true;
                break;
            default:
                break;
        }
    } else {
        std::cout << "Enter y-coordinate: ";
        std::cin >> y;
    }
}

void Board::computer_controls(int &x, int &y) {
    int ty;
    int tx;

    while (true) {
        ty = rand() % height;
        tx = rand() % width;

        if (get(tx, ty)->value == ' ') {
            x = tx;
            y = ty;
            return;
        }
    }
}

bool Board::play(bool &_winner, bool &_won, int &_turns) {
    while (true) {
        int x;
        int y;
        bool q = false;
        bool c = false;

        if ((player1 && !turn) || (player2 && turn)) {
            print();

            user_controls(x, y, q, c);
            if (q) { return true; } else if (c) { c = false; continue; }
        } else {
            computer_controls(x, y);
        }

        if (set(x, y, !turn ? player1char : player2char)) {
            turns++;
            save(x, y);

            if (check(x, y)) {
                _winner = turn;
                _won = true;
                _turns = turns;

                return false;
            } else if (full()) {
                _won = false;
                _turns = turns;

                return false;
            }

            turn = !turn;
        } else {
            std::cout << "Failed to do action.";
        }
    }
}

void Board::deconstruct_history() {
    Action *p = last_action;
    Action *n;
    while (p != nullptr) {
        n = p->previous;
        delete (p);
        p = n;
    }

    last_action = nullptr;
}

void Board::clean() {
    turns = 0;
    turn = false;

    deconstruct_history();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            set(x, y, ' ');
        }
    }
}

void Board::deconstruct() {
    deconstruct_history();

    for (int y = height - 1; y >= 0; y--) {
        for (int x = width - 1; x >= 0; x--) {
            delete get(x, y);
        }
    }

    start = nullptr;
}

void Board::save(int x, int y) {
    last_action = new Action(x, y, last_action);
}

void Board::undo(int times) {
    for (int i = 0; i < times; i++) {
        Action *p = last_action;
        if (p == nullptr) {
            return;
        }
        set(p->x, p->y, ' ');
        turns--;
        turn = !turn;

        last_action = p->previous;
        delete p;
    }
}

int Board::calculate() {
    int count = 0;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Field *p = get(x, y);

            if (p->value == ' ') {
                set(x, y, !turn ? player1char : player2char);
                save(x, y);
                turn = !turn;

                if (full() || check(x, y)) {
                    count += 1;
                } else {
                    count += calculate();
                }

                undo(1);
            }
        }
    }

    return count;
}

Action::Action(int _x, int _y, Action *_previous) {
    x = _x;
    y = _y;
    previous = _previous;
}
/*
 * board.cpp
 *
 * Last edited on: Sunday December 8th 2019
 */

#include <iostream>
#include "board.h"


Board::Board(int _height, int _width, int _amount, bool _player1, bool _player2) {
    height = _height;
    width = _width;
    amount = _amount;

    player1 = _player1;
    player2 = _player2;

    turns_keeper = new int[width * height];
}

void Board::construct() {
    Field *previous_row_start = nullptr; // Previous row
    Field *row_start = nullptr; // Current row
    Field *previous = nullptr; // Previous field
    Field *current = nullptr; // Current field

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            current = new Field; // Create a new field

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
                Field *above = previous_row_start; // The field above us
                for (int i = 0; i < col; i++) {
                    // Take the i-th element in the row above
                    above = above->neighbours[4];
                }

                // Connect us to our upper neighbours
                current->neighbours[0] = above->neighbours[3];
                current->neighbours[1] = above;
                current->neighbours[2] = above->neighbours[4];

                // Connect our upper neighbours to us and our direct (left/right) neighbours
                above->neighbours[5] = current->neighbours[3];
                above->neighbours[6] = current;
                above->neighbours[7] = current->neighbours[4];

            }
            previous = current;
        }
        previous_row_start = row_start;
    }
}

Field *Board::get(int x, int y) {
    Field *target = start; // The target field

    if (x > width - 1 || y > height - 1 || x < 0 || y < 0) {
        return nullptr; // Field does not exist
    }

    for (int i = 0; i < y; i++) {
        // Move down
        target = target->neighbours[6];
    }
    for (int i = 0; i < x; i++) {
        // Move to the right
        target = target->neighbours[4];
    }

    return target;
}

bool Board::set(int x, int y, char value) {
    Field *target = get(x, y); // Get the target
    if (target == nullptr || (target->value != ' ' && value != ' ')) {
        return false; // Failed to update
    }

    target->value = value;
    return true; // Successfully updated
}

void Board::print() {
    Field *row = start;

    std::string s1 = "\n", s2 = "\n", s3 = "\n";

    // Creates strings for our x coordinates.
    for (int i = width - 1; i >= 0; i--) {
        std::string si = std::to_string(i);

        if (i > 99) {
            s1.insert(0, 1, si[2]);
            s2.insert(0, 1, si[1]);
            s3.insert(0, 1, si[0]);
        } else if (i > 9) {
            s1.insert(0, 1, ' ');
            s2.insert(0, 1, si[1]);
            s3.insert(0, 1, si[0]);
        } else {
            s1.insert(0, 1, ' ');
            s2.insert(0, 1, ' ');
            s3.insert(0, 1, si[0]);
        }

        // Spacing between the numbers on x axis
        s1.insert(0, 1, ' ');
        s2.insert(0, 1, ' ');
        s3.insert(0, 1, ' ');
    }

    // Print the x axis
    std::cout << "  " << s1 << "  " << s2 << "  " << s3;

    // Print the y axis and all the field values
    int r = 0;
    while (row != nullptr) {
        Field *col = row;

        printf("%3d", r); // y axis
        while (col != nullptr) {
            std::cout << col->value << ' '; // Print field
            col = col->neighbours[4]; // Go to the next
        }
        std::cout << std::endl; // Newline
        row = row->neighbours[6]; // Go to next row
        r++; // Increment for y axis
    }
}

int Board::filled() {
    return turns;
}

bool Board::full() {
    return filled() == width * height;
}

int Board::score(Field *target, int direction) {
    int score = 0; // The score in the given direction

    Field *next = target->neighbours[direction];
    while (next != nullptr && next->value == target->value) {
        score++; // Increment score
        next = next->neighbours[direction]; // Go to the next field
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
        // Give menu options
        std::cout << "1) Quit 2) Back 3) Undo 4) calculate: ";
        std::cin >> y;

        c = true; // Tells the game we had a menu (avoid calling set())
        switch (y) {
            case 1:
                q = true; // Quit the game
                break;
            case 2:
                break; // Continue with the game
            case 3:
                undo(2); // Undo twice (to their previous turn)
                break;
            case 4:
                std::cout << calculate() << " possible games from this point.";
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
    while (true) {
        y = rand() % height;
        x = rand() % width;

        if (get(x, y)->value == ' ') {
            return;
        }
    }
}

void Board::print_result(bool won) {
    if (!won) {
        std::cout << "There was a tie after " << turns << " turns." << std::endl;
    } else if (!turn) {
        std::cout << "Player one has won after " << turns << " turns." << std::endl;
    } else {
        std::cout << "Player two has won after " << turns << " turns." << std::endl;
    }
}

void Board::print_summary() {
    std::cout << std::endl;
    std::cout << "Player one has won " << p1_wins << " times and player two " << p2_wins << " times." << std::endl;
    std::cout << "There were " << ties << " ties." << std::endl;

    std::cout << "Turn statistics: " << std::endl << "Turns : amount" << std::endl;
    for (int i = 0; i < width * height; i++) {
        // Print the amount of games that took n turns
        printf("%5d : %d \n", i + 1, turns_keeper[i]);
    }
}

void Board::play() {
    int x, y; // Coordinates
    bool q = false, c = false; // Quit/continue flags

    while (true) {
        if ((player1 && !turn) || (player2 && turn)) {
            print();

            user_controls(x, y, q, c);
            if (q) {
                return; // Quit
            } else if (c) {
                c = false;
                continue; // Avoid failing an action
            }
        } else {
            computer_controls(x, y);
        }

        if (set(x, y, !turn ? player1char : player2char)) {
            turns++;
            save(x, y);

            if (check(x, y)) {
                print_result(true);
                turns_keeper[turns - 1] += 1; // Increment turn
                !turn ? p1_wins++ : p2_wins++; // Increment wins
                return;
            } else if (full()) {
                print_result(false);
                turns_keeper[turns - 1]++; // Increment turn
                ties++; // Increment ties
                return;
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
    turn = false; // Player 1 turn again

    deconstruct_history();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            set(x, y, ' '); // Clear the board
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

    turns_keeper = {nullptr};
    p1_wins = 0, p2_wins = 0, ties = 0;

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
        turns--; // We undid a turn so decrement
        turn = !turn;

        last_action = p->previous;
        delete p;
    }
}

long Board::calculate() {
    long count = 0;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Field *p = get(x, y);

            if (p->value == ' ') {
                set(x, y, !turn ? player1char : player2char);
                save(x, y);
                turns += 1;
                turn = !turn;

                if (full() || check(x, y)) {
                    // We reached a final state
                    undo(1);
                    count += 1;
                } else {
                    // Recursive call
                    count += calculate();
                    undo(1);
                }
            }
        }
    }

    return count;
}

Action::Action(int _x, int _y, Action *_previous) {
    /**
     * Constructor of the Action class, should be
     * self explanatory.
     */
    x = _x;
    y = _y;
    previous = _previous;
}
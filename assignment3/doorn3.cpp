/*
 * doorn3.cpp
 *
 * Assignment 3: Life
 * Author: Julian van Doorn (2518074)
 *
 * This is an implementation of Conway's Game of Life. It furthermore aims to provide
 * additional functionality as specified in assignment 3. It has 3 menus: main, options
 * and file.
 *
 * Last edited on: Monday November 4th 2019
 * Compiled using cmake version 3.15.3 on macOS 10.15
 *
 */

#include <iostream>
#include <fstream>

#define pinput input.erase(0, 1);
#define pinputre pinput if (input.empty()) { return; }
#define pinputr pinput return;
#define pinputreb pinputre else { break; }

class Life {
    // These variables define the dimensions of our world.
    static const int width = 1000; // Width of the world
    static const int height = width; // Height of the world

    // The next two variables are based on the default Terminal dimensions on Mac OS.
    static const int view_width = 80; // The width of the terminal (assumption)
    static const int view_height = 24; // The height of the terminal (assumption)

    // Initialize two 2D-arrays that will contain our cells.
    bool current_world[width][height] = {false}; // The current world
    bool next_world[width][height] = {false}; // The next world

    // Initialize some default characters.
    char border_character = '#'; // The character for the border of the world.
    char alive_character = '+'; // The character for a living cell.
    char dead_character = ' '; // The character for a dead cell.
    char cursor_character = '@'; // The character for the cursor.
    char bar_character = '='; // The character for the edge (top/bottom).

    // These variables keep track of the game state, view, etc.
    int generation = 0; // Which generation we're in.
    int percentage = 20; // Percentage of alive cells when generating random world.
    int view_x = (width - view_width) / 2; // The x-coordinate of the view (top left).
    int view_y = (height - view_height) / 2; // The y-coordinate of the view (top left).
    int cursor_x = width / 2; // The x-coordinate of the cursor.
    int cursor_y = height / 2; // The y-coordinate of the cursor.
    int cursor_step = 1; // How much the cursor is shifted.
    int go_step = 100; // How many generations are generated.
    int menu = 0; // 0=main,1=options,2=file

    public:
    void print_bar() {
        // Prints a bar
        for (int i = 0; i < view_width; i++) {
            std::cout << bar_character;
        }
        std::cout << std::endl;
    }

    void print_world() {
        print_bar();
        // Last three lines reserved for menu/input and two edges hence the -5 in the next line.
        for (int y = view_y; y < view_y + view_height - 5; y++) {
            for (int x = view_x; x < view_x + view_width; x++) {
                if (x == cursor_x && y == cursor_y) {
                    std::cout << cursor_character;
                } else if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                    std::cout << border_character;
                } else {
                    if (current_world[y][x]) {
                        std::cout << alive_character;
                    } else {
                        std::cout << dead_character;
                    }
                }
            }

            std::cout << std::endl;
        }
        print_bar();
    }

    void print_options() {
        std::cout << "GEN " << generation << ", x=" << view_x << ", y=" << view_y << ", g=" << go_step << ", r="
                  << percentage << ", cx=" << cursor_x << ", cy=" << cursor_y << ", l='" << alive_character << "', d='"
                  << dead_character << "'" << std::endl;
    }

    void print_menu() {
        if (menu == 0) {
            std::cout << "(S)top (P)urge (C)lean (O)ptions (R)andom (F)ile (T)oggle (N)ext (G)o:" << std::endl;
        } else if (menu == 1) {
            std::cout << "(B)ack (L/D)character (X/Y/G/S/R)integer:" << std::endl;
        } else if (menu == 2) {
            std::cout << "Enter file name (leave empty to return):" << std::endl;
        }
    }

    void print() {
        print_world();
        print_options();
        print_menu();
    }

    bool lives(int x, int y) {
        // Determines if a cell will live in the next generation
        if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
            return false; // The border is always dead
        } else {
            int sum = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0) { continue; }
                    if (current_world[y + dy][x + dx]) {
                        sum += 1;
                    }
                }
            }

            return (current_world[y][x] && (sum == 2 || sum == 3)) || (!current_world[y][x] && sum == 3);
        }
    }

    void clear(int x1, int x2, int y1, int y2) {
        // Clears a specific area of the world.
        generation += 1;

        for (int y = y1; y < y2; y++) {
            for (int x = x1; x < x2; x++) {
                current_world[y][x] = false;
            }
        }
    }

    void clear() {
        // Clears the whole world.
        clear(1, width - 1, 1, height - 1);
    }

    bool random() {
        static long value = time(nullptr);

        value = (221 * value + 1) % 100000;
        return (value / 1000) < percentage;
    }

    void populate() {
        // Populates the world at random.
        generation += 1;

        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                current_world[y][x] = random();
            }
        }
    }

    void simulate() {
        // Calculates the next generation and then updates the current one.
        generation += 1;

        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                next_world[y][x] = lives(x, y);
            }
        }

        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                current_world[y][x] = next_world[y][x];
            }
        }
    }

    void simulate(int iterations) {
        // Simulate X generations
        for (int i = 0; i < iterations; i++) {
            simulate();
            print();
        }
    }

    void toggle(int x, int y) {
        // Toggles a specific cell (excluding border cells)
        if (x > 0 && x < width - 1 && y > 0 && y < height - 1) {
            current_world[y][x] = !current_world[y][x];
        }
    }

    static void set_int(int &integer, int value, int min, int max) {
        if (value < min) {
            integer = min;
        } else if (value > max) {
            integer = max;
        } else {
            integer = value;
        }
    }

    static void extract_integer(std::string &input, int &integer, int min, int max) {
        std::string number = "0";
        do {
            char c = input[0];

            if ('0' <= c && c <= '9') {
                number += c;
                pinput
            } else {
                set_int(integer, std::stoi(number), min, max);
                return;
            }
        } while (true);
    }

    void load_file(const std::string &file_name) {
        std::ifstream input(file_name);

        if (input.fail()) {
            return;
        }

        clear();

        int dx = 0, dy = 0;

        char c;
        while (input.get(c)) {
            if (c == ' ') {
                current_world[cursor_y + dy][cursor_x + dx] = false;
                dx += 1;
            } else if (c == '\n') {
                dy += 1;
                dx = 0;
            } else {
                current_world[cursor_y + dy][cursor_x + dx] = true;
                dx += 1;
            }
        }
    }

    void file_menu(std::string &input) {
        std::string file_name;

        do {
            if (input[0] == ' ' || input[0] == '\n' || input.empty()) {
                load_file(file_name);
                menu = 0;
                pinputr
            } else {
                file_name += input[0];
                pinput
            }
        } while (true);
    }

    void option_menu(std::string &input) {
        do {
            switch (input[0]) {
                case 'b':
                case 'B':
                    menu = 0;
                    pinputr
                case 'l':
                case 'L':
                pinputre
                    else {
                        if (input[0] != dead_character) { alive_character = input[0]; }
                        pinputreb
                    }
                case 'd':
                case 'D':
                pinputre
                    else {
                        if (input[0] != alive_character) { dead_character = input[0]; }
                        pinputreb
                    }
                case 'x':
                case 'X':
                    pinput
                    extract_integer(input, view_x, 0, width - view_width);
                    break;
                case 'y':
                case 'Y':
                    pinput
                    extract_integer(input, view_y, 0, height - view_height);
                    break;
                case 'g':
                case 'G':
                    pinput
                    extract_integer(input, go_step, 0, 250);
                    break;
                case 's':
                case 'S':
                    pinput
                    extract_integer(input, cursor_step, 1, 5);
                    break;
                case 'r':
                case 'R':
                    pinput
                    extract_integer(input, percentage, 0, 100);
                    break;
                default:
                pinputre
            }
        } while (true);
    }

    void main_menu(std::string &input) {
        do {
            switch (input[0]) {
                case 's':
                case 'S':
                    menu = -1;
                    return;
                case 'o':
                case 'O':
                    menu = 1;
                    pinputr
                case 'f':
                case 'F':
                    menu = 2;
                    pinputr
                case 'r':
                case 'R':
                    populate();
                    pinputreb
                case 'n':
                case 'N':
                    simulate();
                    print();
                    pinputreb
                case 'g':
                case 'G':
                    simulate(go_step);
                    pinputreb
                case 'p':
                case 'P':
                    clear();
                    pinputreb
                case 'i':
                case 'I':
                    set_int(cursor_y, cursor_y - cursor_step, 0, height);
                    pinputreb
                case 'j':
                case 'J':
                    set_int(cursor_x, cursor_x - cursor_step, 0, width);
                    pinputreb
                case 'k':
                case 'K':
                    set_int(cursor_y, cursor_y + cursor_step, 0, height - 1);
                    pinputreb
                case 'l':
                case 'L':
                    set_int(cursor_x, cursor_x + cursor_step, 0, width - 1);
                    pinputreb
                case 't':
                case 'T':
                    toggle(cursor_x, cursor_y);
                    pinputreb
                case 'c':
                case 'C':
                    clear(view_x, view_x + view_width, view_y, view_y + view_height);
                    pinputreb
                default:
                pinputr
            }
        } while (true);
    }

    void main() {
        std::string input;

        print();

        char c;
        while (true) {
            c = std::cin.get();

            if (c == '\n') {
                while (!input.empty()) {
                    if (menu == 0) {
                        main_menu(input);
                    } else if (menu == 1) {
                        option_menu(input);
                    } else if (menu == 2) {
                        file_menu(input);
                    } else {
                        return;
                    }
                }
            } else {
                input += c;
            }

            print();
        }
    }
};

int main() {
    Life life; // Our life instance.

    life.main();
}
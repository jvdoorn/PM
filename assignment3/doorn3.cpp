#include <iostream>
#include <fstream>

#define pinput input.erase(0, 1);
#define pinputre pinput if (input.empty()) { return input; }
#define pinputr pinput return input;
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
    char edge_character = '='; // The character for the edge (top/bottom).

    // These variables keep track of the game state, view, etc.
    int generation = 0; // Which generation we're in.
    int percentage = 25; // Percentage of alive cells when generating random world.
    int view_x = (width - view_width) / 2; // The x-coordinate of the view (top left).
    int view_y = (height - view_height) / 2; // The y-coordinate of the view (top left).
    int cursor_x = width / 2; // The x-coordinate of the cursor.
    int cursor_y = height / 2; // The y-coordinate of the cursor.
    int cursor_step = 1; // How much the cursor is shifted.
    int go_step = 100; // How many generations are generated.
    int menu = 0; // 0=main,1=options,2=file

    public:
    void print_edge() {
        for (int i = 0; i < view_width; i++) {
            std::cout << edge_character;
        }
        std::cout << std::endl;
    }

    void print_world() {
        print_edge();
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
        print_edge();
    }

    void print_options() {
        std::cout << "GEN " << generation << ", x=" << view_x << ", y=" << view_y << ", g=" << go_step << ", cx="
                  << cursor_x << ", cy=" << cursor_y << ", l='" << alive_character << "', d='" << dead_character << "'"
                  << std::endl;
    }

    void print_menu() {
        if (menu == 0) {
            std::cout << "(S)top (P)urge (C)lean (O)ptions (R)andom (F)ile (T)oggle (N)ext (G)o:" << std::endl;
        } else if (menu == 1) {
            std::cout << "Enter an option followed by its value (accepts multiple):" << std::endl;
        } else if (menu == 2) {
            std::cout << "Enter file name:" << std::endl;
        }
    }

    void print() {
        print_world();
        print_options();
        print_menu();
    }

    bool lives(int x, int y) {
        // Determines if a cell will live in the next generation (a.k.a. if it has 2 or 3 neighbours).
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

    void clear(int x1, int x2, int y1, int y2) {
        generation += 1;

        // Clears a specific area of the world.
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

    void populate() {
        // Populates the world at random.
        srand(time(nullptr));

        generation += 1;

        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                current_world[y][x] = rand() % 100 < percentage;
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
        for (int i = 0; i < iterations; i++) {
            simulate();
            print();
        }
    }

    void toggle(int x, int y) {
        // Toggles a specific cell.
        if (x > 0 && x < width - 1 && y > 0 && y < height - 1) {
            current_world[y][x] = !current_world[y][x];
        }
    }

    void extract_integer(std::string &input, int &integer) {
        std::string number = "0";
        do {
            char c = input[0];

            if ('0' <= c && c <= '9') {
                number += c;
            } else {
                integer = std::stoi(number);
                return;
            }

            input.erase(0, 1);
        } while (true);

    }

    void load_file(std::string file_name) {
        std::ifstream input(file_name);

        if (input.fail()) {
            std::cout << "fail";
            return;
        }

        clear();

        int dx, dy = 0;

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

    std::string file_menu(std::string input) {
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

    std::string option_menu(std::string input) {
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
                    int x;
                    pinput
                    extract_integer(input, x);

                    if (x + view_width > width) {
                        view_x = width - view_width;
                    } else {
                        view_x = x;
                    }
                    pinputreb
                case 'y':
                case 'Y':
                    int y;
                    pinput
                    extract_integer(input, y);

                    if (y + view_height > height) {
                        view_y = height - view_width;
                    } else {
                        view_y = y;
                    }
                    pinputreb
                case 'g':
                case 'G':
                    int g;
                    pinput
                    extract_integer(input, g);

                    go_step = g;

                    pinputreb
                default:
                pinputre
            }
        } while (true);
    }

    std::string main_menu(std::string input) {
        do {
            switch (input[0]) {
                case 's':
                case 'S':
                    menu = -1;
                    return input;
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
                    cursor_y -= 1;
                    if (cursor_y < 0) { cursor_y = 0; }
                    pinputreb
                case 'j':
                case 'J':
                    cursor_x -= 1;
                    if (cursor_x < 0) { cursor_x = 0; }
                    pinputreb
                case 'k':
                case 'K':
                    cursor_y += 1;
                    if (cursor_y > height - 1) { cursor_y = height - 1; }
                    pinputreb
                case 'l':
                case 'L':
                    cursor_x += 1;
                    if (cursor_x > width - 1) { cursor_x = width - 1; }
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
                        input = main_menu(input);
                    } else if (menu == 1) {
                        input = option_menu(input);
                    } else if (menu == 2) {
                        input = file_menu(input);
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
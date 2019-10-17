#include <iostream>

class Life {
    // These variables define the dimensions of our world.
    static const int width = 100; // Width of the world
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
    int percentage = 10; // Percentage of alive cells when generating random world.
    int view_x = (width - view_width) / 2; // The x-coordinate of the view (top left).
    int view_y = (height - view_height) / 2; // The y-coordinate of the view (top left).
    int cursor_x = width / 2; // The x-coordinate of the cursor.
    int cursor_y = height / 2; // The y-coordinate of the cursor.
    int cursor_step = 1; // How much the cursor is shifted.
    int go_step = 100; // How many generations are generated.
    int menu = 0; // 0=main,1=options,2=file

    public:
    void print_world() {
        // Last three lines reserved for menu/input and two edges hence the -5 in the next line.
        for (int y = view_y; y < view_y + view_height - 5; y++) {
            for (int x = view_x; x < view_x + view_width; x++) {
                if (x == cursor_x && y == cursor_y) {
                    std::cout << cursor_character;
                } else if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                    std::cout << border_character;
                } else {
                    if (current_world[x][y]) {
                        std::cout << alive_character;
                    } else {
                        std::cout << dead_character;
                    }
                }
            }

            std::cout << std::endl;
        }
    }

    void print_edge() {
        for (int i = 0; i < view_width; i++) {
            std::cout << edge_character;
        }
        std::cout << std::endl;
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
            std::cout << "Enter file name:" << std::endl;
        } else {
            std::cout << "Enter an option followed by its value (accepts multiple):" << std::endl;
        }
    }

    void print_full() {
        print_edge();
        print_world();
        print_edge();
        print_options();
        print_menu();
    }

    bool lives(int x, int y) {
        // Determines if a cell will live in the next generation (a.k.a. if it has 2 or 3 neighbours).
        int sum = 0;
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (current_world[x + dx][y + dy]) {
                    sum += 1;
                }
            }
        }

        return sum == 2 || sum == 3;
    }

    void clear(int x1, int x2, int y1, int y2) {
        // Clears a specific area of the world.
        for (int y = y1; y < y2; y++) {
            for (int x = x1; x < x2; x++) {
                current_world[x][y] = false;
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

        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                current_world[x][y] = rand() % 100 < percentage;
            }
        }
    }

    void simulate() {
        // Calculates the next generation and then updates the current one.
        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                next_world[x][y] = lives(x, y);
            }
        }

        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                current_world[x][y] = next_world[x][y];
            }
        }
    }

    void toggle(int x, int y) {
        // Toggles a specific cell.
        if (x > 0 && x < width - 1 && y > 0 && y < height - 1) {
            current_world[x][y] = !current_world[x][y];
        }
    }
};

int main() {
    Life life; // Our life instance.
}
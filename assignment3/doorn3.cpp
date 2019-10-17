#include <iostream>

class Life {
    static const int width = 100; // Width of the world
    static const int height = width; // Height of the world

    bool current_world[width][height] = {false}; // The current world
    bool next_world[width][height] = {false}; // The next world

    char border_character = '#';
    char alive_character = '+';
    char dead_character = ' ';

    public:
    void print() {
        // Prints the current world (useful to debug)
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                    std::cout << border_character << ' ';
                } else {
                    if (current_world[x][y]) {
                        std::cout << alive_character << ' ';
                    } else {
                        std::cout << dead_character << ' ';
                    }
                }
            }
            std::cout << std::endl;
        }
    }

    bool get(int x, int y) {
        // Gets the value of the coordinates x, y in the current world.
        return current_world[x][y];
    }

    bool get_next(int x, int y) {
        // Gets the value of the coordinates x, y in the next world.
        return next_world[x][y];
    }

    bool lives(int x, int y) {
        // Determines if a cell will live in the next generation (a.k.a. if it has 2 or 3 neighbours).
        int sum = 0;
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (get(x + dx, y + dy)) {
                    sum += 1;
                }
            }
        }

        return sum == 2 || sum == 3;
    }

    void clear(int x1, int x2, int y1, int y2) {
        // Clears a specific area of the world.
        for (int y = y1; y < y2; ++y) {
            for (int x = x1; x < x2; ++x) {
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

        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                current_world[x][y] = rand() % 2;
            }
        }
    }

    void simulate() {
        // Calculates the next generation and then updates the current one.
        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                next_world[x][y] = lives(x, y);
            }
        }

        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                current_world[x][y] = get_next(x, y);
            }
        }
    }

    void toggle(int x, int y) {
        // Toggles a specific cell.
        current_world[x][y] = !current_world[x][y];
    }
};

int main() {
    Life life;
    life.populate();
    life.print();
    return 0;
}
#include <iostream>

class Life {
    static const int width = 10; // Width of the world
    static const int height = 10; // Height of the world

    bool current_world[width][height] = {false};
    bool next_world[width][height] = {false};

    public:
    void print() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                std::cout << current_world[x][y] << ' ';
            }
            std::cout << std::endl;
        }
    }

    bool get(int x, int y) {
        if (x <= 0 || x >= width || y <= 0 || y >= height) {
            return false;
        } else {
            return current_world[x][y];
        }
    }

    bool dies(int x, int y) {
        int sum = 0;
        for (int dy = -1; dy < 1; dy++) {
            for (int dx = -1; dx < 1; dx++) {
                if (get(x + dx, y + dy)) {
                    sum += 1;
                }
            }
        }

        return sum == 2 || sum == 3;
    }

    void simulate() {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                next_world[x][y] = dies(x, y);
            }
        }

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                current_world[x][y] = next_world[x][y];
            }
        }
    }
};

int main() {
    Life life;
    life.simulate();
    life.print();
    return 0;
}
#include <iostream>
#include "board.h"

bool is_affirmative(const std::string &value) {
    return value == "Y" ||
           value == "y";
}

int main() {
    srand(time(nullptr));
    // TODO: info block

    int height, width, amount, count;
    std::string holder;
    bool player1, player2;
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

    Board board = Board(height, width, amount, player1, player2);

    board.construct();

    bool forced;
    bool winner = false;
    bool won = false;
    int turns = 0;

    int *turns_keeper = new int[width * height];
    int p1_wins = 0;
    int p2_wins = 0;
    int ties = 0;

    for (int i = 0; i < count; i++) {
        forced = board.play(winner, won, turns);

        if (!forced) {
            if (won) {
                if (!winner) {
                    std::cout << "Player one has won after " << turns << " turns." << std::endl;
                    p1_wins += 1;
                } else {
                    std::cout << "Player two has won after " << turns << " turns." << std::endl;
                    p2_wins += 1;
                }
            } else {
                std::cout << "There was a tie after " << turns << " turns." << std::endl;
                ties += 1;
            }

            turns_keeper[turns - 1] += 1;
        } else {
            break;
        }

        board.clean();
    }

    std::cout << "Player one has won " << p1_wins << " times and player two " << p2_wins << " times." << std::endl;
    std::cout << "There were " << ties << " ties." << std::endl;
    std::cout << "Turn statistics: " << std::endl << "Turns : amount" << std::endl;
    for (int i = 0; i < width * height; i++) {
        printf("%5d : %d \n", i + 1, turns_keeper[i]);
    }

    board.deconstruct();

    return 0;
}
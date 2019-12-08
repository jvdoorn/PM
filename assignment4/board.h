/*
 * board.h
 *
 * Headerfile of board.cpp.
 *
 * Last edited on: Sunday December 8th 2019
 */

class Field {
    /**
     * Represents a field on the board.
     */
    public:
    char value = ' '; // Value of the field
    Field *neighbours[8] = {nullptr}; // Its neighbours
};

class Action {
    /**
     * Represents an action so we can undo
     * it.
     */
    public:
    Action(int _x, int _y, Action *_previous);

    int x; // Its x coordinate
    int y; // Its y coordinate
    Action *previous = nullptr; // The action before it
};

class Board {
    /**
     * Represent the board.
     */
    private:
    Field *start = nullptr; // Start of the pointer field (0, 0)
    Action *last_action = nullptr; // The last action

    int width, height, amount; // Width, height and how many on a row
    bool player1, player2; // Whether player 1/2 are played by a human

    char player1char = 'B', player2char = 'W'; // Character for player 1/2

    bool turn = false; // False means its player one's turn
    int turns = 0; // The amount of turns we had in the current game

    int *turns_keeper; // Keep track of how many games took a specific turn count
    int p1_wins = 0, p2_wins = 0, ties = 0; // Player 1/2 wins and ties counters

    /**
     * Returns the amount of filled fields.
     */
    int filled();

    /**
     * Checks if the board is full.
     */
    bool full();

    /**
     * Calculates the score of field in  a given
     * direction.
     */
    static int score(Field *target, int direction);

    /**
     * Check if the given field at x, y has
     * a score high enough in any direction.
     */
    bool check(int x, int y);

    /**
     * Get instructions of the user and acts
     * accordingly.
     */
    void user_controls(int &x, int &y, bool &q, bool &c);

    /**
     * Generates a random move for the computer.
     */
    void computer_controls(int &x, int &y);

    /**
     * Prints the field including an x
     * and y axis with coordinates. Works
     * perfectly up to 1000x1000 fields.
     */
    void print();

    /**
     * Prints the result of a game.
     */
    void print_result(bool won);

    /**
     * Set a specific field on the board
     * to a value using the given x and
     * y coordinate.
     */
    bool set(int x, int y, char value);

    /**
     * Gets a specific field on the board using
     * the given x and y coordinate.
     */
    Field *get(int x, int y);

    /**
     * Save the last move.
     */
    void save(int x, int y);

    /**
     * Undo the last n-moves.
     */
    void undo(int times);

    /**
     * Clears the whole history.
     */
    void deconstruct_history();

    /**
     * Calculate the remaining games.
     */
    long calculate();

    public:
    /**
     * Constructor of the Board class, should
     * be self explanatory.
     */
    Board(int _height, int _width, int _amount, bool _player1, bool _player2);

    /**
     * Constructs the pointer field of the board.
     */
    void construct();

    /**
     * Prints a summary of the set of games and
     * saves the results to a file.
     */
    void print_summary();

    /**
     * Deconstruct the pointer field and history.
     * Also clears some additional variables.
     */
    void deconstruct();

    /**
     * The main function of the game, it
     * handles all the logic and calls
     * functions correspondingly.
     */
    void play();

    /**
     * Cleans the board for a new game.
     */
    void clean();
};
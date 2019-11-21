class Field {
    public:
    char value = ' ';
    Field *neighbours[8] = {nullptr};
};

class Board {
    private:
    Field *start;

    int height;
    int width;
    int amount;

    bool player1;
    bool player2;

    char player1char;
    char player2char;

    bool turn;

    public:
    Board();

    void print();

    void construct();

    bool set(int w, int h, char value);
};
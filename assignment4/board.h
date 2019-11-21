class Field {
    public:
    char value = ' ';
    Field *neighbours[8] = {nullptr};
};

class Board {
    private:
    Field *start = nullptr;

    int height;
    int width;
    int amount;

    bool player1;
    bool player2;

    char player1char = 'W';
    char player2char = 'Z';

    bool turn = false;
    int turns = 0;

    bool full();

    int score(Field* target, int direction);

    bool check(int x, int y);

    public:
    Board(int _height, int _width, int _amount, bool _player1, bool _player2);

    void print();

    void construct();

    bool set(int x, int y, char value);

    Field* get(int x, int y);
};
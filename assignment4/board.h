class Field {
    public:
    char value = ' ';
    Field *neighbours[8] = {nullptr};
};

class Action {
    public:
    Action(int _x, int _y, Action *_previous);
    int x;
    int y;
    Action *previous = nullptr;
};

class Board {
    private:
    Field *start = nullptr;
    Action *last_action = nullptr;

    int height;
    int width;
    int amount;

    bool player1;
    bool player2;

    char player1char = 'B';
    char player2char = 'W';

    bool turn = false;
    int turns = 0;

    bool full();

    int score(Field *target, int direction);

    bool check(int x, int y);

    public:
    Board(int _height, int _width, int _amount, bool _player1, bool _player2);

    void print();

    void construct();

    bool set(int x, int y, char value);

    Field *get(int x, int y);

    void save(int x, int y);

    void undo(int times);

    void user_controls(int &x, int &y, bool &q);

    void computer_controls(int &x, int &y);

    void play();
};
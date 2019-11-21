#include <iostream>

using namespace std;

struct Box {
    int content;
    int *other;
    Box *next;

    void print() {
        cout << content << ", " << *other << endl;

        if (next != nullptr) {
            next->print();
        }
    }
};

void add_box(Box *&first, int i, int j) {
    Box *p = first;
    Box *n = new Box;

    if (p == nullptr) {
        first = n;
    } else {
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = n;
    }

    n->other = new int(j);
    n->next = nullptr;
    n->content = i;
}

void remove_box(Box *&first) {
    if (first != nullptr) {
        Box *p = first->next;
        delete (first);
        first = p;
    }
}

void input(int &i, int &j) {
    cout << "First integer: ";
    cin >> i;
    cout << "Second integer: ";
    cin >> j;
}

int main() {
    Box *first = nullptr;
    char choice;
    int i, j;

    do {
        cout << "Options: [S]top, [A]dd," << endl
             << "         [P]rint, [R]emove" << endl
             << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 's':
            case 'S':
                break;
            case 'a':
            case 'A':
                input(i, j);
                add_box(first, i, j);
                break;
            case 'p':
            case 'P':
                if (first != nullptr) {
                    first->print();
                }
                break;
            case 'r':
            case 'R':
                remove_box(first);
                break;
            default:
                cout << "Wrong choice you moron." << endl;
                break;
        }
    } while (choice != 's' and choice != 'S');
}
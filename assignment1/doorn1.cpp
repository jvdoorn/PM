/*
 * main.cpp
 * Author: Julian van Doorn (2519074)
 *
 * This program is based on the Python version I wrote (together with
 * Tobias Eikelenboom) for PRna.
 *
 * This program aims to provide the functionality described in the
 * assignment called 'Product'. It will ask and check a user's
 * birthday and test them on their math skills. If they fail the math
 * test it will test their art history knowledge.
 */
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

// The current date.
const int YEAR = 2019;
const int MONTH = 9;
const int DAY = 23;

// The birthday
int birth_year;
int birth_month;
int birth_day;

// The difference between today and the birthday
int day_delta;

// First letter of the day they were born
char first_day_letter;
// Second (optional) letter of the day they were born.
char second_day_letter;
// A number corresponding to the day they were born.
int day_number;

// Our two random numbers.
int number1;
int number2;

// The answer to the second question (if needed).
char answer2;

int get_month_length(int y, int m) {
    /*
     * This function returns the length of month m in year y.
     */
    if (m == 2) {
        if (y % 4 == 0) {
            return 29;
        } else {
            return 28;
        }
    } else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 ||
               m == 10 || m == 12) {
        return 31;
    } else {
        return 30;
    }
}

int get_year_length(int y) {
    /*
     * This function returns the length of year y.
     */
    if (y % 4 == 0) {
        return 366;
    } else {
        return 365;
    }
}

int get_month_delta(int year1, int month1, int day1, int year2,
                    int month2, int day2) {
    /*
     * This function returns the difference in months between two
     * dates.
     */
    if (day2 >= day1) {
        return (year2 - year1) * 12 + (month2 - month1);
    } else {
        return (year2 - year1) * 12 + (month2 - month1 - 1);
    }
}

int get_month_delta(int year1, int month1, int day1) {
    /*
     * This function returns the difference in months between the
     * given date and the current date.
     */
    return get_month_delta(year1, month1, day1, YEAR, MONTH, DAY);
}

string get_day_name(int d) {
    /*
     * This function tells us which day corresponds to the remainder
     * of a day difference with reference point 1901-01-01 -> tuesday.
     */
    switch (d) {
        case 0:
            return "tuesday";
        case 1:
            return "wednesday";
        case 2:
            return "thursday";
        case 3:
            return "friday";
        case 4:
            return "saturday";
        case 5:
            return "sunday";
        case 6:
            return "monday";
        default:
            return "???";
    }
}

int get_day_delta(int year1, int month1, int day1, int year2,
                  int month2, int day2) {
    /*
     * This function returns the difference between two dates in days.
     */
    int days = 0;

    for (int y = year1; y < year2; y++) {
        if (y == year1) {
            for (int m = month1; m <= 12; m++) {
                days += get_month_length(y, m);
            }
            days -= day1;
        } else {
            days += get_year_length(y);
        }
    }

    for (int m = 1; m <= month2; m++) {
        if (m == month2) {
            days += day2;
        } else {
            days += get_month_length(year2, m);
        }
    }

    return days;
}


int main() {
    // Output author information.
    cout << "=====================================\n"
            "|This program was written by:       |\n"
            "|Julian van Doorn (s2518074 - 2019) |\n"
            "|                                   |\n"
            "|The Assignment is called: Product  |\n"
            "|                                   |\n"
            "|This program will determine if, and|\n"
            "|if so, what kind of program you can|\n"
            "|do at Leiden University.           |\n"
            "=====================================\n";

    // Get the birth year and check it.
    cout << "What year were you born in? ";
    cin >> birth_year;
    if (YEAR - birth_year < 10 || YEAR - birth_year > 101) {
        cout << "You are too old or young.";
        return 1;
    }

    // Get the birth month and check it.
    cout << "What month were you born in (1-12)? ";
    cin >> birth_month;
    if (birth_month < 1 || birth_month > 12) {
        cout << "That month is invalid.";
        return 1;
    } else if ((YEAR - birth_year == 10 && birth_month > MONTH) ||
               (YEAR - birth_year == 101 && birth_month < MONTH)) {
        cout << "You are too old or young.";
        return 1;
    }

    // Get the birth day and check it.
    cout << "What day were you born on? ";
    cin >> birth_day;
    if (birth_day < 1 ||
        birth_day > get_month_length(birth_year, birth_month)) {
        cout << "That day is invalid.";
        return 1;
    } else if ((YEAR - birth_year == 10 && birth_month == MONTH &&
                birth_day > DAY) ||
               (YEAR - birth_year == 101 and birth_month == MONTH and
                birth_day <= DAY)) {
        cout << "You are too old or young.";
        return 1;
    }

    // Tell the user how old they are (in years/months and in just
    // months).
    cout << "You are " << floor(
            get_month_delta(birth_year, birth_month, birth_day) / 12)
         << " years and "
         << get_month_delta(birth_year, birth_month, birth_day) % 12
         << " months old.\n";
    cout << "Or we could say that you are just "
         << get_month_delta(birth_year, birth_month, birth_day)
         << " months old.\n";

    // Check if they have their birthday.
    if (birth_month == MONTH && birth_day == DAY) {
        cout << "Happy b-day!\n";
    } else if (birth_day == DAY) {
        cout << "Happy m-day!\n";
    }

    // Calculate the difference in days between 1901-01-01 and their
    // birthday.
    day_delta = get_day_delta(1901, 1, 1, birth_year, birth_month,
                              birth_day);

    // Get the first letter of the day the user was born.
    cout << "Enter the first letter of the day you were born on "
            "(m, t, etc.): ";
    cin >> first_day_letter;

    // Check if it could be multiple days (t/s).
    if (first_day_letter == 't' || first_day_letter == 'T') {
        // Get the second letter of the day the user was born.
        cout << "Enter the second letter of the day you were born on "
                "(h/u): ";
        cin >> second_day_letter;

        // Match it with a day (number).
        if (second_day_letter == 'h' || second_day_letter == 'H') {
            day_number = 2; // Thursday
        } else if (second_day_letter == 'u' ||
                   second_day_letter == 'U') {
            day_number = 0; // Tuesday
        } else {
            cout << "Invalid day letters.";
            return 1;
        }
    } else if (first_day_letter == 's' || first_day_letter == 'S') {
        // Get the second letter of the day the user was born.
        cout << "Enter the second letter of the day you were born on "
                "(a/u): ";
        cin >> second_day_letter;

        // Match it with a day (number).
        if (second_day_letter == 'a' || second_day_letter == 'A') {
            day_number = 4; // Saturday
        } else if (second_day_letter == 'u' ||
                   second_day_letter == 'U') {
            day_number = 5; // Sunday
        } else {
            cout << "Invalid day letters.";
            return 1;
        }
    } else {
        // Else match the first letter with a day.
        if (first_day_letter == 'm' || first_day_letter == 'M') {
            day_number = 6; // Monday
        } else if (first_day_letter == 'w' ||
                   first_day_letter == 'W') {
            day_number = 1; // Wednesday
        } else if (first_day_letter == 'f' ||
                   first_day_letter == 'F') {
            day_number = 3; // Friday
        } else {
            cout << "Invalid day letter.";
            return 1;
        }
    }

    // Check if the user inputted the right day.
    if (day_delta % 7 != day_number) {
        // This print statement was mostly for debug purposes.
        cout << "Wrong. You were born on "
             << get_day_name(day_delta % 7) << ".";
        return 1;
    }

    // Initialize a random number generator.
    srand(time(0));
    // Generate two random numbers.
    number1 = rand() % 10000 + 1;
    number2 = rand() % (10000 - number1) + 1;
    // There is a 10% chance of number1 being zero.
    if (rand() % 10 + 1 == 1) {
        number1 = 0;
    }

    int answer;

    // Ask the user about the product.
    cout << "What is the product of " << number1 << " and " << number2
         << "? ";
    cin >> answer;

    // Check if the answer was correct.
    if (0.9 * number1 * number2 <= answer &&
        answer <= 1.1 * number1 * number2) {
        cout << "Correct! You can start an exact program.";
        return 0;
    }

    // If it was wrong we shall test their art history knowledge.
    cout << "You were wrong.. we will now test your art history "
            "knowledge.\n";

    // Check if the user is 30.
    if (get_month_delta(birth_year, birth_month, birth_day) / 12 >=
        30) {
        cout << "The Nachtwacht was painted by:\n"
                "a) Rembrand;\n"
                "b) Shirley Temple;\n"
                "c) James Bond;\n"
                "d) Trick question: The Nachtwacht is a peanut butter"
                " brand.\n"
                "Enter a/b/c/d: ";
    } else {
        cout << "On average, Van Gogh had:\n"
                "a) one ear;\n"
                "b) two ears;\n"
                "c) three ears;\n"
                "d) no ears.\n"
                "Enter a/b/c/d: ";
    }

    // Get the second answer.
    cin >> answer2;
    // Check if it was correct.
    if (answer2 == 'a' || answer2 == 'A') {
        cout << "Correct! You can start a art history program.";
        return 0;
    } else {
        cout << "Wrong! You may not start with anything.";
        return 1;
    }
}
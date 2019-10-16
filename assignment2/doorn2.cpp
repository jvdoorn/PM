/*
 * doorn2.cpp
 * Author: Julian van Doorn (2518074)
 * October 10th 2019
 *
 * This program aims to provide the functionality described in assignment 2 'Keurig'. It will ask the user to input a
 * tab-width and the file they want to check and where the result should go to. The program will remove all comments
 * made using // and indent it properly. Additionally it will look for Lychrel numbers.
 */

#include <iostream>
#include <fstream>

bool is_number(char c) {
    /*
     * Checks if a character is a number.
     */
    return ('0' <= c && c <= '9');
}

int reverse_int(int n) {
    /*
     * Reverses an integer.
     */
    int reversed_n = 0, remainder;
    while (n != 0) {
        // The remainder is the last digit in the number.
        remainder = n % 10;

        // Shift all digits in the reversed number to the right.
        reversed_n *= 10;
        // Add the remainder to the reversed number.
        reversed_n += remainder;
        // Divide the original number by 10 (floating point will be ignored).
        n /= 10;
    }
    // Return the reversed number.
    return reversed_n;
}

int lychrel(int n) {
    /*
     * Tries to compute a palindrome for n. If it fails to do so before reaching INT_MAX we will assume that it is a
     * Lychrel number. If the return is < 0 we reached INT_MAX, if the return is > 0 then that is the amount of
     * iterations it took to find a palindrome.
     */
    int rn, j = 1;
    while (true) {
        // Get the reverse of N.
        rn = reverse_int(n);
        if (n == rn) {
            // N is equal to RN thus a palindrome.
            return j;
        } else {
            // See if we can add N and RN together without exceeding INT_MAX.
            if (n < INT_MAX - rn) {
                // If we can add them we do so.
                n += rn;
            } else {
                // If not we return j negated (we haven't found a palindrome).
                return -j;
            }
        }
        // Increase j with each iteration.
        j++;
    }
}

int main() {
    std::cout << "=============================================" << std::endl
              << "|This program is written by:                |" << std::endl
              << "|Julian van Doorn (s2518074 - 2019)         |" << std::endl
              << "|                                           |" << std::endl
              << "|The assignment is called: 'Keurig'         |" << std::endl
              << "|                                           |" << std::endl
              << "|It will ask you to enter a input filename, |" << std::endl
              << "|an output filename and a tab-width. It will|" << std::endl
              << "|then format the input file and export it to|" << std::endl
              << "|the output file.                           |" << std::endl
              << "=============================================" << std::endl;

    int d = 0; // The current depth
    int tab; // The width of a tab

    char previous; // The previous character
    char current; // The current character

    int total_in = 1; // Total amount of characters that have been read.
    int total_out = 0; // Total amount of characters that have been written.

    bool comment = false; // Checks if we are in a comments currently.

    std::string number; // A number if we find one (Lychrel).
    int iterations = 0; // Biggest amount of iterations for the Lychrel numbers.
    int integer = 0; // The integer corresponding to those iterations.

    std::string input_file; // The input file.
    std::cout << "Which file would you like to parse: ";
    std::cin >> input_file;
    std::ifstream input(input_file); // Input stream
    // Check if we can read the file (a.k.a. does it exist?).
    if (input.fail()) {
        std::cout << "The file does not exist." << std::endl;
        return 1;
    }

    std::string output_file; // the output file.
    std::cout << "Where would you like the output to go: ";
    std::cin >> output_file;
    std::ofstream output(output_file); // Output stream

    std::cout << "What tab with would you like to use: ";
    std::cin >> tab;

    // Start parsing the file
    while (input.get(current)) {
        total_in += 1; // We've read an additional character.

        // Check if we are currently in a comment.
        if (comment) {
            // Linebreaks end comments.
            if (current == '\n') {
                comment = false;
                output.put('\n');
                total_out += 1;
                previous = '\n';
                continue;
            } else {
                // Skip the character
                continue;
            }
        }

        // Check if we are at the start of a comment
        if (previous == '/') {
            if (current == '/') {
                comment = true;
                continue;
            } else {
                output.put(previous);
                total_out += 1;
            }
        }

        // Check if we just had a newline
        if (previous == '\n') {
            if (current == ' ' || current == '\t') {
                // Skip all spaces/tabs after a newline.
                continue;
            } else {
                // After removing all spaces/tabs insert our own.
                int indent;
                if (current == '}') {
                    indent = tab * (d - 1);
                } else {
                    indent = tab * d;
                }
                for (int i = 0; i < indent; i++) {
                    output.put(' ');
                    total_out += 1;
                }
            }
        }

        if (current == '{') {
            // { increase indent level
            d += 1;
        } else if (current == '}') {
            // { decrease indent level
            d -= 1;
        } else if (is_number(current)) {
            // numbers are added to the current number string
            number += current;
        } else if (is_number(previous)) {
            // we just had a number, now we need to parse it.
            int i = std::stoi(number);
            int l = lychrel(i);

            if (l < 0) {
                std::cout << "Found the number: " << i
                          << " it does not become a palindrome before reaching INT_MAX after " << -l << " iterations."
                          << std::endl;
                if (-l > iterations) {
                    iterations = -l;
                    integer = i;
                }
            } else {
                std::cout << "Found the number: " << i << " it becomes a palindrome after " << l << " iterations."
                          << std::endl;
                if (l > iterations) {
                    iterations = l;
                    integer = i;
                }
            }

            number = "";
        }

        if (current != '/') {
            output.put(current);
            total_out += 1;
        }
        previous = current;
    }

    // Close in and output.
    input.close();
    output.close();

    // give a summary
    std::cout << "We have read " << total_in << " and written " << total_out << " characters." << std::endl;
    if (iterations != 0) {
        std::cout << "The biggest amount of iterations for Lychrel was " << iterations << " for the integer " << integer
                  << std::endl;
    } else {
        std::cout << "No integers were tested if they are Lychrel numbers.";
    }

    return 0;
}

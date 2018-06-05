#include <iostream>
#include <ios>
#include <string>
#include <math.h>

#define REV_MAP_SIZE 100
char rev[REV_MAP_SIZE];

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);

    rev['A'] = 'A';
    rev['E'] = '3';
    rev['H'] = 'H';
    rev['I'] = 'I';
    rev['J'] = 'L';
    rev['L'] = 'J';
    rev['M'] = 'M';
    rev['O'] = 'O';
    rev['S'] = '2';
    rev['T'] = 'T';
    rev['U'] = 'U';
    rev['V'] = 'V';
    rev['W'] = 'W';
    rev['X'] = 'X';
    rev['Y'] = 'Y';
    rev['Z'] = '5';
    rev['1'] = '1';
    rev['2'] = 'S';
    rev['3'] = 'E';
    rev['5'] = 'Z';
    rev['8'] = '8';

    std::string line;
    while (getline(std::cin, line), !std::cin.eof()) {
        const unsigned long long len = line.length();
        unsigned long long mid;
        auto is_palindrome = true, is_mirrored = true;
        if (len & 1) {
            mid = static_cast<unsigned long long>(floor(len / 2));
        } else {
            mid = len / 2;
        }

        for (unsigned long long i = 0; i < mid && (is_palindrome || is_mirrored); ++i) {
            if (is_palindrome && line[i] != line[len - i - 1]) {
                is_palindrome = false;
            }

            if (is_mirrored && line[i] != rev[line[len - i - 1]]) {
                is_mirrored = false;
            }
        }

        if (is_mirrored && len & 1) {
            is_mirrored = line[mid] == rev[line[mid]];
        }

        if (!is_palindrome && !is_mirrored) {
            printf("%s -- is not a palindrome.\n\n", line.c_str());
        } else if (!is_palindrome && is_mirrored) {
            printf("%s -- is a mirrored string.\n\n", line.c_str());
        } else if (is_palindrome && !is_mirrored) {
            printf("%s -- is a regular palindrome.\n\n", line.c_str());
        } else if (is_palindrome && is_mirrored) {
            printf("%s -- is a mirrored palindrome.\n\n", line.c_str());
        }
    }

    return 0;
}

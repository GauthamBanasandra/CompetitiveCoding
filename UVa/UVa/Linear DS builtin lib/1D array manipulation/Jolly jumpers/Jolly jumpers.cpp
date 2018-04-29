#include <iostream>
#include <sstream>
#include <ios>
#include <bitset>
#include <string>
#include <math.h>

#define MAX_N 3010

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);

    int n;
    long long i, j;
    unsigned long long v;
    std::bitset<MAX_N> b;
    std::string line;
    while (getline(std::cin, line), !std::cin.eof()) {
        auto is_jolly = false;
        b.reset();
        std::istringstream buf(line);

        buf >> n;
        if (n == 1) {
            is_jolly = true;
        } else {
            buf >> i;
            for (auto k = 0; k < n - 1; ++k) {
                buf >> j;
                v = abs(i - j);
                if (v < MAX_N) {
                    b[v] = true;
                }

                i = j;
            }
        }

        is_jolly = true;
        for (auto k = 1; k < n; ++k) {
            if (!b[k]) {
                is_jolly = false;
                break;
            }
        }

        printf("%s\n", is_jolly ? "Jolly" : "Not jolly");
    }

    return 0;
}


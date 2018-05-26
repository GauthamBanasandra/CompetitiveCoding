//
// Created by gauth on 14-04-2018.
//

// WA

#include <string>
#include <iostream>
#include <vector>
#include <cassert>

bool CutAndCountEqual(const std::vector<std::string> &waffle, int r, int c, int R, int C) {
    auto q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (i <= r && j <= c) {
                ++q1;
            } else if (i <= r && j > c) {
                ++q2;
            } else if (i > r && j <= c) {
                ++q3;
            } else if (i > r && j > c) {
                ++q4;
            } else {
                assert(false);
            }
        }
    }

    return q1 == q2 == q3 == q4;
}

bool IsPossible(const std::vector<std::string> &waffle, int R, int C) {
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (CutAndCountEqual(waffle, i, j, R, C)) {
                printf("(%d, %d)\n", i, j);
                return true;
            }
        }
    }

    return false;
}

int main() {
    int t, r, c, h, v;
    std::string waffle_row;
    std::vector<std::string> waffle;

    std::cin >> t;
    for (int _t = 1; _t <= t; ++_t) {
        std::cin >> r >> c >> h >> v;
        waffle.clear();
        for (int i = 0; i < r; ++i) {
            std::cin >> waffle_row;
            waffle.emplace_back(waffle_row);
        }

        --r;
        --c;
        printf("Case #%d: %s\n", _t, IsPossible(waffle, r, c) ? "POSSIBLE" : "IMPOSSIBLE");
    }

    return 0;
}
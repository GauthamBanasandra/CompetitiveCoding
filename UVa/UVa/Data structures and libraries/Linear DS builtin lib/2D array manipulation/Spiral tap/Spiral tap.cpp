#include <stdio.h>
#include <vector>

#define SZ_MAX 99999

using big_int = unsigned long long;

struct Cartesian {
    big_int line;
    big_int col;
};

int main(int argc, char *argv[]) {
    const auto sz_max = static_cast<big_int>(SZ_MAX) * static_cast<big_int>(SZ_MAX);

    std::vector<Cartesian> grid(sz_max);
    big_int r = 3, i = 1, k = 0;
    big_int l, c;
    l = c = (SZ_MAX >> 1) + 1;

    grid[i].line = l;
    grid[i++].col = c;

    while (i < sz_max) {
        ++l;
        ++c;
        k = r;
        while (--k) {
            grid[i].line = l;
            grid[i++].col = --c;
        }

        k = r;
        while (--k) {
            grid[i].line = --l;
            grid[i++].col = c;
        }

        k = r;
        while (--k) {
            grid[i].line = l;
            grid[i++].col = ++c;
        }

        k = r;
        while (--k) {
            grid[i].line = ++l;
            grid[i++].col = c;
        }

        r += 2;
    }

    big_int sz, p;
    while (scanf("%llu %llu\n", &sz, &p), sz || p) {
        if (!sz || !p) {
            printf("Line = 0, column = 0.\n");
            continue;
        }

        const auto *pos = &grid[p];
        const auto t = (SZ_MAX - sz) >> 1;
        printf("Line = %llu, column = %llu.\n", pos->line - t, pos->col - t);
    }

    return 0;
}

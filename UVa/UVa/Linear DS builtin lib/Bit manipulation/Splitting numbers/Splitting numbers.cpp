#include <stdio.h>

int main(int argc, char *argv[]) {
    int n;
    auto a = 0, b = 0, c = 0, i = 0;
    while (scanf("%d", &n), n) {
        a = b = c = i = 0;
        while (n) {
            if (n & 1) {
                ++i;
                if (i & 1) {
                    a |= 1 << c;
                } else {
                    b |= 1 << c;
                }
            }

            ++c;
            n = n >> 1;
        }

        printf("%d %d\n", a, b);
    }

    return 0;
}

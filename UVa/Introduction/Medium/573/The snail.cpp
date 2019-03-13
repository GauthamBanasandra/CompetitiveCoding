#include <stdio.h>
#include <ios>

#define COLS 4
#define INITIAL_HEIGHT 0
#define DISTANCE_CLIMBED 1
#define HEIGHT_AFTER_CLIMBING 2
#define HEIGHT_AFTER_SLIDING 3

double state[COLS];

int main() {
    std::ios::sync_with_stdio(false);

    double h, u, d, f;
    while (scanf("%lf%lf%lf%lf", &h, &u, &d, &f), h != 0.0) {
        int day = 1;
        for (int i = 0; i < COLS; ++i) {
            state[i] = 0.0;
        }

        while (state[HEIGHT_AFTER_SLIDING] >= 0 && state[HEIGHT_AFTER_CLIMBING] <= h) {
            if (day == 1) {
                state[INITIAL_HEIGHT] = 0;
                state[DISTANCE_CLIMBED] = state[HEIGHT_AFTER_CLIMBING] = u;
                state[HEIGHT_AFTER_SLIDING] = u - d;
                f = u * f / 100.0;
            } else {
                state[INITIAL_HEIGHT] = state[HEIGHT_AFTER_SLIDING];
                if (state[DISTANCE_CLIMBED] - f <= 0) {
                    state[DISTANCE_CLIMBED] = 0;
                } else {
                    state[DISTANCE_CLIMBED] -= f;
                }
                state[HEIGHT_AFTER_CLIMBING] = state[INITIAL_HEIGHT] + state[DISTANCE_CLIMBED];
                state[HEIGHT_AFTER_SLIDING] = state[HEIGHT_AFTER_CLIMBING] - d;
            }

            /*for (int i = 0; i < COLS; ++i)
            {
            printf("%lf ", state[i]);
            }

            printf("\n");*/

            if (state[HEIGHT_AFTER_SLIDING] < 0 || state[HEIGHT_AFTER_CLIMBING] > h) {
                break;
            }

            ++day;
        }

        if (state[HEIGHT_AFTER_CLIMBING] > h) {
            printf("success on day %d\n", day);
        } else {
            printf("failure on day %d\n", day);
        }
    }
}
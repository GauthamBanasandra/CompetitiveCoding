#include <stdio.h>
#include <ios>

#define MAX_SIZE 3
int salaries[MAX_SIZE];

int main() {
    std::ios::sync_with_stdio(false);

    int T, c = 1;
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < MAX_SIZE; ++i) {
            scanf("%d", &salaries[i]);
        }

        std::sort(std::begin(salaries), std::end(salaries));
        printf("Case %d: %d\n", c++, salaries[MAX_SIZE / 2]);
    }
}
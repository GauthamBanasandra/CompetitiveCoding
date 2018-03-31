#include <stdio.h>
#include <math.h>
#include <ios>

typedef unsigned long long big_int;
typedef long double big_dbl;

inline bool IsInt(big_dbl n) {
    return !(n - trunc(n));
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);

    big_int n, s, d;
    scanf("%llu", &n);
    while (n--) {
        scanf("%llu%llu", &s, &d);
        if (s < d) {
            printf("impossible\n");
            continue;
        }

        const big_dbl a = (s + d) / 2.0;
        const big_dbl b = (s - d) / 2.0;
        if (!IsInt(a) || !IsInt(b)) {
            printf("impossible\n");
            continue;
        }

        printf("%lld %lld\n", static_cast<big_int>(a), static_cast<big_int>(b));
    }

    return 0;
}

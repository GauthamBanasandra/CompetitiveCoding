#include <stdio.h>
#include <ios>
#include <math.h>

int main() {
  std::ios::sync_with_stdio(false);

  int m, n;
  unsigned long long k;
  while (scanf("%d%d\n", &m, &n), m || n) {
    if (!m || !n) {
      k = 0;
    } else if (m == 1) {
      k = n;
    } else if (n == 1) {
      k = m;
    } else if (m == 2) {
      if (n & 1) {
        k = n + 1;
      } else if (!(n % 4)) {
        k = n;
      } else {
        k = n + 2;
      }
    } else if (n == 2) {
      if (m & 1) {
        k = m + 1;
      } else if (!(m % 4)) {
        k = m;
      } else {
        k = m + 2;
      }
    } else {
      k = static_cast<int>(ceil(m * n / 2.0));
    }

    printf("%llu knights may be placed on a %d row %d column board.\n", k, m, n);
  }
}

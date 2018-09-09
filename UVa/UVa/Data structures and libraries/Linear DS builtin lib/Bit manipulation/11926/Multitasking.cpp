// WA

#include <stdio.h>
#include <bitset>

#define TIMELINE_LEN 1000001
using big_int = long long;

std::bitset<2 * TIMELINE_LEN> timeline;

int main(int argc, char *argv[]) {
  int n, m, start, end, interval;
  while (scanf("%d %d\n", &n, &m), n || m) {
    timeline.reset();
    auto conflict = false;
    while (n) {
      --n;
      scanf("%d %d\n", &start, &end);
      // Need to figure out why storing the bits from 2* works.
      for (auto i = 2 * start + 1; i <= 2 * end; ++i) {
        if (timeline.test(i)) {
          conflict = true;
          break;
        }

        timeline.set(i, true);
      }
    }

    while (m) {
      --m;
      scanf("%d %d %d\n", &start, &end, &interval);
      do {
        for (auto i = 2 * start + 1; i <= 2 * end; ++i) {
          if (timeline.test(i)) {
            conflict = true;
            break;
          }

          timeline.set(i, true);
        }

        start += interval;
        end += interval;
      } while (end < TIMELINE_LEN);
    }

    printf("%s\n", conflict ? "CONFLICT" : "NO CONFLICT");
  }

  return 0;
}

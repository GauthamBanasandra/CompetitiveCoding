#include <stdio.h>
#include <ios>
#include <vector>
#include <string>

#define CARD_CHAR_LEN 3
#define ASCII_2 50
#define ASCII_9 57
namespace what_is_the_card {
char card[CARD_CHAR_LEN];
}

using namespace what_is_the_card;

int main() {
  std::ios::sync_with_stdio(false);

  unsigned long long test_cases, c = 1;
  scanf("%llu", &test_cases);
  std::vector<std::string> rem(27);
  std::vector<std::string> top25(25);

  while (test_cases--) {
    for (auto i = 0; i < 27; ++i) {
      scanf("%s", card);
      rem[i] = card;
    }

    for (auto i = 0; i < 25; ++i) {
      scanf("%s", card);
      top25[i] = card;
    }

    auto y = 0, top = 26;

    for (auto i = 0; i < 3; ++i) {
      auto x = ASCII_2 <= rem[top][0] && rem[top][0] <= ASCII_9 ? rem[top][0] - '0' : 10;
      y += x;
      --top;
      top -= 10 - x;
    }

    printf("Case %llu: %s\n", c++, y - 1 <= top ? rem[y - 1].c_str() : top25[y - top - 2].c_str());
  }
}
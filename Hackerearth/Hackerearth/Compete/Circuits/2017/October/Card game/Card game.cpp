#include <stdio.h>
#include <vector>

using big_int = unsigned long long;

int main(int argc, char *argv[]) {
  big_int n, m, w, max_w = 0, money = 0;
  scanf("%llu", &n);

  std::vector<big_int> first_cards(n);
  for (auto &card : first_cards) {
    scanf("%llu", &w);
    card = w;
  }

  scanf("%llu", &m);
  for (big_int i = 0; i < m; ++i) {
    scanf("%llu", &w);
    if (w > max_w) {
      max_w = w;
    }
  }

  for (const auto &card : first_cards) {
    if (card <= max_w) {
      money += max_w - card + 1;
    }
  }

  printf("%llu\n", money);
  return 0;
}

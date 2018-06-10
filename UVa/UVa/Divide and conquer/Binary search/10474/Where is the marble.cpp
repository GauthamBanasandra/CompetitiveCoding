//
// Created by Gautham Banasandra on 08/06/18.
//

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iostream>

void Print(const std::vector<int> &marbles);

int main() {
  std::ios::sync_with_stdio(false);

  int marble;
  std::vector<int> marbles;
  std::unordered_map<int, std::size_t> marble_i;

  for (std::size_t n = 0, q = 0, c = 1; std::cin >> n >> q, n || q; ++c) {
    marble_i.clear();
    marbles.clear();
    marbles.reserve(n);

    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> marble;
      marbles.emplace_back(marble);
    }

    std::sort(marbles.begin(), marbles.end());

    for (std::size_t i = 0; i < marbles.size(); ++i) {
      marble = marbles[i];
      if (marble_i.find(marble) == marble_i.end()) {
        marble_i[marble] = i + 1;
      }
    }

    printf("CASE# %zu:\n", c);
    for (std::size_t i = 0; i < q; ++i) {
      std::cin >> marble;
      if (marble_i.find(marble) == marble_i.end()) {
        printf("%d not found\n", marble);
        continue;
      }

      printf("%d found at %ld\n", marble, marble_i[marble]);
    }
  }

  return 0;
}
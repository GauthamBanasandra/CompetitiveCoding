//
// Created by Gautham Banasandra on 19/06/18.
//

#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

using ull = unsigned long long;

void Print(const std::vector<ull> &numbers);
ull Pow(ull base, ull exponent) {
  ull power = 1;

  for (ull i = 0; i < exponent; ++i) {
    power *= base;
  }

  return power;
}

std::vector<ull> GetC23() {
  std::vector<ull> c23;

  c23.reserve(1000);
  for (int j = 0; j <= 31; ++j) {
    for (int i = 0; i <= 31; ++i) {
      const auto value = Pow(2, i) * Pow(3, j);
      if (value > Pow(2, 31)) {
        continue;
      }

      c23.emplace_back(value);
    }
  }

  std::sort(c23.begin(), c23.end());
  return c23;
}

int main() {
  std::ios::sync_with_stdio(false);

  ull n;
  auto c23 = GetC23();
  while (std::cin >> n, n) {
    auto m = std::lower_bound(c23.begin(), c23.end(), n);
    std::cout << *m << std::endl;
  }

  return 0;
}
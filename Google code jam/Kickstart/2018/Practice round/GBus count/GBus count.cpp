//
// Created by gauth on 24-02-2018.
//

#include <iostream>
#include <vector>

using ui = unsigned int;

int main() {
  ui t, n, p, a, b, city;
  std::vector<std::pair<ui, ui>> cities_covered;

  std::cin >> t;
  for (ui c = 1; c <= t; ++c) {
    cities_covered.clear();
    std::cin >> n;

    for (ui i = 0; i < n; ++i) {
      std::cin >> a >> b;
      cities_covered.emplace_back(a, b);
    }

    std::cin >> p;
    printf("Case #%u:", c);
    while (p--) {
      ui gbus_count = 0;
      std::cin >> city;
      for (auto bus : cities_covered) {
        if ((bus.first <= city) && (city <= bus.second)) {
          ++gbus_count;
        }
      }

      printf(" %u", gbus_count);
    }

    std::cout << std::endl;
  }

  return 0;
}
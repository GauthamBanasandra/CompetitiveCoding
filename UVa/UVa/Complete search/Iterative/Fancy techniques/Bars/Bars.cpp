//
// Created by gauth on 24-02-2018.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using ui = unsigned int;
using ull = unsigned long long;

int main() {
  ui t, n, p, c;
  ull len, sum;
  std::string line;
  std::vector<ull> bars;

  std::cin >> t;
  while (t--) {
    bars.clear();

    std::cin >> n;
    std::cin >> p;
    std::cin.ignore();

    std::getline(std::cin, line);
    std::istringstream tokenizer(line);
    while (tokenizer >> len) {
      bars.emplace_back(len);
    }

    auto possible = false;
    for (ull i = 0; i < (1 << p); ++i) {
      auto j = i;
      sum = c = 0;
      while (j) {
        if (j & 1) {
          sum += bars[c];
        }

        ++c;
        j >>= 1;
      }

      if (sum == n) {
        possible = true;
        break;
      }
    }

    std::cout << (possible ? "YES" : "NO") << std::endl;
  }

  return 0;
}
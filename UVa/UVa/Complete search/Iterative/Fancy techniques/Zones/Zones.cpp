//
// Created by gauth on 01-03-2018.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using ui = unsigned int;
using ull = unsigned long long;

struct CommonTowers {
  CommonTowers() : n_towers(0), towers(0), coverage(0) {}

  ui n_towers;
  ull towers;
  ull coverage;
};

ui count_1(ull n) {
  ui one = 0;
  while (n) {
    if (n & 1) {
      ++one;
    }

    n >>= 1;
  }

  return one;
}

int main() {
  ui n, p, m, t = 0;
  ull c;
  std::string line;
  std::vector<ull> coverage;
  std::vector<CommonTowers> common_towers;
  std::vector<std::pair<ull, ull>> towers_coverage;

  while (true) {
    std::cin >> n;
    std::cin >> p;
    if (n == 0 && p == 0) {
      break;
    }

    coverage.clear();
    common_towers.clear();
    towers_coverage.clear();

    for (ui i = 0; i < n; ++i) {
      std::cin >> c;
      coverage.emplace_back(c);
    }

    std::cin >> m;
    std::cin.ignore();
    for (ui i = 0; i < m; ++i) {
      std::getline(std::cin, line);
      std::istringstream tokenizer(line);
      CommonTowers ct;

      tokenizer >> ct.n_towers;
      for (ui j = 0; j < ct.n_towers; ++j) {
        tokenizer >> c;
        ct.towers |= (1 << (c - 1));
      }

      tokenizer >> ct.coverage;
      common_towers.emplace_back(ct);
    }

    for (ull i = 0; i < (1 << n); ++i) {
      if (count_1(i) != p) {
        continue;
      }

      ull total_coverage = 0;
      for (int j = 0; j < n; ++j) {
        if (i & (1 << j)) {
          total_coverage += coverage[j];
        }
      }

      for (const auto &ct : common_towers) {
        auto n_common_towers = count_1(i & ct.towers);
        if (n_common_towers) {
          total_coverage -= (n_common_towers - 1) * ct.coverage;
          // Referred to https://github.com/justadreamer/uva-solutions/blob/master/uva01047/uva01047.cpp#L82
        }
      }

      towers_coverage.emplace_back(i, total_coverage);
    }

    ull max_i = 0, max = towers_coverage[0].second;
    for (ull i = 1; i < towers_coverage.size(); ++i) {
      if (towers_coverage[i].second > max) {
        max = towers_coverage[i].second;
        max_i = i;
      } else if (towers_coverage[i].second == max) {
        for (ui j = 0; j < n; ++j) {
          if ((towers_coverage[i].first & (1 << j)) && !(towers_coverage[max_i].first & (1 << j))) {
            max = towers_coverage[i].second;
            max_i = i;
            break;
          } else if (!(towers_coverage[i].first & (1 << j)) && (towers_coverage[max_i].first & (1 << j))) {
            break;
          }
        }
      }
    }

    printf("Case Number  %u\n", ++t);
    printf("Number of Customers: %llu\n", towers_coverage[max_i].second);
    printf("Locations recommended:");

    for (ui i = 0; i < n; ++i) {
      if (towers_coverage[max_i].first & (1 << i)) {
        std::cout << " " << (i + 1);
      }
    }

    std::cout << std::endl << std::endl;
  }

  return 0;
}
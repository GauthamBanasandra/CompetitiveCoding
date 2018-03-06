//
// Created by gauth on 05-03-2018.
//

// Referred to https://www.redgreencode.com/when-not-to-simulate-a-game-uva-11553/

#include <vector>
#include <iostream>
#include <algorithm>

using ui = unsigned int;
using ll = long long;
using vll = std::vector<ll>;

void Print(const std::vector<vll> &grid);

ll Sum(const std::vector<vll> &grid, const std::vector<ll> &numbers) {
  ll sum = 0;
  for (ui i = 0; i < numbers.size(); ++i) {
    sum += grid[i][numbers[i]];
  }

  return sum;
}

ll GetOptimalSum(const std::vector<vll> &grid, ui n) {
  std::vector<ll> indices;
  for (ui i = 0; i < n; ++i) {
    indices.emplace_back(i);
  }

  ll min_sum = 0;
  auto min_sum_init = false;
  do {
    if (!min_sum_init) {
      min_sum = Sum(grid, indices);
      min_sum_init = true;
    } else {
      auto sum = Sum(grid, indices);
      if (sum < min_sum) {
        min_sum = sum;
      }
    }
  } while (std::next_permutation(indices.begin(), indices.end()));

  return min_sum;
}

int main() {
  ui t, n;
  std::cin >> t;
  while (t--) {
    std::cin >> n;

    std::vector<vll> grid(n);
    for (ui i = 0; i < n; ++i) {
      grid[i] = vll(n);
      for (ui j = 0; j < n; ++j) {
        std::cin >> grid[i][j];
      }
    }

    std::cout << GetOptimalSum(grid, n) << std::endl;
  }

  return 0;
}
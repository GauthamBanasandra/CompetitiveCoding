//
// Created by gauth on 05-03-2018.
//

#include <vector>
#include <iostream>

using ui = unsigned int;
using ll = long long;
using vll = std::vector<ll>;

void Print(const std::vector<vll> &grid) {
  for (std::size_t i = 0; i < grid.size(); ++i) {
    for (std::size_t j = 0; j < grid.size(); ++j) {
      std::cout << grid[i][j] << " ";
    }

    std::cout << std::endl;
  }
}
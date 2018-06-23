//
// Created by Gautham Banasandra on 23/06/18.
//

#include <vector>
#include <iostream>

void Print(const std::vector<std::vector<long>> &heights_diagonal) {
  for (const auto &heights:heights_diagonal) {
    for (const auto &height: heights) {
      std::cout << height << " ";
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
}
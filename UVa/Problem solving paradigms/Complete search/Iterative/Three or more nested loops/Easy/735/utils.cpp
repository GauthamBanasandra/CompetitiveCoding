//
// Created by gauth on 20-01-2018.
//

#include <vector>
#include <iostream>

void Print(const std::vector<int> &nums) {
  for (const auto n : nums) {
    std::cout << n << std::endl;
  }

  std::cout << std::endl;
}
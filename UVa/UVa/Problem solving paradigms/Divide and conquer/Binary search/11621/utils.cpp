//
// Created by Gautham Banasandra on 19/06/18.
//

#include <vector>
#include <iostream>

using ull = unsigned long long;

void Print(const std::vector<ull> &numbers) {
  for (const auto number : numbers) {
    std::cout << number << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Size : " << numbers.size();
}
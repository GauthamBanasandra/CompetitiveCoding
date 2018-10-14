//
// Created by gauth on 03-07-2018.
//

#include <iostream>
#include <vector>

void Print(const std::vector<int> &elements) {
  for (const auto element : elements) {
    std::cout << element << " ";
  }

  std::cout << std::endl;
}

void Print(const std::vector<std::vector<int>> &matrix) {
  for (const auto &row : matrix) {
    for (int element : row) {
      std::cout << element << " ";
    }
    std::cout << std::endl;
  }
}
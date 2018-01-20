//
// Created by gauth on 20-01-2018.
//

#include <vector>
#include <iostream>

void Print(const std::vector<int> &subset) {
  for (int item : subset) {
    std::cout << item << " ";
  }

  std::cout << std::endl;
}

void Print(const std::vector<std::string> &subsets) {
  for (const auto &str: subsets) {
    std::cout << str << std::endl;
  }
}
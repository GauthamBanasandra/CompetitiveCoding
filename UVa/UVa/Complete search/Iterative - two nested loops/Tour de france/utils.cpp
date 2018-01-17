//
// Created by gauth on 17-01-2018.
//

#include <iostream>
#include <vector>

void print(const std::vector<float> &drive_ratio) {
  for (const auto &d:drive_ratio) {
    std::cout << d << " ";
  }

  std::cout << std::endl;
}
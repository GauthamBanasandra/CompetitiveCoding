//
// Created by gauth on 20-02-2018.
//

#include <list>
#include <iostream>

void Print(const std::list<unsigned long long> &nums) {
  for (auto n : nums) {
    std::cout << n << " ";
  }

  std::cout << std::endl;
}
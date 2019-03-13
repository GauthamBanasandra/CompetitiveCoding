//
// Created by Gautham Banasandra on 16/06/18.
//

#include <iostream>
#include <vector>

using ul = unsigned long;

void Print(const std::vector<ul> &primes) {
  for (const auto p : primes) {
    std::cout << p << " ";
  }

  std::cout << std::endl;
}
//
// Created by gauth on 21-01-2018.
//

#include <iostream>
#include <list>

using ull = unsigned long long;

void Print(const std::list<std::pair<ull, ull>> &data);

void Print(const std::list<std::pair<ull, ull>> &one, const std::list<std::pair<ull, ull>> &three) {
  std::cout << "One loc:" << std::endl;
  Print(one);
  std::cout << "\nThree loc:" << std::endl;
  Print(three);
}

void Print(const std::list<std::pair<ull, ull>> &data) {
  for (const auto &d : data) {
    std::cout << "(" << d.first << ", " << d.second << ")" << std::endl;
  }
} 
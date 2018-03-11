//
// Created by gauth on 11-03-2018.
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>

void Print(const std::unordered_map<int, std::unordered_set<int>> &graph) {
  for (const auto &entry : graph) {
    std::cout << entry.first << " : ";
    for (const auto &n : entry.second) {
      std::cout << n << " ";
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
}
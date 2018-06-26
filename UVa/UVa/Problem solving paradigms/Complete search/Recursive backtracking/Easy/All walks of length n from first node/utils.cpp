//
// Created by gauth on 20-03-2018.
//

#include <iostream>
#include <vector>
#include <unordered_map>

using AdjacencyList = std::unordered_map<int, std::vector<int>>;

void Print(const AdjacencyList &adj_list) {
  for (const auto &k : adj_list) {
    std::cout << k.first << " -> ";
    for (const auto &n : k.second) {
      std::cout << n << " ";
    }

    std::cout << std::endl;
  }
}
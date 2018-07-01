#include <vector>
#include <list>
#include <iostream>

void print(const std::vector<std::list<std::pair<int, int>>> &adj_list) {
  for (auto i = 1; i < adj_list.size(); ++i) {
    std::cout << i << " -> ";
    for (const auto item : adj_list[i]) {
      std::cout << "(" << item.first << ", " << item.second << ")\t";
    }

    std::cout << std::endl;
  }
}
//
// Created by Gautham on 05-12-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <ios>

struct Item {
  Item() : value(0), weight(0) {}
  Item(int value, int weight) : value(value), weight(weight) {}

  int value;
  int weight;
};

class Selector {
 public:
  Selector(const std::vector<Item> &items_, int max_weight);

  int Select(int weight_left);

 private:
  int Select(std::size_t i, int weight_left);

  const std::vector<Item> &items_;
  std::vector<std::vector<int>> memo_;
};

Selector::Selector(const std::vector<Item> &items_, int max_weight) : items_(items_) {
  memo_.resize(items_.size());
  for (auto &row : memo_) {
    row.resize(static_cast<std::size_t>(max_weight) + 1, -1);
  }
  Select(max_weight);
}

int Selector::Select(const int weight_left) {
  return Select(0, weight_left);
}

int Selector::Select(std::size_t i, int weight_left) {
  if (i >= items_.size()) {
    return 0;
  }

  if (items_[i].weight > weight_left) {
    return Select(i + 1, weight_left);
  }

  auto &memo = memo_[i][weight_left];
  if (memo != -1) {
    return memo;
  }
  return memo = std::max(Select(i + 1, weight_left), Select(i + 1, weight_left - items_[i].weight) + items_[i].value);
}

int main() {
  std::ios::sync_with_stdio(false);

  int t;
  std::size_t n, g;
  std::vector<Item> items;
  std::vector<int> capacities;

  std::cin >> t;
  while (t-- > 0) {
    std::cin >> n;
    items.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> items[i].value >> items[i].weight;
    }

    int max_capacity = 0;
    std::cin >> g;
    capacities.resize(g);
    for (std::size_t i = 0; i < g; ++i) {
      std::cin >> capacities[i];
      max_capacity = std::max(max_capacity, capacities[i]);
    }

    Selector selector(items, max_capacity);

    int value_sum = 0;
    for (const auto &capacity : capacities) {
      value_sum += selector.Select(capacity);
    }
    std::cout << value_sum << std::endl;
  }
  return 0;
}
//
// Created by Gautham on 15-12-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

struct Dimsum {
  Dimsum() {}
  Dimsum(int price, int value) : price(price), value(value) {}

  int price{};
  int value{};
};

class Restaurant {
 public:
  Restaurant(const std::vector<Dimsum> &dimsums, int num_people, int budget_each, int tea_price_each);

  double Order();

 private:
  int Order(std::size_t i, int price, int num_ordered);
  bool IsMore(std::size_t i, int price);

  std::vector<std::vector<std::vector<int>>> memo_;

  const int limit_;
  const int tea_price_;
  const int budget_;
  const int num_people_;
  std::vector<Dimsum> dimsums_;
};

Restaurant::Restaurant(const std::vector<Dimsum> &dimsums, int num_people, int budget_each, int tea_price_each)
    : num_people_(num_people),
      budget_(num_people * budget_each),
      tea_price_(num_people * tea_price_each),
      limit_(std::min(2 * static_cast<int>(dimsums.size()), 2 * num_people)) {
  dimsums_.reserve(2 * dimsums.size());
  for (const auto &dimsum : dimsums) {
    dimsums_.emplace_back(dimsum);
    dimsums_.emplace_back(dimsum);
  }

  memo_.resize(dimsums_.size());
  for (auto &table : memo_) {
    table.resize(static_cast<std::size_t>(budget_) + 1);
    for (auto &row : table) {
      row.resize(static_cast<std::size_t>(limit_) + 1, -1);
    }
  }
}

double Restaurant::Order() {
  return Order(0, 0, 0) / static_cast<double>(num_people_);
}

int Restaurant::Order(std::size_t i, int price, int num_ordered) {
  // Inconsistent problem description
  // As per the problem, "NOT order more than 2 dishes of a same type of dim sum. Also, NOT order more than 2(N + 1) dishes in total"
  // I guess it should've been "NOT more than or equal to" hence the following condition "num_ordered >= limit_"
  if (i >= dimsums_.size() || num_ordered >= limit_) {
    return 0;
  }

  if (IsMore(i, price)) {
    return Order(i + 1, price, num_ordered);
  }

  auto &memo = memo_[i][static_cast<std::size_t>(price)][static_cast<std::size_t>(num_ordered)];
  if (memo != -1) {
    return memo;
  }
  return memo = std::max(Order(i + 1, price, num_ordered),
                         Order(i + 1, price + dimsums_[i].price, num_ordered + 1) + dimsums_[i].value);
}

bool Restaurant::IsMore(std::size_t i, int price) {
  auto cost = dimsums_[i].price + price + tea_price_;
  return std::ceil(cost + cost * 0.1) > budget_;
}

int main() {
  int num_people = 4;
  int budget_each = 9;
  int tea_price_each = 3;
  std::size_t num_dimsums;
  std::vector<Dimsum> dimsums{
      {4, 27},
      {10, 14},
  };

  while (std::cin >> num_people >> budget_each >> tea_price_each >> num_dimsums, num_people || budget_each
      || tea_price_each || num_dimsums) {
    ++num_people;
    dimsums.resize(num_dimsums);

    for (std::size_t i = 0; i < num_dimsums; ++i) {
      auto &dimsum = dimsums[i];
      std::cin >> dimsum.price;
      dimsum.value = 0;
      for (auto j = 0, value = 0; j < num_people; ++j) {
        std::cin >> value;
        dimsum.value += value;
      }
    }

    printf("%.2lf\n", Restaurant(dimsums, num_people, budget_each, tea_price_each).Order());
  }
  return 0;
}
//
// Created by Gautham Banasandra on 2018-12-23.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class ChangeMaker {
 public:
  explicit ChangeMaker(std::size_t max_value, const std::vector<int> &denominations);

  int Count(int change);

 private:
  const int infinity_;
  const std::vector<int> &denominations_;
  std::vector<int> memo_;
};

ChangeMaker::ChangeMaker(std::size_t max_value, const std::vector<int> &denominations)
    : denominations_(denominations), infinity_(std::numeric_limits<int>::max()) {
  memo_.resize(max_value + 1, -1);
}

int ChangeMaker::Count(int change) {
  if (change < 0) {
    return infinity_;
  }

  if (change == 0) {
    return 0;
  }

  auto &memo = memo_[change];
  if (memo != -1) {
    return memo;
  }

  auto min_change = infinity_;
  for (int denomination : denominations_) {
    min_change = std::min(min_change, Count(change - denomination));
  }
  return memo = 1 + min_change;
}

int main() {
  auto value = 6;
  std::vector<int> denominations{4, 3, 1};

  ChangeMaker change_maker(500, denominations);
  std::cout << change_maker.Count(value) << std::endl;
  return 0;
}
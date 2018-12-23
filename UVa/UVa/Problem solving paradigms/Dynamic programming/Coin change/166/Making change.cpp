//
// Created by Gautham Banasandra on 2018-12-23.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

const int infinity = std::numeric_limits<int>::max();

struct Denomination {
  Denomination(int value, long count) : value(value), count(count) {}

  int value;
  long count;
};

class ChangeMaker {
 public:
  explicit ChangeMaker(std::size_t max_value, std::vector<Denomination> denominations);

  int Count(int change);

 private:
  std::vector<Denomination> denominations_;
  std::vector<int> memo_;
};

ChangeMaker::ChangeMaker(std::size_t max_value, std::vector<Denomination> denominations) : denominations_(std::move(
    denominations)) {
  memo_.resize(max_value + 1, -1);
}

int ChangeMaker::Count(int change) {
  if (change < 0) {
    return infinity;
  }

  if (change == 0) {
    return 0;
  }

  auto &memo = memo_[change];
  if (memo != -1) {
    return memo;
  }

  auto min_change = infinity;
  for (auto &denomination : denominations_) {
    if (denomination.count == 0) {
      continue;
    }

    --denomination.count;
    min_change = std::min(min_change, Count(change - denomination.value));
    ++denomination.count;
  }
  return memo = 1 + min_change;
}

int main() {
  auto value = 100;
  std::vector<Denomination> denominations{
      {50, 1},
      {20, 3},
      {10, 1},
      {1, infinity}
  };

  ChangeMaker change_maker(500, denominations);
  std::cout << change_maker.Count(value) << std::endl;
  return 0;
}
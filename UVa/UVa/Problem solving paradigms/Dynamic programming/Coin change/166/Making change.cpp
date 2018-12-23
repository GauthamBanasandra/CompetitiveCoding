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

 protected:
  std::vector<Denomination> denominations_;

 private:
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

struct SumIt {
 public:
  SumIt(const std::vector<Denomination> &denominations) : i_denomination(0), i_count(0), denominations(denominations) {}

  int Next(int offset);

 private:
  std::size_t i_denomination;
  std::size_t i_count;
  const std::vector<Denomination> &denominations;
};

int SumIt::Next(int offset) {
  if (i_denomination >= denominations.size()) {
    return -1;
  }

  const auto &denomination = denominations[i_denomination];
  if (i_count >= denomination.count) {
    i_count = 0;
    ++i_denomination;
    return Next(offset);
  }
  ++i_count;
  return denomination.value + offset;
}

class Customer : public ChangeMaker {
 public:
  Customer(std::size_t max_value, std::vector<Denomination> &denominations) : ChangeMaker(max_value, denominations) {}

  SumIt GetSumIt() const { return {denominations_}; }
};

int main() {
  auto value = 100;
  std::vector<Denomination> denominations{
      {50, 1},
      {20, 3},
      {10, 0},
      {1, 10}
  };

  ChangeMaker change_maker(500, denominations);
  std::cout << change_maker.Count(value) << std::endl;

  Customer customer(500, denominations);
  auto sum_it = customer.GetSumIt();
  for (auto change = 0; change != -1; change = sum_it.Next(change)) {
    std::cout << change << std::endl;
  }
  return 0;
}
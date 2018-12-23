//
// Created by Gautham on 23-12-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>

class ChangeMaker {
 public:
  explicit ChangeMaker(std::size_t max_value, const std::vector<int> &denominations);

  long Count(int value) { return Count(0, value); }

 private:
  long Count(std::size_t i, int value);

  const std::vector<int> &denominations_;
  std::vector<std::vector<long>> memo_;
};

ChangeMaker::ChangeMaker(std::size_t max_value, const std::vector<int> &denominations) : denominations_(denominations) {
  std::vector<long> row(max_value + 1, -1);
  memo_.resize(denominations_.size(), row);
}

long ChangeMaker::Count(std::size_t i, int value) {
  if (i >= denominations_.size() || value < 0) {
    return 0;
  }

  if (value == 0) {
    return 1;
  }

  auto &memo = memo_[i][value];
  if (memo != -1) {
    return memo;
  }
  return memo = Count(i + 1, value) + Count(i, value - denominations_[i]);
}

int main() {
  int n;
  std::size_t m;
  std::vector<int> denominations;

  std::cin >> n >> m;
  denominations.resize(m);
  for (std::size_t i = 0; i < m; ++i) {
    std::cin >> denominations[i];
  }
  std::cout << ChangeMaker(250, denominations).Count(n) << std::endl;
  return 0;
}
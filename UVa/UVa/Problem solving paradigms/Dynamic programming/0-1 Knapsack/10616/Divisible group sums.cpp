//
// Created by Gautham on 08-12-2018.
//

#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

class Counter {
 public:
  explicit Counter(const std::vector<int> &numbers);

  ll Count(int divisor, std::size_t m);

 private:
  ll Count(std::size_t i, int sum, std::size_t m);

  int divisor_;
  const std::vector<int> &numbers_;
  std::vector<std::vector<ll>> memo_;
};

Counter::Counter(const std::vector<int> &numbers)
    : divisor_(1), numbers_(numbers) {
  memo_.resize(numbers.size());
}

ll Counter::Count(int divisor, std::size_t m) {
  divisor_ = divisor;
  for (auto &row : memo_) {
    row.resize(m + 1, -1);
  }
  return Count(0, 0, m);
}

ll Counter::Count(std::size_t i, int sum, std::size_t m) {
  if (i >= numbers_.size()) {
    return 0;
  }

  if (m == 0) {
    return sum % divisor_ == 0 ? 1 : 0;
  }

  auto &memo = memo_[i][m];
  if (memo != -1) {
    return memo;
  }
  auto include = Count(i + 1, sum + numbers_[i], m - 1);
  auto exclude = Count(i + 1, sum, m);
  return memo = std::max(include, exclude);
}

int main() {
  std::vector<int> numbers{
      1,
      2,
      3,
      4,
      5,
      6,
      7,
      8,
      9,
      10
  };

  Counter counter(numbers);
  std::cout << counter.Count(5, 1) << std::endl;
  return 0;
}
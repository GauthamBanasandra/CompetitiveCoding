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
  std::vector<std::vector<std::vector<ll>>> memo_;
};

Counter::Counter(const std::vector<int> &numbers)
    : divisor_(1), numbers_(numbers) {
  memo_.resize(numbers.size());
}

ll Counter::Count(int divisor, std::size_t m) {
  divisor_ = divisor;
  for (auto &table : memo_) {
    table.resize(static_cast<std::size_t>(divisor ) + 1);
    for (auto &row : table) {
      row.resize(m + 1, -1);
    }
  }
  return Count(0, 0, m);
}

ll Counter::Count(std::size_t i, int sum, std::size_t m) {
  if (m == 0) {
    return sum % divisor_ == 0 ? 1 : 0;
  }

  if (i >= numbers_.size()) {
    return 0;
  }

  auto &memo = memo_[i][sum][m];
  if (memo != -1) {
    return memo;
  }

  auto exclude = Count(i + 1, sum, m);
  auto include = Count(i + 1, (sum + numbers_[i]) % divisor_, m - 1);
  return memo = exclude + include;
}

int main() {
  std::size_t n, q, m, t = 0;
  int divisor;
  std::vector<int> numbers{
      /*1,
      2,
      3,
      4,
      5,
      6,
      7,
      8,
      9,
      10*/

      2,
      3,
      4,
      5,
      6
  };

  while (std::cin >> n >> q, n || q) {
    numbers.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> numbers[i];
    }

    Counter counter(numbers);
    std::cout << "SET " << (++t) << ":" << std::endl;
    for (std::size_t i = 1; i <= q; ++i) {
      std::cin >> divisor >> m;
      std::cout << "QUERY " << i << ": " << counter.Count(divisor, m) << std::endl;
    }
  }
  return 0;
}
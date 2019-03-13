//
// Created by Gautham on 08-12-2018.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ios>

using ll = long long;

class Counter {
 public:
  explicit Counter(const std::vector<ll> &numbers);

  ll Count(ll divisor, std::size_t m);

 private:
  ll Count(std::size_t i, ll sum, std::size_t m);
  bool IsExists(std::size_t i, ll sum, std::size_t m);

  ll divisor_;
  const std::vector<ll> &numbers_;
  std::unordered_map<std::size_t, std::unordered_map<ll, std::unordered_map<std::size_t, ll>>> memo_;
};

Counter::Counter(const std::vector<ll> &numbers)
    : divisor_(1), numbers_(numbers) {}

ll Counter::Count(ll divisor, std::size_t m) {
  divisor_ = divisor;
  memo_.clear();
  return Count(0, 0, m);
}

ll Counter::Count(std::size_t i, ll sum, std::size_t m) {
  // This condition has to be before i >= numbers_.size()
  // because this check is never made in the calling method

  // Use numbers = {5, 10}, d = 5 and m = 1 with debugger
  // and step through the recursion stack to get an idea
  // about why this check should be done first
  if (m == 0) {
    return sum % divisor_ == 0 ? 1 : 0;
  }

  if (i >= numbers_.size()) {
    return 0;
  }

  if (IsExists(i, sum, m)) {
    return memo_[i][sum][m];
  }

  auto exclude = Count(i + 1, sum, m);
  auto include = Count(i + 1, (sum + numbers_[i]) % divisor_, m - 1);
  memo_[i][sum][m] = exclude + include;
  return memo_[i][sum][m];
}

bool Counter::IsExists(std::size_t i, ll sum, std::size_t m) {
  auto find_i_it = memo_.find(i);
  if (find_i_it == memo_.end()) {
    return false;
  }

  const std::unordered_map<ll, std::unordered_map<std::size_t, ll>> &index_map = find_i_it->second;
  auto find_sum_it = index_map.find(sum);
  if (find_sum_it == index_map.end()) {
    return false;
  }

  const std::unordered_map<std::size_t, ll> &sum_map = find_sum_it->second;
  auto find_m_it = sum_map.find(m);
  return find_m_it != sum_map.end();
}

int main() {
  std::ios::sync_with_stdio(false);

  std::size_t n, q, m, t = 0;
  ll divisor;
  std::vector<ll> numbers;

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
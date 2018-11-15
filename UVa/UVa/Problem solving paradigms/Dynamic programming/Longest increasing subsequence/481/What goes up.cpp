//
// Created by Gautham on 14-11-2018.
//

#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <ios>

using ll = long long;

namespace ds {
class seq {
 public:
  template<typename T>
  static std::vector<T> longest_increasing_latest_elements(const std::vector<T> &numbers);

  template<typename T>
  static std::vector<T> longest_increasing(const std::vector<T> &numbers);
};

template<typename T>
std::vector<T> seq::longest_increasing_latest_elements(const std::vector<T> &numbers) {
  const auto numbers_len = numbers.size();
  std::vector<std::size_t> p(numbers_len);

  std::vector<T> lis;
  lis.reserve(numbers_len);

  std::vector<std::size_t> m;
  m.reserve(numbers_len + 1);
  m.emplace_back(0);

  for (std::size_t i = 0; i < numbers_len; ++i) {
    auto find_it = std::lower_bound(m.begin() + 1, m.end(), numbers[i],
                                    [&numbers](const std::size_t &i_m, const T &number) -> bool {
                                      return numbers[i_m - 1] < number;
                                    });
    auto i_m = std::distance(m.begin(), find_it);
    if (find_it == m.end()) {
      m.emplace_back(i + 1);
    } else {
      *find_it = i + 1;
    }
    p[i] = m[i_m - 1];
  }

  for (auto i = m[m.size() - 1]; i > 0; i = p[i - 1]) {
    lis.emplace_back(numbers[i - 1]);
  }
  std::reverse(lis.begin(), lis.end());
  return lis;
}

template<typename T>
std::vector<T> seq::longest_increasing(const std::vector<T> &numbers) {
  const auto numbers_len = numbers.size();
  std::vector<T> lis;
  std::vector<T> s;
  lis.reserve(numbers_len);
  s.reserve(numbers_len);

  for (const auto &number : numbers) {
    auto find_it = std::lower_bound(s.begin(), s.end(), number);
    auto i_insert = std::distance(s.begin(), find_it);

    if (find_it != s.end()) {
      *find_it = number;
    } else {
      s.emplace_back(number);
    }

    const auto lis_len = lis.size();
    if (i_insert == lis_len) {
      lis.emplace_back(number);
    } else if (i_insert == lis_len - 1) {
      lis[i_insert] = number;
    }
  }
  return lis;
}
}

int main() {
  std::ios::sync_with_stdio(false);

  ll n;
  std::vector<ll> numbers;
  numbers.reserve(100000);

  while (std::cin >> n, !std::cin.eof()) {
    numbers.emplace_back(n);
  }

  auto lis = ds::seq::longest_increasing_latest_elements(numbers);
  std::cout << lis.size() << "\n-" << std::endl;
  for (auto number : lis) {
    std::cout << number << std::endl;
  }
  return 0;
}
//
// Created by Gautham on 14-11-2018.
//

// WA

#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

using ll = long long;

namespace ds {
class seq {
 public:
  template<typename T>
  static std::vector<T> longest_increasing(const std::vector<T> &numbers);
};

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
  ll n;
  std::vector<ll> numbers{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
  numbers.reserve(100000);

  /*while (std::cin >> n, !std::cin.eof()) {
    numbers.emplace_back(n);
  }*/

  auto lis = ds::seq::longest_increasing(numbers);
  std::cout << lis.size() << "\n-" << std::endl;
  for (auto number : lis) {
    std::cout << number << std::endl;
  }
  return 0;
}
//
// Created by Gautham on 16-11-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
std::vector<T> LongestIncreasingSeq(const std::vector<T> &numbers) {
  auto numbers_len = numbers.size();
  std::vector<T> lis;
  lis.reserve(numbers_len);

  std::vector<std::size_t> m;
  m.reserve(numbers_len + 1);
  m.emplace_back(0);

  std::vector<std::size_t> predecessors(numbers_len);

  for (std::size_t i = 0; i < numbers_len; ++i) {
    auto find_it = std::lower_bound(m.begin() + 1,
                                    m.end(),
                                    numbers[i],
                                    [&numbers](const std::size_t &i_m, const T &number) -> bool {
                                      return numbers[i_m - 1] < number;
                                    });
    auto i_m = std::distance(m.begin(), find_it);
    if (find_it == m.end()) {
      m.emplace_back(i + 1);
    } else {
      *find_it = i + 1;
    }
    predecessors[i] = m[i_m - 1];
  }

  for (auto i = m[m.size() - 1]; i > 0; i = predecessors[i - 1]) {
    lis.emplace_back(numbers[i - 1]);
  }
  std::reverse(lis.begin(), lis.end());
  return lis;
}

int main() {
  using ll = long long;

  ll t;
  std::vector<int> numbers{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};

  std::cin >> t;
  while (t--) {

  }
  return 0;
}
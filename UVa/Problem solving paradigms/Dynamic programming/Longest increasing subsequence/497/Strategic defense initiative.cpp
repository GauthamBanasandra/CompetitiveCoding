//
// Created by Gautham on 16-11-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

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

  ll t, number;
  std::string line;
  std::vector<ll> numbers;

  std::cin >> t;
  std::cin.ignore();
  std::getline(std::cin, line);
  for(ll i = 0; i < t; ++i) {
    numbers.clear();
    while (std::getline(std::cin, line), !line.empty() && ((line[0] != '\n') || (line[0] != '\r'))) {
      std::stringstream tokenizer(line);
      tokenizer >> number;
      numbers.emplace_back(number);
    }

    auto lis = LongestIncreasingSeq(numbers);
    if (i > 0) {
      std::cout << std::endl;
    }

    std::cout << "Max hits: " << lis.size() << std::endl;
    for(const auto & n : lis) {
      std::cout << n << std::endl;
    }
  }
  return 0;
}
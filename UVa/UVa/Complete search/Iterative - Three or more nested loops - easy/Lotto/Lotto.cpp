//
// Created by gauth on 20-01-2018.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

void Print(const std::vector<std::string> &subsets);
void Print(const std::vector<int> &subset);

int Count1s(int n) {
  int c = 0;
  while (n) {
    c += n & 1;
    n >>= 1;
  }

  return c;
}

unsigned int NCr(int n, int r) {
  auto p = n - r;
  auto nr = static_cast<unsigned int>(n), dr = static_cast<unsigned int>(p);
  while (--n > r) {
    nr *= n;
  }

  while (--p > 1) {
    dr *= p;
  }

  return nr / dr;
}

void PrintSubsets(const int k, const std::vector<int> &numbers) {
  auto v = NCr(k, 6);
  std::vector<int> subset;
  std::vector<std::vector<int>> subsets(v);

  for (int i = 0, m = 0; i < 1 << k; ++i) {
    auto c = Count1s(i);
    if (c != 6) {
      continue;
    }

    subset.clear();
    subset.assign(c, 0);
    for (int bi = 0, vi = 0, j = 1 << bi; j <= i; j = 1 << (++bi)) {
      if (i & j) {
        subset[vi++] = numbers[bi];
      }
    }

    assert(c == subset.size());
    std::sort(subset.begin(), subset.end());

    subsets[m++] = subset;
  }

  std::sort(subsets.begin(), subsets.end());
  std::string str;
  for (const auto &s : subsets) {
    str.clear();
    for (const auto item : s) {
      str += std::to_string(item) + " ";
    }

    str.pop_back();
    std::cout << str << std::endl;
  }
}

int main() {
  int k, c = 0;
  std::string line;
  std::vector<int> numbers;

  while (std::getline(std::cin, line), line[0] != '0') {
    numbers.clear();
    std::istringstream tokenizer(line);
    tokenizer >> k;
    numbers.assign(k, 0);

    for (int i = 0; i < k; ++i) {
      tokenizer >> numbers[i];
    }

    if (c++ > 0) {
      std::cout << std::endl;
    }

    PrintSubsets(k, numbers);
  }

  return 0;
}
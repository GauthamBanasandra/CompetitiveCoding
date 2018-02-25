//
// Created by gauth on 25-02-2018.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using ui = unsigned int;
using ull = unsigned long long;

namespace ds {
class fen_tree {
 public:
  explicit fen_tree(const ull size) : size_(size + 1) {
    f_.assign(size + 1, 0);
  }

  void update_point(ull i, ull value);
  ull sum(ull i) const;
  ull range_sum(ull i, ull j) const;

 private:
  std::vector<ull> f_;
  ull size_;
};

inline void fen_tree::update_point(ull i, const ull value) {
  while (i < size_) {
    f_[i] += value;
    i += i & -i;
  }
}

inline ull fen_tree::sum(ull i) const {
  ull s = 0;
  while (i > 0) {
    s += f_[i];
    i -= i & -i;
  }

  return s;
}

inline ull fen_tree::range_sum(ull i, ull j) const {
  return sum(j) - (i == 1 ? 0 : sum(i - 1));
}
}

int main() {
  ui t, q;
  ull n, l, r;
  std::string line;
  std::vector<ull> numbers, sub_array_sums;

  std::cin >> t;
  for (ui c = 1; c <= t; ++c) {
    numbers.clear();
    sub_array_sums.clear();
    std::cin >> n >> q;
    std::cin.ignore();

    std::getline(std::cin, line);
    std::istringstream tokenizer(line);
    while (tokenizer >> l) {
      numbers.emplace_back(l);
    }

    ds::fen_tree num_tree(numbers.size());
    for (ull i = 0; i < numbers.size(); ++i) {
      num_tree.update_point(i + 1, numbers[i]);
    }

    for (ull i = 0; i < numbers.size(); ++i) {
      for (ull j = i; j < numbers.size(); ++j) {
        sub_array_sums.emplace_back(num_tree.range_sum(i + 1, j + 1));
      }
    }

    std::sort(sub_array_sums.begin(), sub_array_sums.end());

    ds::fen_tree new_num_tree(sub_array_sums.size());
    for (ull i = 0; i < sub_array_sums.size(); ++i) {
      new_num_tree.update_point(i + 1, sub_array_sums[i]);
    }

    printf("Case #%d:\n", c);
    while (q--) {
      std::cin >> l >> r;
      std::cout << new_num_tree.range_sum(l, r) << std::endl;
    }
  }

  return 0;
}
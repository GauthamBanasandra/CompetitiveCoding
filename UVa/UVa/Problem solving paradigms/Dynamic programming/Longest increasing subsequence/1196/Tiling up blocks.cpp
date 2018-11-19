//
// Created by Gautham on 17-11-2018.
//

// WA

#include <algorithm>
#include <vector>
#include <iostream>

struct Pair {
  Pair() : l(0), m(0) {}
  Pair(const int l, const int m) : l(l), m(m) {}

  int l;
  int m;
};

std::size_t count_longest(std::vector<Pair> &items) {
  std::sort(items.begin(), items.end(), [](const Pair &p, const Pair &q) -> bool {
    return p.l < q.l;
  });

  const auto items_len = items.size();
  std::vector<std::size_t> m;
  m.reserve(items_len + 1);
  m.emplace_back(0);

  std::vector<std::size_t> predecessors(items_len);

  for (std::size_t i = 0; i < items_len; ++i) {
    auto find_it = std::upper_bound(m.begin() + 1,
                                    m.end(),
                                    i,
                                    [&items](const std::size_t &i_m, const std::size_t &i_item) -> bool {
                                      return items[i_m - 1].l < items[i_item].l;
                                    });
    auto i_m = std::distance(m.begin(), find_it);
    if (find_it == m.end()) {
      m.emplace_back(i + 1);
    } else {
      *find_it = i + 1;
    }
    predecessors[i] = m[i_m - 1];
  }

  std::vector<Pair> lis;
  for (auto i = m[m.size() - 1]; i > 0; i = predecessors[i - 1]) {
    lis.emplace_back(items[i - 1]);
  }
  std::reverse(lis.begin(), lis.end());
  for (const auto &item : lis) {
    std::cout << item.l << '\t' << item.m << std::endl;
  }
  return 0;
}

int main() {
  std::size_t n;
  std::vector<Pair> blocks{
      {3, 2},
      {1, 1},
      {2, 3},
  };

  std::cout << count_longest(blocks) << std::endl;

  /*while (std::cin >> n, n) {
    blocks.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> blocks[i].l >> blocks[i].m;
    }

    std::cout << count_longest(blocks) << std::endl;
  }
  std::cout << '*' << std::endl;*/
  return 0;
}
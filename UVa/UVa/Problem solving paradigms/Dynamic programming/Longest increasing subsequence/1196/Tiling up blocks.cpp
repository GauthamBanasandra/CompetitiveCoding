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

  std::vector<Pair> lis;
  lis.reserve(items.size());

  for (const auto &item : items) {
    auto find_it = std::lower_bound(lis.begin(), lis.end(), item, [](const Pair &p, const Pair &q) -> bool {
      return p.m <= q.m;
    });

    if (find_it == lis.end()) {
      lis.emplace_back(item);
    } else {
      *find_it = item;
    }
  }
  return lis.size();
}

int main() {
  std::size_t n;
  std::vector<Pair> blocks{
      {3, 2},
      {1, 1},
      {2, 3},
  };

//  std::cout << count_longest(blocks) << std::endl;

  while (std::cin >> n, n) {
    blocks.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> blocks[i].l >> blocks[i].m;
    }

    std::cout << count_longest(blocks) << std::endl;
  }
  std::cout << '*' << std::endl;
  return 0;
}
//
// Created by gautham on 9/9/18.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <ios>

using ull = unsigned long long;

struct SelectionInfo {
  SelectionInfo(bool success, ull cost) : success(success), cost(cost) {}

  bool success;
  ull cost;
};

class Selector {
 public:
  Selector(std::vector<ull> dragons, std::vector<ull> knights);
  SelectionInfo Select() const;

 private:
  std::vector<ull> dragons_;
  std::vector<ull> knights_;
};

Selector::Selector(std::vector<ull> dragons, std::vector<ull> knights)
    : dragons_(std::move(dragons)), knights_(std::move(knights)) {
  std::sort(dragons_.begin(), dragons_.end());
  std::sort(knights_.begin(), knights_.end());
}

SelectionInfo Selector::Select() const {
  if (knights_.size() < dragons_.size()) {
    return {false, 0};
  }

  ull cost = 0;
  auto k_it = knights_.begin();

  for (auto d : dragons_) {
    k_it = std::lower_bound(k_it, knights_.end(), d);
    if (k_it == knights_.end()) {
      return {false, 0};
    }

    cost += *k_it;
    ++k_it;
  }

  return {true, cost};
}

int main() {
  std::ios::sync_with_stdio(false);

  std::size_t n, m;
  std::vector<ull> dragons{5, 5};
  std::vector<ull> knights{10};

  while (std::cin >> n >> m, n || m) {
    dragons.resize(n);
    knights.resize(m);

    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> dragons[i];
    }

    for (std::size_t i = 0; i < m; ++i) {
      std::cin >> knights[i];
    }

    Selector selector(dragons, knights);
    auto info = selector.Select();
    if (info.success) {
      std::cout << info.cost << std::endl;
    } else {
      std::cout << "Loowater is doomed!" << std::endl;
    }
  }
  return 0;
}
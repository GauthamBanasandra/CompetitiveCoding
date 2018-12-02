//
// Created by Gautham on 01-12-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using ll = long long;
void Print(const std::vector<std::vector<ll>> &matrix);

struct Treasure {
  Treasure() : depth(0), value(0), time(0) {}
  Treasure(ll depth, ll value, ll w) : depth(depth), value(value), time((w * depth) + (2 * w * depth)) {}

  const ll depth;
  const ll value;
  const ll time;
};

class TreasureSelector {
 public:
  explicit TreasureSelector(const std::vector<Treasure> &treasures, ll max_time);
  std::pair<ll, std::vector<size_t>> Select() const;

 private:
  ll Select(size_t i, ll rem) const;
  std::vector<std::size_t> GetSelectedTreasures() const;

  mutable std::vector<std::vector<ll>> memo_, memo_sel_;
  const std::vector<Treasure> &treasures_;
  const std::size_t num_treasures_;
  ll max_time_;
};

TreasureSelector::TreasureSelector(const std::vector<Treasure> &treasures, ll max_time)
    : treasures_(treasures), num_treasures_(treasures_.size()), max_time_(max_time) {
  memo_.resize(num_treasures_);
  for (auto &memo : memo_) {
    memo.assign(static_cast<std::size_t>(max_time_) + 1, -1);
  }

  memo_sel_.resize(num_treasures_);
  for (auto &memo : memo_sel_) {
    memo.assign(static_cast<std::size_t>(max_time_) + 1, 0);
  }
}

ll TreasureSelector::Select(size_t i, ll rem) const {
  if (i >= num_treasures_) {
    return 0;
  }

  if (treasures_[i].time > rem) {
    memo_sel_[i][rem] = -1;
    return Select(i + 1, rem);
  }

  if (memo_[i][rem] != -1) {
    return memo_[i][rem];
  }

  auto include = Select(i + 1, rem - treasures_[i].time) + treasures_[i].value;
  auto exclude = Select(i + 1, rem);

  if (exclude > include) {
    memo_[i][rem] = exclude;
    memo_sel_[i][rem] = -1;
  } else {
    memo_[i][rem] = include;
    memo_sel_[i][rem] = 1;
  }

  return memo_[i][rem];
}

std::pair<ll, std::vector<std::size_t>> TreasureSelector::Select() const {
  std::pair<ll, std::vector<std::size_t>> info;
  auto res = Select(0, max_time_);
//  Print(memo_sel_);
  info.first = res;
  info.second = GetSelectedTreasures();
  return info;
}

std::vector<size_t> TreasureSelector::GetSelectedTreasures() const {
  std::vector<std::size_t> indices;
  indices.reserve(num_treasures_);

  for (std::size_t i = 0, column = static_cast<std::size_t>(max_time_); i < num_treasures_; ++i) {
    assert(memo_sel_[i][column] == 1 || memo_sel_[i][column] == -1);
    if (memo_sel_[i][column] == 1) {
      indices.emplace_back(i);
      column -= treasures_[i].time;
    }
  }
  return indices;
}

int main() {
  ll t = 210, w = 0, depth, value;
  std::size_t n = 0, c = 0;
//  ll t = 12;
//  ll t = 604;
  std::vector<Treasure> treasures{
      {10, 5, 4},
      {10, 1, 4},
      {7, 2, 4}

      /*{2, 5, 1},
      {2, 1, 1},
      {1, 2, 1}*/

      /*{32, 11, 3},
      {15, 83, 3},
      {78, 61, 3},
      {45, 56, 3},
      {87, 3, 3},
      {14, 57, 3},
      {52, 64, 3},
      {10, 45, 3},
      {14, 99, 3},
      {55, 6, 3},
      {89, 11, 3},
      {64, 79, 3},
      {7, 73, 3},
      {78, 86, 3},
      {73, 62, 3},
      {73, 1, 3},
      {85, 5, 3},
      {19, 88, 3},
      {97, 15, 3},
      {18, 16, 3},
      {74, 84, 3},
      {29, 26, 3},
      {77, 10, 3},
      {68, 95, 3},
      {58, 84, 3},
      {16, 57, 3},
      {83, 22, 3},
      {8, 23, 3}*/
  };

  while (std::cin >> t >> w, !std::cin.eof()) {
    std::cin >> n;
    treasures.clear();
    treasures.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> depth >> value;
      treasures.emplace_back(depth, value, w);
    }

    if (c > 0) {
      std::cout << std::endl;
    }

    auto info = TreasureSelector(treasures, t).Select();
    std::cout << info.first << std::endl;
    std::cout << info.second.size() << std::endl;
    for (const auto &i_treasure : info.second) {
      std::cout << treasures[i_treasure].depth << " " << treasures[i_treasure].value << std::endl;
    }

    ++c;
  }
  return 0;
}
//
// Created by Gautham on 01-12-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>

using ll = long long;
void Print(const std::vector<std::vector<ll>> &matrix);

struct Treasure {
  Treasure(ll depth, ll value, ll w) : depth(depth), value(value), time((w * depth) + (2 * w * depth)) {}

  const ll depth;
  const ll value;
  const ll time;
};

class TreasureSelector {
 public:
  explicit TreasureSelector(const std::vector<Treasure> &treasures, ll max_time);
  ll Select() const;

 private:
  ll Select(std::size_t i, ll rem) const;

  mutable std::vector<std::vector<ll>> memo_;
  const std::vector<Treasure> &treasures_;
  const std::size_t num_treasures_;
  ll memo_row_len_;
};

TreasureSelector::TreasureSelector(const std::vector<Treasure> &treasures, ll max_time)
    : treasures_(treasures), num_treasures_(treasures_.size()), memo_row_len_(max_time) {
  memo_.resize(num_treasures_);
  for (auto &memo : memo_) {
    memo.assign(static_cast<std::size_t>(memo_row_len_) + 1, -1);
  }
}

ll TreasureSelector::Select(std::size_t i, ll rem) const {
  if (i >= num_treasures_) {
    return 0;
  }

  if (treasures_[i].time > rem) {
    return Select(i + 1, rem);
  }

  if (memo_[i][rem] != -1) {
    return memo_[i][rem];
  }

  memo_[i][rem] = std::max(Select(i + 1, rem), Select(i + 1, rem - treasures_[i].time) + treasures_[i].value);
  return memo_[i][rem];
}

ll TreasureSelector::Select() const {
  auto res = Select(0, memo_row_len_);
//  Print(memo_);
  return res;
}

int main() {
  ll t = 12;
//  ll t = 210;
//  ll t = 604;
  std::vector<Treasure> treasures{
      /*{10, 5, 4},
      {10, 1, 4},
      {7, 2, 4}*/

      {2, 5, 1},
      {2, 1, 1},
      {1, 2, 1}

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

  std::cout << TreasureSelector(treasures, t).Select() << std::endl;
  return 0;
}
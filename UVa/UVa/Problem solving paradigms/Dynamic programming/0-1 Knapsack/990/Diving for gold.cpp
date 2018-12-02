//
// Created by Gautham on 01-12-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <ios>

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
  explicit TreasureSelector(const std::vector<Treasure> &treasures)
      : treasures_(treasures), num_treasures_(treasures_.size()) {}

  std::pair<ll, std::vector<std::size_t>> Select(std::size_t max_time) const;

 private:
  void InitMemo(std::size_t num_row) const;
  ll Select(std::size_t i, std::size_t rem) const;
  std::vector<size_t> GetSelectedTreasures(std::size_t column) const;

  mutable std::vector<std::vector<ll>> memo_value_;
  mutable std::vector<std::vector<short>> memo_pick_; // Table to remember whether we chose to pick or not pick a treasure for a given (i, remaining_time)
  const std::vector<Treasure> &treasures_;
  const std::size_t num_treasures_;
};

ll TreasureSelector::Select(std::size_t i, std::size_t rem) const {
  if (i >= num_treasures_) {
    return 0;
  }

  if (treasures_[i].time > rem) {
    memo_pick_[i][rem] = -1;
    return Select(i + 1, rem);
  }

  if (memo_value_[i][rem] != -1) {
    return memo_value_[i][rem];
  }

  auto include = Select(i + 1, rem - treasures_[i].time) + treasures_[i].value;
  auto exclude = Select(i + 1, rem);

  if (exclude > include) {
    memo_value_[i][rem] = exclude;
    memo_pick_[i][rem] = -1; // Don't pick the treasure as we have exclude > include without this treasure i
  } else {
    memo_value_[i][rem] = include;
    memo_pick_[i][rem] = 1; // Pick the treasure as we have include > exclude with this treasure i
  }

  return memo_value_[i][rem];
}

std::pair<ll, std::vector<std::size_t>> TreasureSelector::Select(std::size_t max_time) const {
  InitMemo(max_time);
  return {Select(0, max_time), GetSelectedTreasures(max_time)};
}

std::vector<size_t> TreasureSelector::GetSelectedTreasures(std::size_t column) const {
  std::vector<std::size_t> indices;
  indices.reserve(num_treasures_);

  // Nicely explained here - https://www.programminglogic.com/knapsack-problem-dynamic-programming-algorithm/
  // Refer to the section "Storing the Picked Items" in the above link
  for (std::size_t i = 0; i < num_treasures_; ++i) {
    assert(memo_pick_[i][column] == 1 || memo_pick_[i][column] == -1);
    if (memo_pick_[i][column] == 1) {
      indices.emplace_back(i);
      column -= treasures_[i].time;
    }
  }
  return indices;
}

void TreasureSelector::InitMemo(std::size_t num_row) const {
  memo_value_.resize(num_treasures_);
  for (auto &memo : memo_value_) {
    memo.assign(static_cast<std::size_t>(num_row) + 1, -1);
  }

  memo_pick_.resize(num_treasures_);
  for (auto &memo : memo_pick_) {
    memo.assign(static_cast<std::size_t>(num_row) + 1, 0);
  }
}

int main() {
  std::ios::sync_with_stdio(false);

  ll w = 0, depth, value;
  std::size_t n = 0, c = 0, t = 210;
  std::vector<Treasure> treasures;

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

    auto info = TreasureSelector(treasures).Select(t);
    std::cout << info.first << std::endl;
    std::cout << info.second.size() << std::endl;
    for (const auto &i_treasure : info.second) {
      std::cout << treasures[i_treasure].depth << " " << treasures[i_treasure].value << std::endl;
    }

    ++c;
  }
  return 0;
}
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <ostream>
#include <unordered_map>
#include <utility>
#include <vector>

namespace LeetCodeCodingChallenge_02_2021 {
class WeakInfoProvider {
public:
  WeakInfoProvider(const std::vector<std::vector<int>> &data);

  std::vector<int> GetTopKWeakRowIndexes(size_t k) const;

private:
  const size_t num_rows_;
  std::vector<size_t> ones_count_;
  std::vector<size_t> order_;
  std::vector<size_t> weak_order_;
  std::unordered_map<size_t, std::vector<size_t>> indexes_;
};

WeakInfoProvider::WeakInfoProvider(const std::vector<std::vector<int>> &data)
    : num_rows_{data.size()} {
  ones_count_.reserve(num_rows_);
  order_.reserve(num_rows_);
  weak_order_.reserve(num_rows_);

  for (const auto &row : data) {
    ones_count_.emplace_back(std::accumulate(row.begin(), row.end(), 0));
  }

  assert(ones_count_.size() == num_rows_);
  for (size_t i = 0; i < num_rows_; ++i) {
    indexes_[ones_count_[i]].emplace_back(i);
  }

  order_ = ones_count_;
  std::sort(order_.begin(), order_.end());
}

std::vector<int> WeakInfoProvider::GetTopKWeakRowIndexes(const size_t k) const {
  std::vector<std::pair<size_t, size_t>> weakest_rows;
  weakest_rows.reserve(num_rows_);

  for (size_t i = 0; i < num_rows_; ++i) {
    size_t weak_score = 0;
    const auto pos_order =
        std::upper_bound(order_.begin(), order_.end(), ones_count_[i]);
    weak_score = num_rows_ - std::distance(order_.begin(), pos_order);

    const auto &pos = indexes_.at(ones_count_[i]);
    const auto pos_index = std::upper_bound(pos.begin(), pos.end(), i);
    weak_score += pos.size() - std::distance(pos.begin(), pos_index);

    weakest_rows.emplace_back(i, weak_score);
  }

  std::sort(weakest_rows.begin(), weakest_rows.end(),
            [](const std::pair<size_t, size_t> &a,
               const std::pair<size_t, size_t> &b) -> bool {
              return a.second > b.second;
            });

  std::vector<int> k_weakest_rows(k);
  for (size_t i = 0; i < k; ++i) {
    k_weakest_rows[i] = weakest_rows[i].first;
  }
  return k_weakest_rows;
}
} // namespace LeetCodeCodingChallenge_02_2021

class Solution {
public:
  std::vector<int> kWeakestRows(std::vector<std::vector<int>> &mat, int k);
};

std::vector<int> Solution::kWeakestRows(std::vector<std::vector<int>> &mat,
                                        int k) {
  return LeetCodeCodingChallenge_02_2021::WeakInfoProvider(mat)
      .GetTopKWeakRowIndexes(k);
}

int main(int argc, char *argv[]) {
  std::vector<std::vector<int>> mat = {
      {1, 0, 0, 0}, {1, 1, 1, 1}, {1, 0, 0, 0}, {1, 0, 0, 0}};
  const auto k = 3;
  auto result = Solution().kWeakestRows(mat, k);
  for (const auto value : result) {
    std::cout << value << std::endl;
  }
  return 0;
}

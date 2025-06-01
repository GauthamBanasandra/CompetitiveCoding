#include <algorithm>
#include <iostream>
#include <limits>
#include <optional>
#include <unordered_map>
#include <vector>

class Solution {
public:
  std::vector<int> topKFrequent(std::vector<int> &nums, int k);
};

std::vector<int> Solution::topKFrequent(std::vector<int> &nums, int k) {
  std::unordered_map<int, std::size_t> freq_table;
  for (const auto num : nums) {
    ++freq_table[num];
  }

  std::vector<std::vector<int>> freq_order(nums.size() + 1);
  for (const auto &kv : freq_table) {
    const auto &value = kv.first;
    const auto &freq = kv.second;
    freq_order[freq].emplace_back(value);
  }

  std::vector<int> k_freq;
  k_freq.reserve(k);
  for (auto i_it = freq_order.rbegin(); i_it != freq_order.rend(); ++i_it) {
    if (i_it->empty()) {
      continue;
    }

    for (auto j_it = i_it->begin(); j_it != i_it->end() && k > 0; ++j_it, --k) {
      k_freq.emplace_back(*j_it);
    }
  }
  return k_freq;
}

int main(int argc, char *argv[]) {
  std::vector nums{1, 2, 2, 3, 3, 3};
  auto k = 2;
  for (const auto num : Solution().topKFrequent(nums, k)) {
    std::cout << num << std::endl;
  }

  return 0;
}

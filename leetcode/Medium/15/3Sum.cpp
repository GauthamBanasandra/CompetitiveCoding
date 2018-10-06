//
// Created by gautham on 5/10/18.
//

// TLE
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include <unordered_set>
#include <cassert>

using FrequencyTable = std::unordered_map<int, std::size_t>;

class Solution {
 public:
  std::vector<std::vector<int>> threeSum(const std::vector<int> &nums);

 private:
  static std::vector<int> GetTriplet(int a, int b, int c);
  static std::string Hash(const std::vector<int> &triplet);
  void Select(FrequencyTable &f, FrequencyTable::iterator &&it) const;
};

std::vector<std::vector<int>> Solution::threeSum(const std::vector<int> &nums) {
  std::vector<std::vector<int>> triplets;
  FrequencyTable f;
  std::unordered_set<std::string> uniq_triplets;

  for (const auto num : nums) {
    ++f[num];
  }

  for (std::size_t i = 0, nums_len = nums.size(); i < nums_len; ++i) {
    auto a = nums[i];
    Select(f, f.find(a));

    for (std::size_t j = i + 1; j < nums_len; ++j) {
      auto b = nums[j];
      Select(f, f.find(b));

      auto c = -(a + b);
      auto c_it = f.find(c);
      if (c_it != f.end()) {
        auto triplet = Solution::GetTriplet(a, b, c);
        auto hash = Hash(triplet);
        auto uniq_triplets_it = uniq_triplets.find(hash);
        if (uniq_triplets_it == uniq_triplets.end()) {
          triplets.emplace_back(triplet);
          uniq_triplets.emplace_hint(uniq_triplets_it, hash);
        }
      }

      ++f[b];
    }

    ++f[a];
  }
  return triplets;
}

void Solution::Select(FrequencyTable &f, FrequencyTable::iterator &&it) const {
  assert(it != f.end());

  --it->second;
  if (it->second == 0) {
    f.erase(it);
  }
}

std::vector<int> Solution::GetTriplet(int a, int b, int c) {
  std::vector<int> triplet{a, b, c};
  std::sort(triplet.begin(), triplet.end());
  return triplet;
}

std::string Solution::Hash(const std::vector<int> &triplet) {
  assert(triplet.size() == 3);
  return std::to_string(triplet[0]) + " " + std::to_string(triplet[1]) + " " + std::to_string(triplet[2]);
}

int main() {
  std::vector<int> nums{-1, 0, 1, 2, -1, -4};
  for (auto &sol : Solution().threeSum(nums)) {
    std::cout << sol[0] << "\t" << sol[1] << "\t" << sol[2] << std::endl;
  }
  return 0;
}
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

class Solution {
public:
  std::vector<int> twoSum(std::vector<int> &nums, int target);

private:
  static std::unordered_map<int, std::list<std::size_t>>
  GetValueIndices(const std::vector<int> &nums);
};

std::vector<int> Solution::twoSum(std::vector<int> &nums, int target) {
  auto value_indices = GetValueIndices(nums);

  for (const auto num : nums) {
    const auto kv_1 = value_indices.find(num);
    const auto key_1 = kv_1->first;
    const auto value_1 = kv_1->second.front();
    kv_1->second.pop_front();

    const auto kv_2 = value_indices.find(target - key_1);
    if (kv_2 != value_indices.end() && !kv_2->second.empty()) {
      const auto value_2 = kv_2->second.front();
      return {static_cast<int>(value_1), static_cast<int>(value_2)};
    }

    kv_1->second.emplace_back(value_1);
  }

  return {};
}

std::unordered_map<int, std::list<std::size_t>>
Solution::GetValueIndices(const std::vector<int> &nums) {
  std::unordered_map<int, std::list<std::size_t>> value_indices;
  for (auto it = nums.begin(); it != nums.end(); ++it) {
    value_indices[*it].emplace_back(std::distance(nums.begin(), it));
  }
  return value_indices;
}

int main(int argc, char *argv[]) {
  std::vector nums{3, 4, 5, 6};
  auto target = 7;

  for (auto index : Solution().twoSum(nums, target)) {
    std::cout << index << std::endl;
  }

  return 0;
}

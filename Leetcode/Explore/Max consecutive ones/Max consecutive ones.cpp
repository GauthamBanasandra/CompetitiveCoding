#include <iostream>
#include <utility>
#include <vector>

class Solution {
public:
  int findMaxConsecutiveOnes(std::vector<int> &nums);
};

int Solution::findMaxConsecutiveOnes(std::vector<int> &nums) {
  std::size_t max_consecutive_ones = 0;
  std::size_t consecutive_ones_count = 0;

  for (const int num : nums) {
    if (num == 0) {
      consecutive_ones_count = 0;
    } else {
      ++consecutive_ones_count;
      max_consecutive_ones =
          std::max(max_consecutive_ones, consecutive_ones_count);
    }
  }

  return max_consecutive_ones;
}

int main(int argc, char *argv[]) {
  std::vector<int> nums = {1, 1, 0, 1, 1, 1};
  std::cout << Solution().findMaxConsecutiveOnes(nums) << std::endl;

  nums = {1, 0, 1, 1, 0, 1};
  std::cout << Solution().findMaxConsecutiveOnes(nums) << std::endl;

  return 0;
}
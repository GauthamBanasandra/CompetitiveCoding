#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
  int removeElement(std::vector<int> &nums, int val);
};

int Solution::removeElement(std::vector<int> &nums, int val) {
  const auto it = std::ranges::remove(nums, val).begin();
  return static_cast<int>(std::distance(nums.begin(), it));
}

int main(int argc, char *argv[]) {
  std::vector nums{3, 2, 2, 3};
  constexpr auto val = 3;
  const auto k = Solution().removeElement(nums, val);

  std::cout << "k = " << k << std::endl;
  for (int num : nums) {
    std::cout << num << std::endl;
  }

  return 0;
}

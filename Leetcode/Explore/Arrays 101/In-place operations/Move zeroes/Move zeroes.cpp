#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

class Solution {
public:
  void moveZeroes(std::vector<int> &nums);
};

void Solution::moveZeroes(std::vector<int> &nums) {
  auto write_it = std::ranges::find(nums, 0);
  if (write_it == nums.end()) {
    return;
  }

  for (auto read_it = std::find_if(write_it + 1, nums.end(),
                                   [](const auto &e) { return e != 0; });
       read_it != nums.end();
       read_it = std::find_if(read_it, nums.end(),
                              [](const auto &e) { return e != 0; })) {
    std::swap(*read_it, *write_it);
    ++write_it;
  }
}

int main(int argc, char *argv[]) {
  std::vector nums{0};
  Solution().moveZeroes(nums);
  for (int num : nums) {
    std::cout << num << std::endl;
  }

  return 0;
}

#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

class Solution {
public:
  std::vector<int> sortArrayByParity(std::vector<int> &nums);
};

std::vector<int> Solution::sortArrayByParity(std::vector<int> &nums) {
  auto write_it =
      std::ranges::find_if(nums, [](const auto &e) { return (e & 1) == 1; });
  if (write_it == nums.end()) {
    return nums;
  }

  for (auto read_it = write_it + 1; read_it != nums.end(); ++read_it) {
    if ((*read_it & 1) == 0) {
      std::swap(*write_it, *read_it);
      ++write_it;
    }
  }

  return nums;
}

int main(int argc, char *argv[]) {
  std::vector nums{1};
  for (const int num : Solution().sortArrayByParity(nums)) {
    std::cout << num << std::endl;
  }
  return 0;
}

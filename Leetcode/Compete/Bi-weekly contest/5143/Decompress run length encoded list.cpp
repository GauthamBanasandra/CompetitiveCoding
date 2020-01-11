#include <vector>

class Solution {
public:
  std::vector<int> decompressRLElist(std::vector<int> &nums);
};

std::vector<int> Solution::decompressRLElist(std::vector<int> &nums) {
  std::vector<int> decompressed;
  size_t i = 0;
  while (true) {
    auto a_idx = 2 * i;
    auto b_idx = 2 * i + 1;
    if (b_idx >= nums.size()) {
      break;
    }

    for (auto j = 0; j < nums[a_idx]; ++j) {
      decompressed.emplace_back(nums[b_idx]);
    }
    ++i;
  }
  return decompressed;
}

int main(int argc, char *argv[]) { return 0; }

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

class Solution {
public:
  std::vector<int> replaceElements(std::vector<int> &arr);
};

std::vector<int> Solution::replaceElements(std::vector<int> &arr) {
  auto max = -1;
  for (int &it : std::ranges::reverse_view(arr)) {
    auto curr = it;
    it = max;
    max = std::max(max, curr);
  }

  return arr;
}

int main(int argc, char *argv[]) {
  std::vector arr{400};
  for (const int num : Solution().replaceElements(arr)) {
    std::cout << num << std::endl;
  }
  return 0;
}

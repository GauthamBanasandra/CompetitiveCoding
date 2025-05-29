#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

class Solution {
public:
  int heightChecker(std::vector<int> &heights);
};

int Solution::heightChecker(std::vector<int> &heights) {
  auto sorted_heights = heights;
  std::ranges::sort(sorted_heights);

  std::size_t invalid_pos_count = 0;
  for (auto i_it = heights.begin(), j_it = sorted_heights.begin();
       i_it != heights.end(); ++i_it, ++j_it) {
    invalid_pos_count =
        *i_it != *j_it ? invalid_pos_count + 1 : invalid_pos_count;
  }

  return static_cast<int>(invalid_pos_count);
}

int main(int argc, char *argv[]) {
  std::vector heights{5, 1, 2, 3, 4};
  std::cout << Solution().heightChecker(heights) << std::endl;
  return 0;
}

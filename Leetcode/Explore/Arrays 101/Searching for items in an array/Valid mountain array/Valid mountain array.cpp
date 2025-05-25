#include <iostream>
#include <vector>

class Solution {
public:
  bool validMountainArray(std::vector<int> &arr);
};

bool Solution::validMountainArray(std::vector<int> &arr) {
  if (arr.size() < 3) {
    return false;
  }

  auto up_slope = false;
  auto it = arr.begin();
  for (; it != arr.end() - 1 && *it < *(it + 1); ++it) {
    up_slope = true;
  }

  if (!up_slope) {
    return false;
  }

  auto down_slope = false;
  for (; it != arr.end() - 1 && *it > *(it + 1); ++it) {
    down_slope = true;
  }

  return up_slope && down_slope && it == arr.end() - 1;
}

int main(int argc, char *argv[]) {
  std::vector arr{1, 2, 3, 1};
  std::cout << Solution().validMountainArray(arr) << std::endl;
  return 0;
}

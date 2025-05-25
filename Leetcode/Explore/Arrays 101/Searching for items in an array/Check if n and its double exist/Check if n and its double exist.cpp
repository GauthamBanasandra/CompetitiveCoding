#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
  bool checkIfExist(std::vector<int> &arr);
};

bool Solution::checkIfExist(std::vector<int> &arr) {
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    if (std::find(it + 1, arr.end(), *it * 2) != arr.end() ||
        !(*it & 1) && std::find(it + 1, arr.end(), *it / 2) != arr.end()) {
      return true;
    }
  }

  return false;
}

int main(int argc, char *argv[]) {
  std::vector arr{3, 1, 7, 11};
  std::cout << Solution().checkIfExist(arr) << std::endl;
  return 0;
}

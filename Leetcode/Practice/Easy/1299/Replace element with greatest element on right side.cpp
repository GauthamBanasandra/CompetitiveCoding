#include <algorithm>
#include <vector>

class Solution {
public:
  std::vector<int> replaceElements(std::vector<int> &arr);
};

std::vector<int> Solution::replaceElements(std::vector<int> &arr) {
  auto max = -1;
  auto temp = 0;
  for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
    temp = *it;
    *it = max;
    max = std::max(max, temp);
  }
  return arr;
}

int main(int argc, char *argv[]) { return 0; }

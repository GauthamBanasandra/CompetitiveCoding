#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

namespace lc_1099 {
using namespace std;

const auto infinity = numeric_limits<int>::max();

class Solution {
public:
  int twoSumLessThanK(vector<int> &A, int K);
};

int Solution::twoSumLessThanK(vector<int> &a, int k) {
  sort(a.begin(), a.end());
  reverse(a.begin(), a.end());

  auto max_value = 0;

  for (auto it = a.begin(); it != a.end(); ++it) {
    if (*it >= k) {
      continue;
    }

    auto diff = k - *it;
    auto find_it = upper_bound(it + 1, a.end(), diff, greater<>());
    if (find_it != a.end()) {
      max_value = max(max_value, *it + *find_it);
    }

    if (it == a.begin()) {
      continue;
    }

    find_it = upper_bound(a.begin(), it, diff, greater<>());
    if (find_it != it) {
      max_value = max(max_value, *it + *find_it);
    }
  }
  return max_value;
}
} // namespace lc_1099

int main(int argc, char *argv[]) {
  std::vector<int> numbers{34, 23, 1, 24, 75, 33, 54, 8};
  auto k = 60;
  std::cout << lc_1099::Solution().twoSumLessThanK(numbers, k) << std::endl;
  return 0;
}

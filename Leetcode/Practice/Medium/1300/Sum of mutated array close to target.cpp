#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <ostream>
#include <vector>

const auto infinity = std::numeric_limits<int>::max();

class Solution {
public:
  int findBestValue(std::vector<int> &arr, int target);

private:
  static std::vector<int> GetPrefixSum(const std::vector<int> &arr);
};

int Solution::findBestValue(std::vector<int> &arr, const int target) {
  std::sort(arr.begin(), arr.end());
  auto prefix_sum = GetPrefixSum(arr);

  auto min_diff = infinity;
  auto best_value = 0;

  // Went wrong here. I was looping from arr.front() i.e. the min in the array
  // to arr.back() i.e. the max in the array. That is incorrect because the
  // numbers from 0 to arr.front() need to be considered too
  for (auto num = 0; num <= arr.back(); ++num) {
    auto find_it = std::lower_bound(arr.begin(), arr.end(), num);
    auto i = std::distance(arr.begin(), find_it);
    auto right_sum = (static_cast<int>(arr.size()) - static_cast<int>(i)) * num;
    auto left_sum = 0;
    if (i > 0) {
      left_sum = prefix_sum[i - 1];
    }
    auto sum = left_sum + right_sum;
    auto diff = std::abs(target - sum);
    if (diff < min_diff || (diff == min_diff && num < best_value)) {
      min_diff = diff;
      best_value = num;
    }
  }
  return best_value;
}

std::vector<int> Solution::GetPrefixSum(const std::vector<int> &arr) {
  std::vector<int> prefix_sum(arr.size());
  prefix_sum.front() = arr.front();
  for (size_t i = 1; i < arr.size(); ++i) {
    prefix_sum[i] = prefix_sum[i - 1] + arr[i];
  }
  return prefix_sum;
}

int main(int argc, char *argv[]) {
  std::vector<int> arr{60864, 25176, 27249, 21296, 20204};
  auto target = 56803;

  std::cout << Solution().findBestValue(arr, target) << std::endl;
  return 0;
}

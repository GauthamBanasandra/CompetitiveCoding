#include <iostream>
#include <vector>

class Solution {
public:
  void merge(std::vector<int> &nums1, int m, std::vector<int> &nums2, int n);
};

void Solution::merge(std::vector<int> &nums1, int m, std::vector<int> &nums2,
                     int n) {
  const auto last = nums1.rbegin();
  std::cout << *last << std::endl;
}

int main() {
  std::vector nums1{1, 2, 3, 0, 0, 0};
  std::vector nums2{2, 5, 6};
  int m = 3;
  int n = 3;
  Solution().merge(nums1, m, nums2, n);
  return 0;
}
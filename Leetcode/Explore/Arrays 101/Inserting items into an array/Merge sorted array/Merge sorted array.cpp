#include <algorithm>
#include <vector>

class Solution {
public:
  void merge(std::vector<int> &nums1, int m, std::vector<int> &nums2, int n);
};

void Solution::merge(std::vector<int> &nums1, int m, std::vector<int> &nums2,
                     int n) {
  auto i_it = nums1.begin();
  std::reverse(i_it, i_it + m);
  std::ranges::reverse(nums1);

  i_it += nums1.size() - m;
  auto j_it = nums2.begin();
  auto r_it = nums1.begin();

  for (; i_it != nums1.end() && j_it != nums2.end(); ++r_it) {
    if (*i_it < *j_it) {
      *r_it = *i_it;
      ++i_it;
    } else {
      *r_it = *j_it;
      ++j_it;
    }
  }

  if (i_it == nums1.end()) {
    std::copy(j_it, nums2.end(), r_it);
  } else if (j_it == nums2.end()) {
    std::copy(i_it, nums1.end(), r_it);
  }
}

int main() {
  std::vector nums1{0};
  std::vector<int> nums2{1};
  int m = 0;
  int n = static_cast<int>(nums2.size());
  Solution().merge(nums1, m, nums2, n);
  return 0;
}
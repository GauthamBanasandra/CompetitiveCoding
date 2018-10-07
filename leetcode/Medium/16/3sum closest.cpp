//
// Created by gautham on 7/10/18.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <cassert>

using FrequencyTable = std::map<int, std::size_t>;

class ClosestValue {
 public:
  explicit ClosestValue(int target) : target_(target), closest_(0), initialized_(false) {}

  bool Update(int value);
  int GetTarget() const { return target_; }

 private:
  bool initialized_;
  int target_;
  int closest_;
};

bool ClosestValue::Update(int value) {
  if (!initialized_) {
    closest_ = value;
    initialized_ = true;
    return true;
  }

  if (std::abs(target_ - value) < std::abs(target_ - closest_)) {
    closest_ = value;
    return true;
  }
  return false;
}

struct ClosestInfo {
  ClosestInfo(bool is_closest, int value) : is_closest(is_closest), value(value) {}

  bool is_closest;
  int value;
};

class Solution {
 public:
  int threeSumClosest(const std::vector<int> &nums, int target) const;

 private:
  void Select(FrequencyTable &f, int element) const;
  ClosestInfo UpdateClosest(int a, int b, int c, const FrequencyTable &f, ClosestValue &closest) const;
};

int Solution::threeSumClosest(const std::vector<int> &nums, int target) const {
  auto sum = 0;
  FrequencyTable f;
  ClosestValue closest(target);

  for (auto num : nums) {
    ++f[num];
  }

  for (std::size_t i = 0, nums_len = nums.size(); i < nums_len; ++i) {
    auto a = nums[i];
    Select(f, a);

    for (std::size_t j = i + 1; j < nums_len; ++j) {
      auto b = nums[j];
      Select(f, b);

      auto c = target - (a + b);
      auto info = UpdateClosest(a, b, c, f, closest);
      if (info.is_closest) {
        sum = a + b + info.value;
      }
      ++f[b];
    }

    ++f[a];
  }
  return sum;
}

ClosestInfo Solution::UpdateClosest(int a, int b, int c, const FrequencyTable &f, ClosestValue &closest) const {
  assert(!f.empty());
  auto greater_it = std::lower_bound(f.begin(),
                                     f.end(),
                                     c,
                                     [](const std::pair<const int, std::size_t> &a, const int b) -> bool {
                                       return a.first < b;
                                     });
  auto lesser_it = std::lower_bound(f.rbegin(),
                                    f.rend(),
                                    c,
                                    [](const std::pair<const int, std::size_t> &a, const int b) -> bool {
                                      return a.first > b;
                                    });

  assert((greater_it != f.end()) || (lesser_it != f.rend()));
  if (greater_it == f.end()) {
    return {closest.Update(a + b + lesser_it->first), lesser_it->first};
  }
  if (lesser_it == f.rend()) {
    return {closest.Update(a + b + greater_it->first), greater_it->first};
  }

  auto target = closest.GetTarget();
  if (std::abs(target - lesser_it->first) < std::abs(target - greater_it->first)) {
    return {closest.Update(a + b + lesser_it->first), lesser_it->first};
  } else {
    return {closest.Update(a + b + greater_it->first), greater_it->first};
  }
}

void Solution::Select(FrequencyTable &f, int element) const {
  auto it = f.find(element);
  assert(it != f.end());

  --it->second;
  if (it->second == 0) {
    f.erase(it);
  }
}

int main() {
  auto target = -9;
  std::vector<int> nums
      {35, 28, 94, 27, 0, 1, -89, -20, 60, -51, 35, 67, -94, -78, -67, -60, 52, 40, -4, 99, -26, -26, -77, 61, -28, 9,
       66, -40, -2, 45, 59, -37, 59, -90, 76, 100, 20, 83, 37, -65, 20, -95, 16, -77, -18, 53, 93, -88, -33, 46, -30,
       -77, -36, 79, 34, -3, -84, 72, -66, -84, -36, 94, -26, 11, -23, 35, 1, 36, -70, 76, -24, 91, -9, -73, 43, -92,
       93, 39, 99, 44, 73, 7, 90, -77, -92, -62, -63, 90, -81, 80, 18, 68, -89, 95, -22, 74, -50, -34, 58, -64, 61, -30,
       44, -28, 48, 13, -45, -75, 19, 86, 40, 68, 74, -62, 44, -12, -18, 61, 95, 53, -63, 6, 46, -74, 82, -39, -52, -45,
       -41, 55, 99, 22, 41, -45, -37, -9, -62, -41, 28, 5, -40, -99, -83, 49, 15, 75, -36, 97, 79, -45, -4, -82, -2, 6,
       3, -7, -21, 68, 81, 94, -87, 76, 64, -32, 80, -91, 65, -84, -61, -64, 68, -73, 8, -25, 23, 51, 53, -30, 65, 92,
       73, -96, 20, 70, 0, 10, -37, 90, 90, 0};
  std::cout << Solution().threeSumClosest(nums, target) << std::endl;
  return 0;
}

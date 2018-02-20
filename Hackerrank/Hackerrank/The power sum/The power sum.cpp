//
// Created by gauth on 20-02-2018.
//

#include <iostream>
#include <list>
#include <vector>

using ull = unsigned long long;

void Print(const std::list<ull> &nums);

ull pow(ull b, ull e) {
  ull p = 1;
  while (e--) {
    p *= b;
  }

  return p;
}

ull add_all(const std::list<ull> &nums) {
  ull sum = 0;
  for (auto n : nums) {
    sum += n;
  }

  return sum;
}

int main() {
  ull x, n, count = 0;
  std::vector<ull> nums;
  std::list<ull> nums_subset;

  std::cin >> x >> n;
  for (ull i = 1; i <= x; ++i) {
    auto p = pow(i, n);
    if (p <= x) {
      nums.emplace_back(p);
    } else {
      break;
    }
  }

  auto ns = pow(2, nums.size());
  for (ull i = 0; i < ns; ++i) {
    auto i_ = i;
    ull c = 0;
    nums_subset.clear();
    while (i_) {
      if (i_ & 1) {
        nums_subset.emplace_back(nums[c]);
      }

      ++c;
      i_ >>= 1;
    }

//    Print(nums_subset);
    if (add_all(nums_subset) == x) {
      ++count;
    }
  }

  std::cout << count << std::endl;
  return 0;
}
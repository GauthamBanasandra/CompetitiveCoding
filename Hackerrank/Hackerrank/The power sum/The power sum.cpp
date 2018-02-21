//
// Created by gauth on 20-02-2018.
//

#include <iostream>
#include <vector>

using ull = unsigned long long;

ull pow(ull b, ull e) {
  ull p = 1;
  while (e--) {
    p *= b;
  }

  return p;
}

int main() {
  ull x, n, count = 0;
  std::vector<ull> nums;

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
    ull c = 0, sum = 0;
    while (i_) {
      if (i_ & 1) {
        sum += nums[c];
      }

      if (sum > x) {
        break;
      }

      ++c;
      i_ >>= 1;
    }

    if (sum == x) {
      ++count;
    }
  }

  std::cout << count << std::endl;
  return 0;
}
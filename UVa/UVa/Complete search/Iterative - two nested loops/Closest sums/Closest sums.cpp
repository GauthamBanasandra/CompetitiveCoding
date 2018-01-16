//
// Created by gauth on 16-01-2018.
//

#include <iostream>
#include <vector>
#include <list>

using ll = long long;

int main() {
  int n, m, c = 0;
  ll d, q, closest_sum;
  std::vector<ll> nums;
  std::list<ll> pair_sum;

  while (std::cin >> n, n != 0) {
    nums.clear();
    pair_sum.clear();
    nums.assign(n, 0);
    for (int i = 0; i < n; ++i) {
      std::cin >> nums[i];
    }

    for (int i = 0; i < n - 1; ++i) {
      for (int j = i + 1; j < n; ++j) {
        pair_sum.emplace_back(nums[i] + nums[j]);
      }
    }

    printf("Case %d:\n", ++c);
    std::cin >> m;
    for (int i = 1; i <= m; ++i) {
      std::cin >> q;
      auto d_init = false;
      for (const auto &sum : pair_sum) {
        if (!d_init) {
          d = sum < q ? q - sum : sum - q;
          closest_sum = sum;
          d_init = true;
        } else if ((sum < q ? q - sum : sum - q) < d) {
          d = sum < q ? q - sum : sum - q;
          closest_sum = sum;
        }
      }

      printf("Closest sum to %lld is %lld.\n", q, closest_sum);
    }
  }

  return 0;
}
//
// Created by gauth on 10-02-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>

using ll = long long;
using ui = unsigned int;

int main() {
  ui t, n;
  ll x;
  std::vector<ll> v1;
  std::vector<ll> v2;

  std::cin >> t;
  for (ui c = 1; c <= t; ++c) {
    std::cin >> n;
    v1.clear();
    v2.clear();

    for (ui i = 0; i < n; ++i) {
      std::cin >> x;
      v1.emplace_back(x);
    }

    for (ui i = 0; i < n; ++i) {
      std::cin >> x;
      v2.emplace_back(x);
    }

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    ll sum = 0;
    auto i = v1.begin();
    auto j = v2.rbegin();
    for (; i != v1.end() && j != v2.rend(); ++i, ++j) {
      sum += (*i) * (*j);
    }

    printf("Case #%u: %lld\n", c, sum);
  }

  return 0;
}
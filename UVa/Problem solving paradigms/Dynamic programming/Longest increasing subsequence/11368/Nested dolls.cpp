// WA

#include <algorithm>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

size_t GetMinNestingLevel(std::vector<std::pair<int, int>> &measurements) {
  std::sort(measurements.begin(), measurements.end());

  std::vector<int> lis;
  lis.reserve(measurements.size());
  for (const auto &[_, height] : measurements) {
    auto it = std::lower_bound(lis.begin(), lis.end(), height);
    if (it == lis.end()) {
      lis.emplace_back(height);
    } else {
      *it = height;
    }
  }

  const auto lis_len = lis.size();
  lis.clear();

  std::sort(
      measurements.begin(), measurements.end(),
      [](const std::pair<int, int> &a, const std::pair<int, int> &b) -> bool {
        return a.second == b.second ? a.first < b.first : a.second < b.second;
      });
  for (const auto &[width, _] : measurements) {
    auto it = std::lower_bound(lis.begin(), lis.end(), width);
    if (it == lis.end()) {
      lis.emplace_back(width);
    } else {
      *it = width;
    }
  }
  return std::max(lis_len, lis.size()) - 1;
}

int main(int argc, char *argv[]) {
  size_t t, m;
  std::vector<std::pair<int, int>> measurements;

  std::cin >> t;
  while (t--) {
    std::cin >> m;
    measurements.resize(m);
    for (size_t i = 0; i < m; ++i) {
      std::cin >> measurements[i].first >> measurements[i].second;
    }

    std::cout << GetMinNestingLevel(measurements) << std::endl;
  }
  return 0;
}

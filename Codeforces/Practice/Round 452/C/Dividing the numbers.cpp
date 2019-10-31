#include <cassert>
#include <cmath>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

namespace round_452 {
std::pair<int, std::vector<int>> Partition(const int n) {
  std::vector<int> partition;
  partition.reserve(static_cast<size_t>(n) >> 1);
  const auto len = static_cast<int>(std::ceil(static_cast<double>(n) / 4));

  if ((n & 1) == 1 && (n >> 1 & 1) == 1) {
    for (auto i = 2; i <= len; ++i) {
      partition.push_back(i);
      partition.push_back(n - i + 2);
    }
    partition.emplace_back(1);
    partition.push_back(
        static_cast<int>(std::ceil(static_cast<double>(n) / 2)));
    return {0, std::move(partition)};
  }

  if ((n & 1) == 1 && (n >> 1 & 1) == 0) {
    for (auto i = 2; i <= len; ++i) {
      partition.push_back(i);
      partition.push_back(n - i + 2);
    }
    partition.emplace_back(1);
    return {1, partition};
  }

  if ((n & 1) == 0 && (n >> 1 & 1) == 1) {
    for (auto i = 1; i < len; ++i) {
      partition.push_back(i);
      partition.push_back(n - i + 1);
    }
    partition.push_back(n >> 1);
    return {1, partition};
  }

  if ((n & 1) == 0 && (n >> 1 & 1) == 0) {
    for (auto i = 1; i <= len; ++i) {
      partition.push_back(i);
      partition.push_back(n - i + 1);
    }
    return {0, partition};
  }

  assert(false);
  return {-1, partition};
}
} // namespace round_452

int main(int argc, char *argv[]) {
  int n;
  std::cin >> n;

  auto [min_difference, partition] = round_452::Partition(n);
  std::cout << min_difference << std::endl;
  std::cout << partition.size();
  for (const auto &number : partition) {
    std::cout << " " << number;
  }
  std::cout << std::endl;
  return 0;
}

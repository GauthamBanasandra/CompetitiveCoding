//
// Created by Gautham on 07-11-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <ios>

using ll = long long;

std::size_t GetMaxInterceptions(const std::vector<int> &heights) {
  std::vector<int> sequence;
  sequence.reserve(heights.size());

  for (const auto height : heights) {
    auto find_it = std::upper_bound(sequence.begin(), sequence.end(), height, std::greater<int>());
    if (find_it == sequence.end()) {
      sequence.emplace_back(height);
    }

    *find_it = height;
  }
  return sequence.size();
}

int main() {
  std::ios::sync_with_stdio(false);

  int height;
  std::vector<int> heights;

  for (ll i = 1; true; ++i) {
    std::cin >> height;
    if (height == -1) {
      break;
    }

    heights.clear();
    heights.emplace_back(height);
    while (std::cin >> height, height != -1) {
      heights.emplace_back(height);
    }

    if (i > 1) {
      std::cout << std::endl;
    }
    std::cout << "Test #" << i << ":\n  maximum possible interceptions: " << GetMaxInterceptions(heights) << std::endl;
  }
  return 0;
}
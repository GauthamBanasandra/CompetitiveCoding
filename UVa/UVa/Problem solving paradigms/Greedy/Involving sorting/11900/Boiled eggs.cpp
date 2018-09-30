//
// Created by gautham on 30/9/18.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include <ios>

int MaxEggsCount(const std::vector<int> &weights, int p, int q) {
  auto weight_sum = 0;
  int num_eggs;
  for (num_eggs = 0; num_eggs < static_cast<int>(weights.size()); ++num_eggs) {
    if (weight_sum + weights[num_eggs] > q) {
      break;
    }
    weight_sum += weights[num_eggs];
  }

  return std::min(p, num_eggs);
}

int main() {
  std::ios::sync_with_stdio(false);

  int p, q, t;
  std::size_t n;
  std::vector<int> weights;

  std::cin >> t;
  for (auto j = 1; j <= t; ++j) {
    std::cin >> n >> p >> q;

    weights.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> weights[i];
    }

    std::cout << "Case " << j << ": " << MaxEggsCount(weights, p, q) << std::endl;
  }
  return 0;
}
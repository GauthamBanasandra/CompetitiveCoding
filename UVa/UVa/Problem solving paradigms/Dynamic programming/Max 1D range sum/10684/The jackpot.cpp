//
// Created by Gautham Banasandra on 13/10/18.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <ios>

using ll = long long;

ll GetPatternInfo(const std::vector<int> &bets) {
  ll sum = 0;
  ll maximum = 0;

  for (const auto bet : bets) {
    sum += bet;
    maximum = std::max(maximum, sum);
    if (sum < 0) {
      sum = 0;
    }
  }
  return maximum;
}

int main() {
  std::ios::sync_with_stdio(false);

  std::size_t n;
  std::vector<int> bets{-4, -10};

  while (std::cin >> n, n) {
    bets.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> bets[i];
    }

    const auto winning_streak = GetPatternInfo(bets);
    if (winning_streak == 0) {
      std::cout << "Losing streak." << std::endl;
    } else {
      std::cout << "The maximum winning streak is " << winning_streak << "." << std::endl;
    }
  }
  return 0;
}
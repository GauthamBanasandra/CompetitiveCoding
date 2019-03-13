//
// Created by Gautham on 24-12-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>

using ll = long long;

class CoinCounter {
 public:
  CoinCounter();

  ll Count(int change) { return Count(0, change); }

 private:
  ll Count(std::size_t i, int change);

  std::vector<int> denominations_;
  std::vector<std::vector<ll>> memo_;
};

CoinCounter::CoinCounter() : denominations_({1, 5, 10, 25, 50}) {
  memo_.resize(denominations_.size(), std::vector<ll>(30000 + 1, -1));
}

ll CoinCounter::Count(std::size_t i, int change) {
  if (i >= denominations_.size() || change < 0) {
    return 0;
  }

  if (change == 0) {
    return 1;
  }

  auto &memo = memo_[i][change];
  if (memo != -1) {
    return memo;
  }
  return memo = Count(i + 1, change) + Count(i, change - denominations_[i]);
}

int main() {
  int cents;
  CoinCounter counter;
  while (std::cin >> cents, !std::cin.eof()) {
    auto ways = counter.Count(cents);
    if (ways == 1) {
      std::cout << "There is only 1 way to produce " << cents << " cents change." << std::endl;
    } else {
      std::cout << "There are " << ways << " ways to produce " << cents << " cents change." << std::endl;
    }
  }
  return 0;
}
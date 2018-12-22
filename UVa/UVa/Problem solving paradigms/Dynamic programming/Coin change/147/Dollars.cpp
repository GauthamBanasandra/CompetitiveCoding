//
// Created by Gautham on 22-12-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ios>

class CoinCounter {
 public:
  explicit CoinCounter(std::size_t max_currency);
  long Count(int value) { return Count(0, value); }

 private:
  long Count(std::size_t i, int value);

  const std::vector<int> denominations_;
  std::vector<std::vector<long>> memo_;
};

CoinCounter::CoinCounter(std::size_t max_currency) : denominations_({10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10,
                                                                     5}) {
  memo_.resize(denominations_.size(), std::vector<long>(max_currency + 1, -1));
}

long CoinCounter::Count(std::size_t i, int value) {
  if (i >= denominations_.size() || value < 0) {
    return 0;
  }

  if (value == 0) {
    return 1;
  }

  auto &memo = memo_[i][value];
  if (memo != -1) {
    return memo;
  }
  return memo = Count(i + 1, value) +
      // In Knapsack, if an item is picked once, it can't be picked again. So, we move to the next item by F(i + 1, remV - V[i])
      // But in Coin change, since there are no limits on the number of coins, we can still pick the same denomination
      // any number of times. So, we do F(i, remV - V[i])
      Count(i, value - denominations_[i]);
}

int main() {
  std::ios::sync_with_stdio(false);

  std::string currency;
  CoinCounter counter(300000);

  while (std::cin >> currency, !std::cin.eof()) {
    std::string cents(currency);
    cents.erase(cents.begin() + cents.find('.'));
    auto value = std::stoi(cents);
    if (value == 0) {
      break;
    }
    std::cout.width(6);
    std::cout << std::right << currency;
    std::cout.width(17);
    std::cout << std::right << counter.Count(value) << std::endl;
  }
  return 0;
}
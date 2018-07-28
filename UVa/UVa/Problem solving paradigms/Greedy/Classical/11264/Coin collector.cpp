//
// Created by gautham on 28/7/18.
//

// WA

#include <algorithm>
#include <vector>
#include <iostream>

class CoinSelector {
 public:
  explicit CoinSelector(std::vector<long> coins) : coins_(std::move(coins)) {}

  int Select() const;

 private:
  int Withdraw(long sum) const;

 public:
  std::vector<long> coins_;
};

int CoinSelector::Select() const {
  int max_num_coins = 0;
  long sum = std::accumulate(coins_.begin(), coins_.end(), 0l);

  for (auto rev_it = coins_.rbegin(); rev_it != coins_.rend(); ++rev_it) {
    auto num_coins = Withdraw(sum);
    max_num_coins = std::max(num_coins, max_num_coins);
    sum -= *rev_it;
  }

  return max_num_coins;
}

int CoinSelector::Withdraw(long sum) const {
  int num_coins = 0;
  for (auto rev_it = coins_.rbegin(); rev_it != coins_.rend(); ++num_coins) {
    rev_it = std::lower_bound(rev_it, coins_.rend(), sum, std::greater<long>());
    if (rev_it == coins_.rend()) {
      break;
    }

    auto num = *rev_it;
    sum %= *rev_it;
  }

  return num_coins;
}

int main() {
  long t;
  int n;
  std::vector<long> numbers{1, 5, 9, 74, 111, 121, 159};
  std::cout << CoinSelector(numbers).Select() << std::endl;

  /*std::cin >> t;
  for (int i = 0; i < t; ++i) {
    std::cin >> n;
    numbers.resize(static_cast<std::size_t>(n));

    for (std::size_t j = 0; j < n; ++j) {
      std::cin >> numbers[j];
    }

    std::cout << CoinSelector(numbers).Select() << std::endl;
  }
*/
  return 0;
}
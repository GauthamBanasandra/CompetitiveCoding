//
// Created by gautham on 11/9/18.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <ios>

using ll = long long;

class Advisor {
 public:
  explicit Advisor(std::vector<int> prices);
  ll GetMaxDiscount() const;

 private:
  std::vector<int> prices_;
};

Advisor::Advisor(std::vector<int> prices) : prices_(std::move(prices)) {
  std::sort(prices_.begin(), prices_.end(), std::greater<int>());
}

ll Advisor::GetMaxDiscount() const {
  ll discount = 0;

  for (std::size_t i = 0; i < prices_.size(); ++i) {
    if ((i + 1) % 3) {
      continue;
    }

    discount += prices_[i];
  }
  return discount;
}

int main() {
  std::ios::sync_with_stdio(false);

  short t;
  std::size_t n;
  std::vector<int> prices;

  std::cin >> t;
  while (t-- > 0) {
    std::cin >> n;
    prices.resize(n);

    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> prices[i];
    }
    std::cout << Advisor(prices).GetMaxDiscount() << std::endl;
  }
  return 0;
}
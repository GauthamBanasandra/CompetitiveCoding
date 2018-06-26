//
// Created by Gautham Banasandra on 16/06/18.
//

#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>

using ul = unsigned long;

void Print(const std::vector<ul> &primes);

class PaymentOptions {
 public:
  PaymentOptions();
  ul Count(ul n);

  static std::vector<ul> primes_;

 private:
  static void InitializePrimes();
};

std::vector<ul> PaymentOptions::primes_;

void PaymentOptions::InitializePrimes() {
  if (!primes_.empty()) {
    return;
  }

  ul max_num = 1000003;
  primes_.resize(max_num, 0);
  for (std::size_t p = 2; p <= max_num; ++p) {
    primes_[p] = p;
  }

  auto sqrt_n = static_cast<ul>(std::floor(std::sqrt(max_num)));
  for (std::size_t p = 2; p <= sqrt_n; ++p) {
    if (primes_[p] == 0) {
      continue;
    }

    for (auto j = p * p; j <= max_num; j += p) {
      primes_[j] = 0;
    }
  }

  primes_.erase(std::remove(primes_.begin(), primes_.end(), 0), primes_.end());
}

PaymentOptions::PaymentOptions() {
  InitializePrimes();
}

ul PaymentOptions::Count(ul n) {
  ul num_ways = 0;
  auto greatest_coin_it = std::lower_bound(primes_.rbegin(), primes_.rend(), n, std::greater<ul>());
  auto half_it = std::lower_bound(greatest_coin_it, primes_.rend(), n / 2, std::greater<ul>());

  for (auto it = half_it; it != primes_.rend(); ++it) {
    auto coin_it = std::lower_bound(greatest_coin_it, it, n - *it, std::greater<ul>());
    auto distance = std::distance(coin_it, it);
    assert(distance >= 0);
    num_ways += distance;
  }

  return num_ways;
}

int main() {
  std::ios::sync_with_stdio(false);
  ul n = 0;

  std::cin >> n;
  for (ul i = 1; n; ++i, std::cin >> n) {
    std::cout << "Case " << i << ": " << PaymentOptions().Count(n) << std::endl;
  }

  return 0;
}
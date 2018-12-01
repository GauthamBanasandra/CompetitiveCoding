//
// Created by Gautham on 01-12-2018.
//

#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;
void Print(const std::vector<std::vector<ll>> &matrix);

class Partition {
 public:
  explicit Partition(std::vector<ll> coins);

  ll Halve() const;

 private:
  ll Halve(std::size_t i, ll rem_v) const;

  std::vector<ll> coins_;
  mutable std::vector<std::vector<ll>> memo_;
};

Partition::Partition(std::vector<ll> coins) : coins_(std::move(coins)) {
  auto len = coins_.size();
  ll sum = 0;
  for (const auto &coin : coins_) {
    sum += coin;
  }

  memo_.resize(len);
  for (auto &memo : memo_) {
    memo.resize(static_cast<std::size_t>(sum) + 1, -1);
  }
}

ll Partition::Halve() const {
  ll sum = 0;
  for (const auto &coin : coins_) {
    sum += coin;
  }
  auto sum_half = sum / 2;
  auto max_half = Halve(0, sum_half);
//  Print(memo_);
  return sum - 2 * max_half;
}

ll Partition::Halve(std::size_t i, ll rem_v) const {
  auto len = coins_.size();
  if (i >= len) {
    return 0;
  }

  if (coins_[i] > rem_v) {
    return Halve(i + 1, rem_v);
  }

  if (memo_[i][rem_v] != -1) {
    return memo_[i][rem_v];
  }

  memo_[i][rem_v] = std::max(Halve(i + 1, rem_v), Halve(i + 1, rem_v - coins_[i]) + coins_[i]);
  return memo_[i][rem_v];
}

int main() {
  std::size_t t, num_coins;
  std::vector<ll> coins
      {264, 362, 493, 239, 22, 227, 195, 455, 437, 180, 312, 126, 72, 270, 447, 153, 374, 448, 276, 297, 169, 448, 415,
       392, 99, 24, 153, 448, 68, 381, 40, 332, 242, 384, 422, 116, 110, 468, 422, 46, 147, 233, 23, 71, 3, 470, 223,
       228, 417, 351, 377, 85, 298, 291, 476, 249, 314, 480, 196, 233, 360, 87, 416, 454, 471, 337, 421, 80, 304, 342,
       478, 303, 74, 500, 225, 428, 469, 447, 156, 385, 149, 32, 321, 447, 322, 148, 47, 487, 127, 94, 71, 487, 181,
       487};

  std::cin >> t;
  while (t--) {
    std::cin >> num_coins;
    coins.resize(num_coins);
    for (std::size_t i = 0; i < num_coins; ++i) {
      std::cin >> coins[i];
    }
    std::cout << Partition(coins).Halve() << std::endl;
  }
  return 0;
}
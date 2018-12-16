//
// Created by Gautham on 16-12-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using ll = long long;

class Coalition {
 public:
  Coalition(const std::vector<double> &shares, std::size_t i_opt);
  double Coalesce();

 private:
  ll Coalesce(std::size_t i, ll sum);

  const std::size_t i_opt_;
  std::vector<int> shares_;
  std::vector<std::vector<ll>> memo_;
};

Coalition::Coalition(const std::vector<double> &shares, std::size_t i_opt) : i_opt_(i_opt) {
  shares_.resize(shares.size());
  for (std::size_t i = 0, len = shares.size(); i < len; ++i) {
    shares_[i] = static_cast<int>(shares[i] * 1000) / 10;
  }

  memo_.resize(shares_.size());
  for (auto &row : memo_) {
    row.resize(10001, -1);
  }
}

double Coalition::Coalesce() {
  auto c = Coalesce(0, shares_[i_opt_]);
  auto d = static_cast<double>(shares_[i_opt_]) / c;
  return d * 100.0f;
}

ll Coalition::Coalesce(std::size_t i, ll sum) {
  if (i >= shares_.size() || sum > 5000) {
    return sum;
  }

  if (i == i_opt_) {
    return Coalesce(i + 1, sum);
  }

  auto &memo = memo_[i][sum];
  if (memo != -1) {
    return memo;
  }

  auto exclude = Coalesce(i + 1, sum);
  auto include = Coalesce(i + 1, sum + shares_[i]);

  if (exclude > 5000 && include <= 5000) {
    return memo = exclude;
  }
  if (exclude <= 5000 && include > 5000) {
    return memo = include;
  }
  return memo = std::abs(5001 - exclude) < std::abs(5001 - include) ? exclude : include;
}

int main() {
//  std::size_t i_opt = 5;
//  std::size_t i_opt = 1;
//  std::size_t i_opt = 2;
//  std::size_t i_opt = 1;
  std::size_t i_opt = 7, num_shares = 0;
//  std::size_t i_opt = 5, num_shares = 0;
  std::vector<double> shares{
      /*20.00,
      12.00,
      29.00,
      14.00,
      25.00*/

      /*56.87,
      43.13*/

      /*56.87,
      43.13*/

      /*10.00,
      45.00,
      45.00*/

      2.44,
      5.46,
      0.68,
      0.02,
      2.04,
      4.34,
      4.14,
      5.50,
      1.99,
      0.62,
      1.47,
      1.82,
      7.24,
      0.28,
      4.84,
      5.60,
      4.11,
      4.96,
      2.86,
      5.66,
      6.54,
      7.84,
      7.10,
      2.87,
      3.71,
      2.87,
      1.23,
      1.77

      /*24.75,
      23.21,
      20.51,
      9.19,
      22.34*/
  };

//  printf("%.2f\n", Coalition(shares, i_opt - 1).Coalesce());
  std::size_t tc = 1;
  while (std::cin >> num_shares >> i_opt, num_shares || i_opt) {
    shares.resize(num_shares);
    for (std::size_t i = 0; i < num_shares; ++i) {
      std::cin >> shares[i];
    }
    printf("%.2f\n", Coalition(shares, i_opt - 1).Coalesce());
    ++tc;
  }
  return 0;
}
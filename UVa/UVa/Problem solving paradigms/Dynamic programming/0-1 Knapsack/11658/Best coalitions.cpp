//
// Created by Gautham on 16-12-2018.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>

using ll = int;

class Coalition {
 public:
  Coalition(const std::vector<std::string> &shares, std::size_t i_opt);
  double Coalesce();

 private:
  ll Coalesce(std::size_t i, ll sum);
  int RemoveDecimalPoint(const std::string &num_str) const;

  const std::size_t i_opt_;
  std::vector<int> shares_;
  std::vector<std::vector<ll>> memo_;
};

Coalition::Coalition(const std::vector<std::string> &shares, std::size_t i_opt) : i_opt_(i_opt) {
  shares_.resize(shares.size());
  for (std::size_t i = 0, len = shares.size(); i < len; ++i) {
    shares_[i] = RemoveDecimalPoint(shares[i]);
  }

  memo_.resize(shares_.size());
  for (auto &row : memo_) {
    row.resize(10001, -1);
  }
}

double Coalition::Coalesce() {
  return (static_cast<double>(shares_[i_opt_]) / Coalesce(0, shares_[i_opt_])) * 100.0f;
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

  // The share sum must be greater than 50.00
  if (exclude > 5000 && include <= 5000) {
    return memo = exclude;
  }
  if (exclude <= 5000 && include > 5000) {
    return memo = include;
  }
  // At this point, the share sum of both "include" and "exclude" are either greater than 5000 or less than equal to 5000
  // So, we just memoize the one nearest to 5001 (because it must be greater than 50.01)
  return memo = std::abs(5001 - exclude) < std::abs(5001 - include) ? exclude : include;
}

int Coalition::RemoveDecimalPoint(const std::string &num_str) const {
  std::string num(num_str);
  // This is equivalent to multiplying by 100
  // This is necessary as we need to memoize the state of share sum
  // Since share sum is in decimal, we are naturalizing it by removing the decimal point
  num.erase(num.begin() + num.find('.'));
  return std::stoi(num);
}

int main() {
  std::size_t i_opt = 7, num_shares = 0;

  // Using a vector of string because reading as float/double itself causes loss of precision
  // For example, try reading 4.14. It will be read as 4.13.
  std::vector<std::string> shares;

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
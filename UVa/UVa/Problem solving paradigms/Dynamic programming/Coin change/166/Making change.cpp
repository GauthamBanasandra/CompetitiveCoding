//
// Created by Gautham Banasandra on 2018-12-23.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <cassert>

const auto infinity = std::numeric_limits<int>::max();

enum CoinType {
  k5,
  k10,
  k20,
  k50,
  k100,
  k200,
  Count
};

struct Denomination {
  Denomination(CoinType type, long count);

  CoinType type;
  int value;
  std::size_t count;
};

Denomination::Denomination(CoinType type, long count) : type(type), count(count) {
  switch (type) {
    case k5: value = 5;
      break;
    case k10:value = 10;
      break;
    case k20:value = 20;
      break;
    case k50:value = 50;
      break;
    case k100:value = 100;
      break;
    case k200:value = 200;
      break;
  }
}

class ShopKeeper {
 public:
  explicit ShopKeeper(std::size_t max_value);

  int Count(int change);

 protected:
  std::vector<Denomination> denominations_;

 private:
  std::vector<int> memo_;
};

ShopKeeper::ShopKeeper(std::size_t max_value) : denominations_({{k5, infinity}, {k10, infinity}, {k20, infinity},
                                                                {k50, infinity}, {k100, infinity}, {k200, infinity}}) {
  memo_.resize(max_value + 1, -1);
}

int ShopKeeper::Count(int change) {
  if (change < 0) {
    return infinity;
  }

  if (change == 0) {
    return 0;
  }

  auto &memo = memo_[change];
  if (memo != -1) {
    return memo;
  }

  auto min_change = infinity;
  for (auto &denomination : denominations_) {
    min_change = std::min(min_change, Count(change - denomination.value));
  }
  return memo = min_change == infinity ? infinity : 1 + min_change;
}

struct CoinIterator {
 public:
  CoinIterator(const std::vector<Denomination> &denominations)
      : i_denomination(0), i_count(0), denominations(denominations) {}

  int Next(int offset);

 private:
  std::size_t i_denomination;
  std::size_t i_count;
  const std::vector<Denomination> &denominations;
};

int CoinIterator::Next(int offset) {
  if (i_denomination >= denominations.size()) {
    return -1;
  }

  const auto &denomination = denominations[i_denomination];
  if (i_count >= denomination.count) {
    i_count = 0;
    ++i_denomination;
    return Next(offset);
  }
  ++i_count;
  return denomination.value + offset;
}

class Customer {
 public:
  explicit Customer(std::vector<Denomination> &denominations);

  CoinIterator GetCoinIterator() const { return {denominations_}; }
  int GetBudget() const { return budget_; }

  int Count(int change);

 private:
  int Count(size_t i_denomination, std::size_t i_coin, int change);

  int budget_;
  std::vector<Denomination> denominations_;
  std::vector<std::vector<std::vector<int>>> memo_;
};

Customer::Customer(std::vector<Denomination> &denominations)
    : budget_(0), denominations_(denominations) {
  for (const auto &denomination : denominations_) {
    budget_ += denomination.value * denomination.count;
  }

  memo_.resize(denominations_.size());
  std::vector<int> row(budget_ + 1, -1);
  for (std::size_t i = 0, len = denominations_.size(); i < len; ++i) {
    memo_[i].resize(static_cast<std::size_t>(denominations_[i].count), row);
  }
}

int Customer::Count(int change) {
  return Count(0, denominations_[0].count, change);
}

int Customer::Count(std::size_t i_denomination, std::size_t i_coin, int change) {
  if (change < 0 || i_denomination >= denominations_.size()) {
    return infinity;
  }
  if (change == 0) {
    return 0;
  }

  if (i_coin == 0) {
    return Count(i_denomination + 1,
                 i_denomination + 1 >= denominations_.size() ? infinity : denominations_[i_denomination + 1].count,
                 change);
  }

  auto &memo = memo_[i_denomination][i_coin - 1][change];
  if (memo != -1) {
    return memo;
  }

  auto min_change = infinity;
  for (std::size_t i = 0, len = denominations_.size(); i < len; ++i) {
    auto &denomination = denominations_[i];
    if (denomination.count == 0) {
      continue;
    }
    --denomination.count;
    min_change = std::min(min_change, Count(i, denomination.count, change - denomination.value));
    ++denomination.count;
  }
  return memo = min_change == infinity ? infinity : 1 + min_change;
}

class Shop {
 public:
  explicit Shop(std::size_t max_value) : shop_keeper_(max_value) {}

  int Buy(Customer &customer, int value);

 private:
  ShopKeeper shop_keeper_;
};

int Shop::Buy(Customer &customer, int value) {
  auto min_coins = infinity;
  for (auto tender = value, budget = customer.GetBudget(); tender <= budget; tender += 5) {
    auto coins_tendered = customer.Count(tender);
    if (coins_tendered == infinity) {
      continue;
    }

    auto receive = tender - value;
    auto coins_received = shop_keeper_.Count(receive);
    if (coins_received == infinity) {
      continue;
    }
    min_coins = std::min(min_coins, coins_tendered + coins_received);
  }
  return min_coins;
}

int main() {
  auto value = 400;
//  auto value = 315;
  std::string value_str;
  Shop shop(1000000);
  std::vector<Denomination> denominations{
      {k5, 0},
      {k10, 0},
      {k20, 0},
      {k50, 0},
      {k100, 2},
      {k200, 1},

      /*{k5, 0},
      {k10, 0},
      {k20, 6},
      {k50, 7},
      {k100, 8},
      {k200, 0},*/
  };

  auto &num_k5 = denominations[k5].count;
  auto &num_k10 = denominations[k10].count;
  auto &num_k20 = denominations[k20].count;
  auto &num_k50 = denominations[k50].count;
  auto &num_k100 = denominations[k100].count;
  auto &num_k200 = denominations[k200].count;

  while (std::cin >> num_k5 >> num_k10 >> num_k20 >> num_k50 >> num_k100 >> num_k200,
      num_k5 || num_k10 || num_k20 || num_k50 || num_k100 || num_k200) {
    std::cin >> value_str;
    value_str.erase(value_str.begin() + value_str.find('.'));
    value = std::stoi(value_str);

    Customer customer(denominations);
    std::cout.width(3);
    std::cout << std::right << shop.Buy(customer, value) << std::endl;
  }

  /*Customer customer(denominations);
  std::cout.width(3);
  std::cout << std::right << shop.Buy(customer, value) << std::endl;*/
  return 0;
}
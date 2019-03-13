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

struct Coin {
	Coin(CoinType type, std::size_t count);

	CoinType type;
	int value;
	std::size_t count;
};

Coin::Coin(CoinType type, std::size_t count) : type(type), count(count) {
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
	default:assert(false);
		break;
	}
}

class ShopKeeper {
public:
	explicit ShopKeeper(std::size_t max_value);

	int Count(int change);

private:
	std::vector<Coin> coins_;
	std::vector<int> memo_;
};

ShopKeeper::ShopKeeper(std::size_t max_value) : coins_({ {k5, static_cast<std::size_t>(infinity)},
	{k10, static_cast<std::size_t>(infinity)},
	{k20, static_cast<std::size_t>(infinity)},
	{k50, static_cast<std::size_t>(infinity)},
	{k100, static_cast<std::size_t>(infinity)},
	{k200, static_cast<std::size_t>(infinity)}
	}) {
	memo_.resize(max_value + 1, -1);
}

// Traditional coin change problem where infinite coins are available for any type
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
	for (auto &coin : coins_) {
		min_change = std::min(min_change, Count(change - coin.value));
	}
	return memo = min_change == infinity ? infinity : 1 + min_change;
}

struct CountInfo {
	CountInfo() : is_possible(false), count(-1) {}
	CountInfo(const bool is_possible, const int count) : is_possible(is_possible), count(count) {}

	bool is_possible;
	int count;
};

class Customer {
public:
	explicit Customer(const std::vector<Coin> &coins);

	int GetBudget() const { return budget_; }

	CountInfo Count(int change) { return Count(0, change); }

private:
	CountInfo Count(std::size_t i, int change);

	int budget_;
	std::vector<int> coins_;
	std::vector<std::vector<CountInfo>> memo_;
};

Customer::Customer(const std::vector<Coin> &coins)
	: budget_(0) {
	auto num_coins = 0;
	for (const auto &coin : coins) {
		num_coins += coin.count;
		budget_ += coin.value * coin.count;
	}

	coins_.resize(static_cast<std::size_t>(num_coins));
	std::size_t i = 0;
	for (const auto &coins : coins) {
		for (std::size_t j = 0; j < coins.count; ++j, ++i) {
			coins_[i] = coins.value;
		}
	}

	memo_.resize(static_cast<std::size_t>(num_coins), std::vector<CountInfo>(static_cast<std::size_t>(budget_) + 1));
}

// Using Knapsack to compute the minimum number of coins, when the availability of coins are limited
CountInfo Customer::Count(const std::size_t i, const int change) {
	// A valid state is represented as {true, 0}
	// This means that the sequence of operations that have been carried out will yield change == 0
	if (change == 0) {
		return { true, 0 };
	}

	// An invalid state is represented as {false, -2}
	// This means that the sequence of operations that have been carried out will not yield a change == 0
	if (i >= coins_.size()) {
		return { false, -2 };
	}

	auto &memo = memo_[i][change];
	if (memo.count != -1) {
		return memo;
	}

	if (coins_[i] > change) {
		return Count(i + 1, change);
	}

	const auto exclude = Count(i + 1, change);
	auto include = Count(i + 1, change - coins_[i]);
	// Included this coin[i], so incrementing its count
	++include.count;

	if (!exclude.is_possible && !include.is_possible) {
		// Need to memoize if the sequence of operations could not yield change == 0 to avoid recomputation
		return memo = { false, -2 };
	}

	if (!exclude.is_possible && include.is_possible) {
		return memo = include;
	}

	if (exclude.is_possible && !include.is_possible) {
		return memo = exclude;
	}

	if (exclude.count < include.count) {
		return memo = exclude;
	}
	return memo = include;
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
	// TODO : Use Knapsack to get the highest possible price that the customer can produce beyond value
	// and loop over all such possible sums
	for (auto tender = value, budget = customer.GetBudget(); tender <= budget; tender += 5) {
		auto coins_tendered = customer.Count(tender);
		if (!coins_tendered.is_possible) {
			continue;
		}

		auto receive = tender - value;
		auto coins_received = shop_keeper_.Count(receive);
		if (coins_received == infinity) {
			continue;
		}
		min_coins = std::min(min_coins, coins_tendered.count + coins_received);
	}
	return min_coins;
}

int main() {
	auto value = 150;
	std::string value_str;
	Shop shop(1000000);
	std::vector<Coin> coins{
		/*{k5, 100},
		{k10, 1},
		{k20, 1},
		{k50, 2},
		{k100, 2},
		{k200, 1},*/

		{k5, 0},
		{k10, 0},
		{k20, 6},
		{k50, 7},
		{k100, 8},
		{k200, 0},
	};

	auto &num_k5 = coins[k5].count;
	auto &num_k10 = coins[k10].count;
	auto &num_k20 = coins[k20].count;
	auto &num_k50 = coins[k50].count;
	auto &num_k100 = coins[k100].count;
	auto &num_k200 = coins[k200].count;

	while (std::cin >> num_k5 >> num_k10 >> num_k20 >> num_k50 >> num_k100 >> num_k200,
		num_k5 || num_k10 || num_k20 || num_k50 || num_k100 || num_k200) {
		std::cin >> value_str;
		value_str.erase(value_str.begin() + value_str.find('.'));
		value = std::stoi(value_str);

		Customer customer(coins);
		std::cout.width(3);
		std::cout << std::right << shop.Buy(customer, value) << std::endl;
	}

	/*Customer customer(coins);
	std::cout.width(3);
	std::cout << std::right << shop.Buy(customer, value) << std::endl;*/
	return 0;
}
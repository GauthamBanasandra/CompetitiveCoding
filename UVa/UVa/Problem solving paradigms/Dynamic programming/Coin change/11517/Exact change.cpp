#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

using ll = long long;

const auto infinity_int = std::numeric_limits<int>::max();
const auto infinity_ll = std::numeric_limits<ll>::max();
const auto minus_inf_int = std::numeric_limits<int>::min();
const auto minus_inf_ll = std::numeric_limits<ll>::min();

struct Coins
{
	Coins() :is_valid(true), amount(0), num(0) {}
	Coins(const bool is_valid) : is_valid(is_valid), amount(minus_inf_int), num(minus_inf_ll) {}
	Coins(const int amount, const ll num) :is_valid(true), amount(amount), num(num) {}

	bool is_valid;
	int amount;
	ll num;
};

class ChangeMaker
{
public:
	ChangeMaker(const std::vector<int> &coins, int target);
	Coins Count() { return Count(0, {}); }
private:
	const Coins &Min(const Coins &a, const Coins &b) const;
	Coins Count(std::size_t i, Coins cum);

	const int target_;
	const std::vector<int> &coins_;
	std::vector<std::vector<Coins>> memo_;
};

ChangeMaker::ChangeMaker(const std::vector<int>& coins, const int target) : target_(target), coins_(coins)
{
	memo_.resize(coins_.size(), std::vector<Coins>(20000, { false }));
}

const Coins& ChangeMaker::Min(const Coins& a, const Coins& b) const
{
	if (a.amount <= target_ && b.amount<= target_)
	{
		return a.num < b.num ? a : b;
	}

	return a.amount < b.amount ? a : b;
}

Coins ChangeMaker::Count(const std::size_t i, const Coins cum)
{
	assert(cum.amount <= target_);
	if (i >= coins_.size())
	{
		return { false };
	}

	assert(cum.amount < 20000);
	auto &memo = memo_[i][static_cast<std::size_t>(cum.amount)];
	if (memo.is_valid)
	{
		return memo;
	}

	const auto exclude = Count(i + 1, cum);
	Coins include{ coins_[i] + cum.amount , cum.num + 1 };
	if (include.amount <= target_)
	{
		include = Count(i + 1, include);
	}

	if (!exclude.is_valid && !include.is_valid)
	{
		return { false };
	}
	if (!exclude.is_valid && include.is_valid)
	{
		return include;
	}
	if (exclude.is_valid && !include.is_valid)
	{
		return exclude;
	}
	return memo = Min(exclude, include);
}

int main(int argc, char* argv[])
{
	/*auto target = 1400;
	std::vector<int> coin_values{
		500,
		1000,
		2000,
	};*/

	ll t;
	auto target = 100;
	std::size_t num_coin_values;
	std::vector<int> coin_values{
		50,
		25,
		27,
		26,
	};

	std::cin >> t;
	while (t-- > 0)
	{
		std::cin >> target >> num_coin_values;
		coin_values.resize(num_coin_values);
		for (std::size_t i = 0; i < num_coin_values; ++i)
		{
			std::cin >> coin_values[i];
		}

		ChangeMaker change_maker(coin_values, target);
		const auto coins = change_maker.Count();
		assert(coins.is_valid);
		std::cout << coins.amount << " " << coins.num << std::endl;
	}
	return 0;
}

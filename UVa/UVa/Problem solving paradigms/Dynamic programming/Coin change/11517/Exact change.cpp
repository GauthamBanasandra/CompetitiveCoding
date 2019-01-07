#include <iostream>
#include <vector>
#include <numeric>

using ll = long long;

struct Coins
{
	Coins() :amount(0), num(0) {}
	Coins(const int amount, const ll num) :amount(amount), num(num) {}

	int amount;
	ll num;
};

const auto infinity_int = std::numeric_limits<int>::max();
const auto infinity_ll = std::numeric_limits<ll>::max();

class ChangeMaker
{
public:
	ChangeMaker(const std::vector<int> &coins, int target);
	Coins Count() { return Count({ 0, 0 }); }

private:
	Coins Count(Coins sum);
	static const Coins &Min(const Coins &a, const Coins &b);

	const int target_;
	const std::vector<int> &coins_;
	std::vector<Coins> memo_;
};

ChangeMaker::ChangeMaker(const std::vector<int>& coins, const int target) : target_(target), coins_(coins)
{
	memo_.resize(20000, { -1, -1 });
}

Coins ChangeMaker::Count(const Coins sum)
{
	if (sum.amount >= target_)
	{
		return sum;
	}

	auto &memo = memo_[sum.amount];
	if (memo.amount != -1 && memo.num != -1)
	{
		return memo;
	}

	Coins min_coins{ infinity_int, infinity_ll };
	for (const auto& coin : coins_)
	{
		min_coins = Min(min_coins, Count({ sum.amount + coin, sum.num + 1 }));
	}
	return memo = min_coins;
}

const Coins& ChangeMaker::Min(const Coins& a, const Coins& b)
{
	if (a.num < b.num)
	{
		return a;
	}

	if (a.num == b.num)
	{
		if (a.amount < b.amount)
		{
			return a;
		}
	}
	return b;
}

int main(int argc, char* argv[])
{
	auto target = 1400;
	std::vector<int> coin_values{
		500,
		1000,
		2000,
	};

	ChangeMaker change_maker(coin_values, target);
	auto coins = change_maker.Count();
	std::cout << coins.amount << " " << coins.num << std::endl;
	return 0;
}

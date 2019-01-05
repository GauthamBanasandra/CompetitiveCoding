#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

class ChangeMaker
{
public:
	ChangeMaker();
	ll Count(const int rem) { return Count(0, rem); }

private:
	void InitializeCoins();
	ll Count(std::size_t i, int rem);

	std::vector<int> coins_;
	std::vector<std::vector<ll>> memo_;
};

ChangeMaker::ChangeMaker()
{
	InitializeCoins();
	memo_.resize(coins_.size(), std::vector<ll>(10000 + 1, -1));
}

void ChangeMaker::InitializeCoins()
{
	coins_.resize(21);
	auto i = 0;
	std::generate(coins_.begin(), coins_.end(), [&i]()->auto
	{
		++i;
		return i * i * i;
	});
}

ll ChangeMaker::Count(const std::size_t i, const int rem)
{
	if (i >= coins_.size() || rem < 0)
	{
		return 0;
	}

	if (rem == 0)
	{
		return 1;
	}

	auto &memo = memo_[i][rem];
	if (memo != -1)
	{
		return memo;
	}

	return memo = Count(i + 1, rem) + Count(i, rem - coins_[i]);
}

int main(int argc, char* argv[])
{
	int amount;
	ChangeMaker change_maker;

	while (std::cin >> amount, !std::cin.eof())
	{
		std::cout << change_maker.Count(amount) << std::endl;
	}
	return 0;
}

#include <vector>
#include <iostream>

class ChangeMaker
{
public:
	ChangeMaker(const std::vector<int> &coins, std::size_t n);
	long Count() { return Count(0, n_); }

private:
	long Count(std::size_t i_coin, long rem);

	const long n_;
	const std::vector<int> &coins_;
	std::vector<std::vector<long>> memo_;
};

ChangeMaker::ChangeMaker(const std::vector<int>& coins, const std::size_t n) :n_(static_cast<long>(n)), coins_(coins)
{
	memo_.resize(coins_.size(), std::vector<long>(n + 1, -1));
}

long ChangeMaker::Count(const std::size_t i_coin, const long rem)
{
	if (rem == 0)
	{
		return 1;
	}
	if (rem < 0 || i_coin >= coins_.size())
	{
		return 0;
	}	

	auto &memo = memo_[i_coin][static_cast<std::size_t>(rem)];
	if (memo != -1)
	{
		return memo;
	}

	const auto exclude = Count(i_coin + 1, rem);
	const auto include = Count(i_coin, rem - coins_[i_coin]);
	return memo = exclude + include;
}

int main(int argc, char* argv[])
{
	std::size_t m;
	long n = 4;
	std::vector<int> coins{ 1, 2, 3 };

	std::cin >> n >> m;
	coins.resize(m);
	for (std::size_t i = 0; i < m; ++i)
	{
		std::cin >> coins[i];
	}

	ChangeMaker change_maker(coins, n);
	std::cout << change_maker.Count() << std::endl;
	return 0;
}

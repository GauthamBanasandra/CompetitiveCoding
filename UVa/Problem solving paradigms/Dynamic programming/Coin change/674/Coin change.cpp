#include <iostream>
#include <vector>
#include <ios>

class ChangeMaker
{
public:
	ChangeMaker();
	long Count(const int change) { return Count(0, change); }

private:
	long Count(std::size_t i, int change);

	std::vector<int> coins_;
	std::vector<std::vector<long>> memo_;
};

ChangeMaker::ChangeMaker() :coins_({ 50, 25, 10, 5, 1 })
{
	memo_.resize(coins_.size(), std::vector<long>(7489 + 1, -1));
}

long ChangeMaker::Count(const std::size_t i, const int change)
{
	if (i >= coins_.size() || change < 0)
	{
		return 0;
	}

	if (change == 0)
	{
		return 1;
	}

	auto &memo = memo_[i][change];
	if (memo != -1)
	{
		return memo;
	}
	return memo = Count(i + 1, change) + Count(i, change - coins_[i]);
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	auto change = 0;
	ChangeMaker change_maker;

	while (std::cin >> change, !std::cin.eof())
	{
		std::cout << change_maker.Count(change) << std::endl;
	}
	return 0;
}
